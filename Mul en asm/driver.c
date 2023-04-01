#include <stdio.h>

#include "cdecl.h"


void PRE_CDECL mul( int, int  ) POST_CDECL; /* prototype for assembly routine */

int main(void)
{
    int a, b;
    printf("Number one: ");
    scanf("%d", &a);
    printf("Number two: ");
    scanf("%d", &b);
    mul(a, b);
    return 0;
}
