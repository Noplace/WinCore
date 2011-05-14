/******************************************************************************
* Copyright Khalid Al-Kooheji 2010
* Filename    : hash_table.h
* Description : very primitive and simple and fast hash table to be used to 
*  quickly access data based on key, maximum size currently must be known in 
*  advance, 
* 
*  Note: no support for collisions , index must be castable to int
*  
*******************************************************************************/
#ifndef COLLECTIONS_VECTOR_H
#define COLLECTIONS_VECTOR_H

#include "../types.h"

namespace core {
namespace collections {

template<typename Type>
class Vector {
 public:
  Type& operator [](uint32_t index) {
    return buffer_[uint32_t];
  }

 private:
   Type* buffer_;

};

}
}

#endif