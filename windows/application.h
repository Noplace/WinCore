#ifndef WINDOWS_APPLICATION_H
#define WINDOWS_APPLICATION_H

#include <windows.h>

namespace core {
namespace windows {


/*
  Class Name  : Application
  Description : this is the application's class
*/
class Application {
 public:
   Application();
   Application(HINSTANCE instance , LPSTR command_line, int show_command);
   virtual ~Application();
   virtual int Run() = 0;
   void InitConsole();
   bool RanBefore(LPCSTR identifier);
};

}
}

#endif