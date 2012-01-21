#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include "../collections/hash_table.h"

namespace core {
namespace windows {

/*
  Class Name  : Window
  Description : this is a base class to use for creating windows
*/
class Window {
 public:
  Window();
  ~Window();
  void SetClientSize(int width,int height);
  void Center();
  void Show();
  void Hide();
  HWND handle() { return handle_; }
  DWORD style() { return style_; }
  void set_style(DWORD style) { style_ = style; }
 protected:
  void Create(char* title);
  void Destroy();
  virtual int OnCreate(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnDestroy(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnResize(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnMouseMove(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnMouseWheel(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnLeftButtonDown(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnLeftButtonUp(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnMiddleButtonDown(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnMiddleButtonUp(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnRightButtonDown(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnRightButtonUp(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnCaptureChanged(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnInput(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnKeyDown(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnKeyUp(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnSysKeyDown(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnSysKeyUp(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnSysCommand(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnClose(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int OnActivate(WPARAM wParam,LPARAM lParam) { return -1; }
  virtual int PreProcessMessages(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { return -1; }
 private:
  char class_name_[255];
  HWND handle_;
  DWORD style_;
  ATOM class_;
  static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

}
}

#endif