#include <stdio.h>


extern float mul(float base, float exp);

int main(void)
{
		
    float a, b;
    printf("Number one: ");
    scanf("%f", &a);
    printf("Number two: ");
    scanf("%f", &b);
    printf("The result is: %f \n", mul(a,b));
    return 0;
}
