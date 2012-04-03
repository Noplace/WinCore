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
/*
Based on FNV Hash http://isthe.com/chongo/tech/comp/fnv/#FNV-param
*/
#ifndef HASH_H
#define HASH_H


#define FNV_PRIME(n) ((1<<(n-8)) + (1<<8) + 0x93)
#define FNV_ob_32 2166136261U
#define TINY_MASK(x) (((unsigned int)1<<(x))-1)

namespace core {

class Hash {
 public:
  inline static unsigned int hash32(char* data,unsigned int length) {
    unsigned int hash = FNV_ob_32;
    for (; length != 0; data++ && --length) {
	    hash = hash * FNV_PRIME(32);
	    hash = hash ^ *data;
    }
    return hash;
  }

  inline static unsigned int hashx(char* data,unsigned int length,unsigned int x) {
    unsigned int hash = hash32(data, length);
    return (((hash>>x) ^ hash) & TINY_MASK(x));
  }
};

}

#undef TINY_MASK

#endif