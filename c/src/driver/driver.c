#include <stdio.h>
#include <stdlib.h>

#include "../../inc/cdecl/cdecl.h"
#include "../../inc/requests/request.h"

void PRE_CDECL mul( float, float, float *  ) POST_CDECL; /* prototype for assembly routine */

int main(void) {

    float a, b, result;
    
    printf("Number one: ");
    scanf("%f", &a);
    printf("Number two: ");
    scanf("%f", &b);

    // Hacemos la conversión
    mul(a, b, &result);

    printf("The result is: %f \n", result);

    return 0;
}
