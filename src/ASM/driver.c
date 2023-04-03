#include <stdio.h>

#include "cdecl.h"


void PRE_CDECL mul( float, float, float *  ) POST_CDECL; /* prototype for assembly routine */

int main(void)
{
    float a, b, res;
    printf("Number one: ");
    scanf("%f", &a);
    printf("Number two: ");
    scanf("%f", &b);
    mul(a, b, &res);
    printf("The result is: %f \n", res);
    return 0;
}
