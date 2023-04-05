#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <curl/curl.h>

#include "../../inc/cJSON/cJSON.h"

#define MSG_MAX 100

// Función para enviar la información al proceso principal
void sendVal(char *msg);
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

/**
 * @brief Ejecuta una request a una API con información sobre el
 * exchange de cryptomonedas y le envia los datos relevantes al
 * proceso principal
 */
int main(int argc, char const *argv[]) {

  if(argc < 1) {
    printf("Faltan args.\n");
    exit(1);
  } else {
    printf("Making request...%s\n", argv[1]);
  }

  CURL *curl_handle;
  CURLcode res;
 
  struct MemoryStruct chunk;
 
  chunk.memory = malloc(1);  // Memoria reservada para la info (Crece dinámicamente)
  chunk.size = 0;            // Aún no hay info
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  // Inicializamos el curl
  curl_handle = curl_easy_init();
 
  // Especificamos el url 
  curl_easy_setopt(curl_handle, CURLOPT_URL, "https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=BTC&to_currency=USD&apikey=EG7JWLOAMEKIU3IR");
 
  // Enviaremos la información obtenida y la estructura a WriteMemoryCallback
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 
  // Algunos servers precisan esta info (user_agent)
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
  // Obtenemos los datos
  res = curl_easy_perform(curl_handle);
 
  // Chequeo de errores
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  } else {  // Obtenemos la información en formato json
    printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
    printf("DATA: \n%s\n", (char *)chunk.memory);
  }

  // Parseamos el json
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
    if(!cJSON_IsString(exchange)) {
      printf("Error parsing value\n");
    }
  }

  // Obtenemos el valor en float
  float rate = (float) atof(exchange->valuestring);
  printf("RATE: %f\n", rate);

  // Enviamos el valor del rate
  sendVal(exchange->valuestring);

  // Eliminamos el objeto de json
  cJSON_Delete(jason);
 
  // Limpiamos el curl y la memoria
  curl_easy_cleanup(curl_handle);
  free(chunk.memory);
  curl_global_cleanup();
 
  return 0;
}

/**
 * @brief Envia la información al proceso principal
 * haciendo uso de una FIFO
 * 
 * @param msg Mensaje a enviar
 */
void sendVal(char *msg) {
    // File descriptor y ubicación para la FIFO
    int fd;
    char *fifo = "/tmp/fifoRequest";
    char message[MSG_MAX];

    // Abrimos el archivo
    fd = open(fifo, O_WRONLY | O_NONBLOCK);

    if(fd == -1) {
        if(errno == ENOENT || errno == ENXIO) {
            fprintf(stdout, "Server Disconnected.\n");        
            exit(1);
        }
        perror("Error abriendo la FIFO.");
        exit(1);
    }

    // Formato del mensaje
    memset(message,0,sizeof(message));
    strcpy(message,msg);

    // Escribimos el mensaje en la FIFO
    if(write(fd, message, sizeof(message)) == -1) {
        if(errno == EBADF || errno == ENXIO) {
            fprintf(stdout, "Server Disconnected.\n");  
            exit(1);
        } else {
            perror("Error al leer el mensaje (B).\n");
            exit(1);
        }
    }

    printf("Data sent: %s",message);

    // Cerramos el archivo
    if(close(fd) == -1) {
        fprintf(stderr,"Error al cerrar el archivo (B).");
        exit(1);
    }

}
