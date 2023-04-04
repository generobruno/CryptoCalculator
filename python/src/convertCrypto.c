#include <stdio.h>



extern float mul(float base, float exp);

float _convert(float rate, float cant) {
    
		float res;
    // Hacemos la conversión
    

    res = mul(rate, cant);

    return res;
}
