#ifndef WINDOWS_WINDOWS_H
#define WINDOWS_WINDOWS_H

//#define nullptr 0

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//#include <stdint.h>
#include "../types.h"
#include "application.h"
#include "window.h"

template<class Interface> 
inline void SafeRelease(Interface **ppInterfaceToRelease) {
    if (*ppInterfaceToRelease != NULL) {
        (*ppInterfaceToRelease)->Release();
        (*ppInterfaceToRelease) = NULL;
    }
}

template<class Interface> 
inline void SafeDelete(Interface **ppInterfaceToDelete) {
    if (*ppInterfaceToDelete != NULL) {
        delete (*ppInterfaceToDelete);
        (*ppInterfaceToDelete) = NULL;
    }
}

template<class Interface> 
inline void SafeDeleteArray(Interface **ppInterfaceToDelete) {
    if (*ppInterfaceToDelete != NULL) {
        delete [] (*ppInterfaceToDelete);
        (*ppInterfaceToDelete) = NULL;
    }
}


#endif