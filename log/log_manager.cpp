#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <queue>
#include "../hash/hash.h"
#include "log_manager.h"


namespace core {

LogManager::LogManager() : current_channel(NULL)  {

}

LogManager::~LogManager() {
  Deinitialize();
}

void LogManager::Initialize(char* path) {
  memset(channels,0,sizeof(channels));
  strcpy_s<MAX_PATH>(this->path,path);
  InitializeCriticalSection(&requests_cs);
  requests_thread = CreateThread(NULL,0,&LogManager::FlushThreadProc,this,0,NULL);
}

void LogManager::Deinitialize() {
  for(int i=0;i<LOG_CHANNEL_COUNT;++i) {
    current_channel = &channels[i];
    CloseChannel(i);
  }
  CloseHandle(requests_thread);
  DeleteCriticalSection(&requests_cs);
}

LogManager& LogManager::Channel(char* channel_name) {
  unsigned int channel_index = core::Hash::hashx(channel_name,strlen(channel_name),8);
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
  if (channels[index].file == NULL) {
    char filename[MAX_PATH];
    sprintf_s<MAX_PATH>(filename,"%s%s.log",path,name);
    fopen_s(&channels[index].file, filename, "w+n"); 
    channels[index].buffer_pos = 0;
    channels[index].buffer_size = 1024*16;
    channels[index]._index = index;
    channels[index].th = NULL;
    setvbuf(channels[index].file,NULL,_IOFBF,channels[index].buffer_size);
    strcpy_s<MAX_PATH>(channels[index].name,name);
    InitializeCriticalSection(&channels[index].critical_section);
  }
  return &channels[index];
}

void LogManager::CloseChannel(int index) {
  if (channels[index].file != NULL) {
    CloseThread(&channels[index]);
    fflush(channels[index].file);
    fclose(channels[index].file);
    channels[index].buffer_pos = 0;
    channels[index].buffer_size = 0;
    channels[index]._index = 0;
    channels[index].file = NULL;
    DeleteCriticalSection(&channels[index].critical_section);
  }
}

void LogManager::CloseThread(LogChannel* ch) {
  if (ch->th != NULL) {
    EnterCriticalSection(&ch->critical_section);
    CloseHandle(ch->th);
    LeaveCriticalSection(&ch->critical_section);
    ch->th = NULL;
  }
}

 void LogManager::FlushCheck(LogChannel* ch) {
   if (ch->buffer_pos >= ch->buffer_size) {
     fflush(ch->file);
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