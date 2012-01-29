/*
Based on FNV Hash http://isthe.com/chongo/tech/comp/fnv/#FNV-param
*/
#ifndef HASH_H
#define HASH_H


#define FNV_PRIME(n) ((1<<(n-8)) + (1<<8) + 0x93)
#define FNV_ob_32 2166136261U
#define TINY_MASK(x) (((unsigned int)1<<(x))-1)

namespace core {

class Hash {
 public:
  inline static unsigned int hash32(char* data,unsigned int length) {
    unsigned int hash = FNV_ob_32;
    for (; length != 0; data++ && --length) {
	    hash = hash * FNV_PRIME(32);
	    hash = hash ^ *data;
    }
    return hash;
  }

  inline static unsigned int hashx(char* data,unsigned int length,unsigned int x) {
    unsigned int hash = hash32(data, length);
    return (((hash>>x) ^ hash) & TINY_MASK(x));
  }
};

}

#undef TINY_MASK

#endif