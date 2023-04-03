#include <stdio.h>

#include "ASM/cdecl.h"

void PRE_CDECL mul( float, float, float *  ) POST_CDECL; /* prototype for assembly routine */

float _convert(float rate, float cant) {
    float res;

    // Hacemos la conversión
    mul(rate, cant, &res);

    res = rate * cant;

    return res;
}
