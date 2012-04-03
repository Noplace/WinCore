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
#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H
#include <windows.h>
#include <queue>
#define LOG_CHANNEL_COUNT 256

namespace core {

struct LogChannel {
  FILE* file;
  char name[MAX_PATH];
  size_t buffer_size;
  size_t buffer_pos;
  int _index;
  CRITICAL_SECTION critical_section;
  HANDLE th;
};

class LogManager {
 public:
  LogManager();
  ~LogManager();
  void Initialize(char* path);
  void Deinitialize();
  LogManager& Channel(char* channel_name);
  LogManager& Log(char* text,...);
  LogManager& TimeStamp();
 private:
  struct ThreadParam {
    LogManager* lm;
    LogChannel* ch;
  };

  struct FlushRequest {
    FlushRequest():lm(NULL),ch(NULL) {

    }
    FlushRequest(const FlushRequest& other):lm(other.lm),ch(other.ch) {

    }
    LogManager* lm;
    LogChannel* ch;
  };

  LogChannel* OpenChannel(int index,char* name);
  void CloseChannel(int index);
  void CloseThread(LogChannel* ch);
  void FlushCheck(LogChannel* ch);
  static DWORD WINAPI FlushThreadProc(__in  LPVOID lpParameter);
  char path[MAX_PATH];
  LogChannel* channels[LOG_CHANNEL_COUNT];
  LogChannel* current_channel;
  std::queue<FlushRequest> requests;
  CRITICAL_SECTION requests_cs;
  HANDLE requests_thread;
};

}

#endif