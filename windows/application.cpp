#include "application.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

namespace core {
namespace windows {


Application::Application() {
}

Application::Application(HINSTANCE instance , LPSTR command_line, int show_command) {

}

Application::~Application() {

  FreeConsole();
}

void Application::InitConsole() {
  AllocConsole();
  HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
  int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
  FILE* hf_out = _fdopen(hCrt, "w");
  setvbuf(hf_out, NULL, _IONBF, 1);
  *stdout = *hf_out;

  HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
  hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
  FILE* hf_in = _fdopen(hCrt, "r");
  setvbuf(hf_in, NULL, _IONBF, 128);
  *stdin = *hf_in;
    
}

bool Application::RanBefore(LPCSTR identifier) {
  HANDLE handle = CreateMutex(NULL,TRUE,identifier);
  if (GetLastError() == ERROR_ALREADY_EXISTS) {
    return true;
  }
  return false;
}

}
}
