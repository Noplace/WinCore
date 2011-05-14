#ifndef TYPES_H
#define TYPES_H
  
typedef unsigned __int8   uint8_t;
typedef unsigned __int16  uint16_t;
typedef unsigned __int32  uint32_t;
typedef unsigned __int64  uint64_t;

typedef signed __int8     sint8_t;
typedef signed __int16    sint16_t;
typedef signed __int32    sint32_t;
typedef signed __int64    sint64_t;

#if defined(_M_IA64)
typedef unsigned __int128 uint128_t;
typedef signed __int128   sint128_t;
#endif

#define null 0

#endif