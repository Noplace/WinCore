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
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <queue>
#include <Shlobj.h>
#include "../hash/hash.h"
#include "log_manager.h"


namespace core {

LogManager::LogManager() : current_channel(nullptr),requests_thread(nullptr)  {
    memset(channels,0,sizeof(channels));
}

LogManager::~LogManager() {
  Deinitialize();
}

void LogManager::Initialize(char* path) {
  SHCreateDirectoryEx(nullptr,path,nullptr);
  strcpy_s<MAX_PATH>(this->path,path);

  InitializeCriticalSection(&requests_cs);
  requests_thread = CreateThread(NULL,0,&LogManager::FlushThreadProc,this,0,NULL);
}

void LogManager::Deinitialize() {
  for(int i=0;i<LOG_CHANNEL_COUNT;++i) {
    current_channel = channels[i];
    if (current_channel != nullptr)
      CloseChannel(i);
  }
  if (requests_thread!=nullptr) {
    WaitForSingleObject(requests_thread,INFINITE);
    CloseHandle(requests_thread);
    requests_thread = nullptr;
    DeleteCriticalSection(&requests_cs);
  }
  
}

LogManager& LogManager::Channel(char* channel_name) {
  unsigned int channel_index = core::Hash::hashx(channel_name,(unsigned int)strlen(channel_name),8);
  current_channel = OpenChannel(channel_index,channel_name);
  return *this;
}

LogManager& LogManager::Log(char* text,...) {
  assert(current_channel != NULL);
  va_list args;
  va_start(args,text);
  EnterCriticalSection(&current_channel->critical_section);
  int result = vfprintf_s(current_channel->file,text,args);
  LeaveCriticalSection(&current_channel->critical_section);
  va_end(args);
  _fflush_nolock(current_channel->file);
  if (result > 0) {
    current_channel->buffer_pos += result;
    FlushCheck(current_channel);
  }

  return *this;
}

LogManager& LogManager::TimeStamp() {
  time_t ltime;
  struct tm today;
  _tzset();
  time(&ltime);
  _localtime64_s(&today,&ltime);
  
  return Log("%02d/%02d/%04d - %02d:%02d:%02d",
    today.tm_mday,
    today.tm_mon,
    1900+today.tm_year,
    today.tm_hour,
    today.tm_min,
    today.tm_sec);
}

LogChannel* LogManager::OpenChannel(int index,char* name) {
  if (channels[index] == nullptr) {
    channels[index] = new LogChannel();
    channels[index]->file = nullptr;
  }
  if (channels[index]->file == nullptr) {
    char filename[MAX_PATH];
    sprintf_s<MAX_PATH>(filename,"%s%s.log",path,name);
    fopen_s(&channels[index]->file, filename, "w+"); 
    channels[index]->buffer_pos = 0;
    channels[index]->buffer_size = 1024*32;
    channels[index]->_index = index;
    channels[index]->th = NULL;
    setvbuf(channels[index]->file,NULL,_IOFBF,channels[index]->buffer_size);
    strcpy_s<MAX_PATH>(channels[index]->name,name);
    InitializeCriticalSection(&channels[index]->critical_section);
  }
  return channels[index];
}

void LogManager::CloseChannel(int index) {
  if (channels[index]->file != nullptr) {
    CloseThread(channels[index]);
    fflush(channels[index]->file);
    fclose(channels[index]->file);
    channels[index]->buffer_pos = 0;
    channels[index]->buffer_size = 0;
    channels[index]->_index = 0;
    channels[index]->file = NULL;
    DeleteCriticalSection(&channels[index]->critical_section);
  }
  delete current_channel;
  current_channel = nullptr;
  channels[index] = nullptr;
}

void LogManager::CloseThread(LogChannel* ch) {
  if (ch != nullptr && ch->th != NULL) {
    EnterCriticalSection(&ch->critical_section);
    WaitForSingleObject(ch->th,INFINITE);
    CloseHandle(ch->th);
    LeaveCriticalSection(&ch->critical_section);
    ch->th = NULL;
  }
}

 void LogManager::FlushCheck(LogChannel* ch) {
   if (ch->buffer_pos >= ch->buffer_size) {
     _fflush_nolock(ch->file);
     ch->buffer_pos = 0;     
     /*FlushRequest fr;
     fr.ch = ch;
     fr.lm = this;
     EnterCriticalSection(&fr.lm->requests_cs);
     requests.push(fr);
     LeaveCriticalSection(&fr.lm->requests_cs);*/
     /*CloseThread(ch);
     static ThreadParam tp;
     tp.ch = ch;
     tp.lm = this;
     ch->th = CreateThread(NULL,0,&LogManager::FlushThreadProc,&tp,0,NULL);*/
   }
 }

 DWORD WINAPI LogManager::FlushThreadProc(__in  LPVOID lpParameter) {
   /*
   LogManager* lm = static_cast<LogManager*>(lpParameter);

   while (1) {
     if (lm->requests.empty() == false) {
       FlushRequest fr = lm->requests.front();
       LogChannel* ch = fr.ch;
       EnterCriticalSection(&ch->critical_section);
       fflush(ch->file);
       ch->buffer_pos = 0;
       LeaveCriticalSection(&ch->critical_section);

       EnterCriticalSection(&fr.lm->requests_cs);
       lm->requests.pop();
       LeaveCriticalSection(&fr.lm->requests_cs);
     } else {

       Sleep(100);
     }
   } */
   /*
   ThreadParam* tp = static_cast<ThreadParam*>(lpParameter);
   LogManager* lm = tp->lm;
   LogChannel* ch = tp->ch;
   EnterCriticalSection(&ch->critical_section);
   fflush(ch->file);
   ch->buffer_pos = 0;
   LeaveCriticalSection(&ch->critical_section);*/
   return 0;
 }

 }