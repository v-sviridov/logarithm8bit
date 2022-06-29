// log8bit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "math.h"
#include "convert2decibel.cpp"

void test( float in);

int _tmain(int argc, _TCHAR* argv[]) {
  test( 555555 );
  test( 10.);
  test( 200 );
  test( 10000 );
  test( 1 );
  test( 0.001 );
  test( 0.0001 );
  test( 0.000000123 );
  test( 0.0000123 );
  test(1024);
  test(4097);
  test(42);
  getchar();
}


void test(float in) {
    if (in == 0) {
        printf("\n INFINITY %f", INFINITY);
    }
    else {
        printf("\n out2 = %f (%f)", convert2decibel(in), 10 * log10(in));
    }
}
