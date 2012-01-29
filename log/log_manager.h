#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H
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
  LogChannel channels[LOG_CHANNEL_COUNT];
  LogChannel* current_channel;
  std::queue<FlushRequest> requests;
  CRITICAL_SECTION requests_cs;
  HANDLE requests_thread;
};

}

#endif