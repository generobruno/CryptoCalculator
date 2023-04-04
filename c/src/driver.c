#include <stdio.h>
#include <stdlib.h>

#include "../inc/cdecl.h"

void PRE_CDECL mul( float, float, float *  ) POST_CDECL; /* prototype for assembly routine */

int main(void) {

    float a, b, result;

    /*
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=ars,usd,eur");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Hacemos el request
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            perror("Error en curl_perform.\n");
            printf("%s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            exit(1);
        }

        curl_easy_cleanup(curl);
    }
    */
    
    printf("Number one: ");
    scanf("%f", &a);
    printf("Number two: ");
    scanf("%f", &b);

    // Hacemos la conversión
    mul(a, b, &result);

    printf("The result is: %f \n", result);

    return 0;
}
