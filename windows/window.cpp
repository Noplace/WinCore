#include "windows.h"

namespace core {
namespace windows {

//core::collections::HashTable<HWND,Window*,100> Window::windows_map_;

Window::Window() {
  set_style(WS_BORDER|WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU|WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
}

Window::~Window() {
//UnregisterClass(
}

void Window::SetClientSize(int width,int height) {
  RECT rectangle;
  SetRect(&rectangle,0,0,width,height);
  AdjustWindowRect(&rectangle,style(),false);
  
 
  int actual_width  = static_cast<int>(rectangle.right  - rectangle.left);
  int actual_height = static_cast<int>(rectangle.bottom - rectangle.top);

  SetWindowPos(handle(),0,0,0,actual_width,actual_height,SWP_NOACTIVATE|SWP_NOMOVE);  

}

void Window::Center() {
  RECT rectangle;
  GetWindowRect(handle(),&rectangle);
  
  int screen_width  = GetSystemMetrics(SM_CXSCREEN);
  int screen_height = GetSystemMetrics(SM_CYSCREEN);
  
  int left   = (screen_width - rectangle.right)/2;
  int top    = (screen_height - rectangle.bottom)/2;
  
  SetWindowPos(handle(),0,left,top,0,0,SWP_NOACTIVATE|SWP_NOSIZE);  
  
}

void Window::Show() {
  ShowWindow(handle(), SW_SHOW); 
  UpdateWindow(handle()); 
}

void Window::Hide() {
  ShowWindow(handle(), SW_HIDE); 
}

void Window::Create(TCHAR* title) {
  WNDCLASSEXA window_class;
  memset(&window_class,0,sizeof(window_class));
  window_class.cbSize = sizeof(window_class);
  window_class.cbClsExtra = 0;
  window_class.cbWndExtra = 0;
  window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  window_class.lpfnWndProc = WindowProc;
  window_class.lpszClassName = "Window Class";
  window_class.hCursor = LoadCursor((HINSTANCE) NULL, IDC_ARROW); 
  window_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)); 
  
  RegisterClassEx(&window_class);
  
  CreateWindow("Window Class",title,WS_CLIPSIBLINGS | WS_CLIPCHILDREN | style(),0,0,100,100,NULL,NULL,NULL,this);
  SetWindowText(handle_,title);
}


LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  
 
  switch( uMsg ) {
    case WM_NCCREATE: {
      CREATESTRUCT* create_struct = reinterpret_cast<CREATESTRUCT*>(lParam);
      Window* current_window = reinterpret_cast<Window*>(create_struct->lpCreateParams);
      //Window::windows_map_[hwnd] = current_window;
      current_window->handle_ = hwnd;
      SetWindowLongPtr(hwnd,GWLP_USERDATA,PtrToUlong(current_window));
      return TRUE;
    }  
    break;
  }
  
  //Window* current_window = Window::windows_map_[hwnd];
  Window* current_window = reinterpret_cast<Window*>(static_cast<LONG_PTR>(GetWindowLongPtr(hwnd,GWLP_USERDATA)));
  int result = -1;
  if (current_window != NULL) {
    switch( uMsg ) {
      case WM_CREATE: {
          result = current_window->OnCreate(wParam,lParam);
        }
        break;
      case WM_DESTROY: {
         result = current_window->OnDestroy(wParam,lParam);
       }
       break;
      case WM_CLOSE: {
          result = current_window->OnClose(wParam,lParam);
        }
        break;
      case WM_SIZE: {
          result = current_window->OnResize(wParam,lParam);
        }
        break;
      case WM_INPUT: {
          result = current_window->OnInput(wParam,lParam);
        }
        break;
      case WM_KEYDOWN: {
          result = current_window->OnKeyDown(wParam,lParam);
        }
        break;
      case WM_KEYUP: {
          result = current_window->OnKeyUp(wParam,lParam);
        }
        break;

      case WM_SYSKEYDOWN: {
          result = current_window->OnSysKeyDown(wParam,lParam);
        }
        break;
      case WM_SYSKEYUP: {
          result = current_window->OnSysKeyUp(wParam,lParam);
        }
        break;
      case WM_CAPTURECHANGED: {
          result = current_window->OnCaptureChanged(wParam,lParam);
        }
        break;
      case WM_MOUSEMOVE: {
          result = current_window->OnMouseMove(wParam,lParam);
        }
        break;
      case WM_MOUSEWHEEL: {
          result = current_window->OnMouseWheel(wParam,lParam);
        }
        break;
      case WM_LBUTTONDOWN: {
          result = current_window->OnLeftButtonDown(wParam,lParam);
        }
        break;
      case WM_LBUTTONUP: {
          result = current_window->OnLeftButtonUp(wParam,lParam);
        }
        break;
      case WM_MBUTTONDOWN: {
          result = current_window->OnMiddleButtonDown(wParam,lParam);
        }
        break;
      case WM_MBUTTONUP: {
          result = current_window->OnMiddleButtonUp(wParam,lParam);
        }
        break;
      case WM_RBUTTONDOWN: {
          result = current_window->OnRightButtonDown(wParam,lParam);
        }
        break;
      case WM_RBUTTONUP: {
          result = current_window->OnRightButtonUp(wParam,lParam);
        }
        break;
      default:
        result = -1;
        break;
      
    }
  }

  if (result == -1)
    result = DefWindowProc(hwnd,uMsg,wParam,lParam);

  return result;
}


}
}