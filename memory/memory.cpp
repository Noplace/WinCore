/*****************************************************************************************************************
* Copyright (c) 2012 Khalid Ali Al-Kooheji                                                                       *
*                                                                                                                *
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and              *
* associated documentation files (the "Software"), to deal in the Software without restriction, including        *
* without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        *
* copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the       *
* following conditions:                                                                                          *
*                                                                                                                *
* The above copyright notice and this permission notice shall be included in all copies or substantial           *
* portions of the Software.                                                                                      *
*                                                                                                                *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT          *
* LIMITED TO THE WARRANTIES OF MERCHANTABILITY, * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.          *
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, * DAMAGES OR OTHER LIABILITY,      *
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE            *
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                                         *
*****************************************************************************************************************/
#include "memory.h"

struct {
  LPVOID base;
  uint8_t* ptr;
  uint32_t reserve_size;
}v;

struct AllocationHeader {
  uint64_t ptr;
  uint32_t size_bytes;
};

void virtualInit(uint32_t reserve_size) {
  v.reserve_size = reserve_size;
  v.base = VirtualAlloc((LPVOID)0,v.reserve_size,MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE);
  v.ptr = (uint8_t*)v.base;
}

void virtualDeinit() {
  VirtualFree(v.base,v.reserve_size,MEM_DECOMMIT);
  VirtualFree(v.base,0,MEM_RELEASE);
}

void* virtualAlloc(uint32_t size_bytes) {
  auto result = v.ptr;
  AllocationHeader allocation;
  allocation.ptr = uint64_t(v.ptr + sizeof(allocation));
  allocation.size_bytes = size_bytes;
  memcpy(v.ptr,&allocation,sizeof(allocation));
  v.ptr += size_bytes + sizeof(allocation);
  return (void*)allocation.ptr;
}

void virtualFree(void* ptr) {
  AllocationHeader* allocation = (AllocationHeader* )((uint8_t*)ptr - sizeof(AllocationHeader));
  v.ptr -= allocation->size_bytes + sizeof(AllocationHeader);
}