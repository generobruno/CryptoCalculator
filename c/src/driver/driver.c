#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "../../inc/cdecl/cdecl.h"
#include "../../inc/requests/request.h"

#define MSG_MAX 100

void PRE_CDECL mul( float, float, float *  ) POST_CDECL; /* prototype for assembly routine */

void createFIFO(void);
void removeFIFO(void);
float recvVal(void);

/**
 * @brief Hace una conversión de la cantidad de cryptomonedas
 * que le pasemos a dolares, euros y pesos.
 */
int main(void) {

    float a, rate, result;
    createFIFO();
    
    // Hacemos que un hijo ejecute la funcion de request
    pid_t child = fork();

    char *args = "En request";

    switch (child)
    {
    case -1:    // Caso de error
        perror("Error en fork");
        exit(1);
    case 0:     // Caso del hijo
        execvp("./requester", &args); // TODO Revisar: De esta manera solo funca ejecutando en CryptoCalculator/c.
        exit(errno);
    default:    // Caso del padre
        // Espera a que el hijo termine
        rate = recvVal();
        removeFIFO();
        wait(NULL);
        break;
    }
    
    printf("\n\nRate BTC: %f\n", rate);
    printf("Number to calculate: ");
    scanf("%f", &a);

    // Hacemos la conversión
    mul(a, rate, &result);

    printf("\n\nThe result is: %f \n", result);

    return 0;
}

/**
 * @brief Crea una FIFO para comunicarse con el proceso
 * que obtiene la tasa de conversión de la cryptomoneda
 */
void createFIFO(void) {
    // File descriptor y ubicación para la FIFO
    char *fifo = "/tmp/fifoRequest";

    // Estructura de control
    struct stat stats;

    // Eliminamos la FIFO si ya existía
    if(stat(fifo, &stats) < 0) {
        if(errno != ENOENT) {
            perror("Fallo en stat().");
            exit(1);
        }
    } else {
        if(unlink(fifo) < 0) {
            perror("Error eliminando la FIFO anterior.");
            exit(1);
        }
    }

    // Creamos la FIFO
    if(mkfifo(fifo, 0666) == -1) {
        fprintf(stderr,"Error creando la FIFO (B).");
        exit(1);
    }

    printf("FIFO Creada\n");
}

/**
 * @brief Elimina la FIFO luego de que haya sido utilizada
 */
void removeFIFO(void) {
    // File descriptor y ubicación para la FIFO
    char *fifo = "/tmp/fifoRequest";

    // Remueve la FIFO
    if(unlink(fifo) == -1) {
        fprintf(stderr,"Error eliminando la FIFO anterior (B).");
        exit(1);
    } else {
        fprintf(stdout,"FIFO Eliminada con éxito.\n");
    }
}

/**
 * @brief Recibe el valor de la tasa de conversión a través
 * de la FIFO
 * 
 * @return float Tasa de conversión
 */
float recvVal(void) {
    // File descriptor y ubicación para la FIFO
    char *fifo = "/tmp/fifoRequest";

    // File descriptor para la FIFO de clientes B   
    int fd;

    // Abrimos el archivo para lectura 
    fd = open(fifo, O_RDONLY);

    if(fd == -1) {
        perror("Error abriendo la FIFO.");
        exit(1);
    }

    // File descriptor y ubicación de la FIFO
    char buff[MSG_MAX];

    // Leemos el mensaje (Bloqueante)
    if(read(fd,buff,MSG_MAX) <= 0) {
        perror("No se pudo recibir el mensaje\n");
        exit(1);
    }

    // Cerramos el archivo de la FIFO
    if(close(fd) == -1) {
        fprintf(stderr,"Error al cerrar el archivo (B).");
        exit(1);
    }

    // Obtenemos el valor numerico del string
    float rate = (float) atof(buff);
    printf("Rate obtenido: %f\n", rate);

    return rate;
}