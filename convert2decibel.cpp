#include "stdafx.h"

// Big-endian platform
#define BE_INDEX 0

// Little-endian platform
#define LE_INDEX 3

#define EXP_INDEX LE_INDEX
// select 20 precalculate values
// #define PREC20

#ifdef PREC20
const float lg2[] = {
  0.0,    0.0704, 0.1375, 0.2016, 0.2630, 0.3219, 0.3785,
  0.4330, 0.4854, 0.5361, 0.5850, 0.6323, 0.6781, 0.7225,
  0.7655, 0.8074, 0.8480, 0.8875, 0.9260, 0.9635, 1.0
}; // 21 values so max index is 20
#define MAX_INDEX 20
#else
const float lg2[] = {
  0.0,    0.1375, 0.2630, 0.3785, 0.4854,
  0.5850, 0.6781, 0.7655, 0.8480, 0.9260, 1.0
};
#define MAX_INDEX 10
#endif // PREC20


static float convert2decibel(float x) {    
  union {
    unsigned char ch[4];
    float   fl;
    unsigned long ln;
  } un;
  float exp2;
  int index, offset;
  
  un.fl = x;
  un.ln = ( un.ln << 1 );
  offset = ( un.ch[EXP_INDEX] - 127 );
  if (offset < 30 && offset > -30) {
    if (offset < 0) {
      exp2 = (float)(1. / (1 << (-offset)));
    }
    else {
      exp2 = (float)(1 << offset);
    }
    // convert x/exp2 ratio to index
    // 1.0 <= x/exp2 < 2.0
    index = (int)((x / exp2 - 1.) * MAX_INDEX + 0.5);
  }
  else {
    index = 0;
  }
  // dB = 10* log(x) = 10 * log(2) * lg2(x);
  // lg2(x) = (offset + lg2[index]);
  // 10 * log(2) = 3.01
  return 3.01 * (offset + lg2[index]); 
}

