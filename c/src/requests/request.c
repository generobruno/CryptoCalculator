#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "../../inc/cJSON/cJSON.h"
struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}
 
int main(void) {
  CURL *curl_handle;
  CURLcode res;
 
  struct MemoryStruct chunk;
 
  chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
  chunk.size = 0;    /* no data at this point */
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */
  curl_handle = curl_easy_init();
 
  /* specify URL to get */
  curl_easy_setopt(curl_handle, CURLOPT_URL, "https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=BTC&to_currency=USD&apikey=EG7JWLOAMEKIU3IR");
 
  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
  /* we pass our 'chunk' struct to the callback function */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 
  /* some servers do not like requests that are made without a user-agent
     field, so we provide one */
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
  /* get it! */
  res = curl_easy_perform(curl_handle);
 
  /* check for errors */
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }
  else {
    /*
     * Now, our chunk.memory points to a memory block that is chunk.size
     * bytes big and contains the remote file.
     *
     * Do something nice with it!
     */
 
    printf("%lu bytes retrieved\n", (unsigned long)chunk.size);


    printf("DATA: \n%s\n", (char *)chunk.memory);
  }

  // TODO Parsear JSON
  cJSON *jason = cJSON_Parse(chunk.memory);
  if(jason == NULL) {
      const char *error = cJSON_GetErrorPtr();
      if(error != NULL) {
          fprintf(stderr, "ERROR: %s\n", error);
      }
  }
  const cJSON *data = cJSON_GetObjectItem(jason, "Realtime Currency Exchange Rate");
  cJSON *exchange = NULL;
  if(data) {
    exchange = cJSON_GetObjectItemCaseSensitive(data,"5. Exchange Rate");
    if(cJSON_IsString(exchange)) {
      printf("RATE: %s\n",exchange->valuestring);
    }
  }

  float rate = (float) atof(exchange->valuestring);
  printf("FLOAT RATE: %f\n", rate);

  // Eliminamos el objeto de json
  cJSON_Delete(jason);
 
  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);
 
  free(chunk.memory);
 
  /* we are done with libcurl, so clean it up */
  curl_global_cleanup();
 
  return 0;
}
