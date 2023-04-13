Pregunte al administrador.
Dentro de la carpeta python se encuentra el scrypt cryptoCalc.py y este es el que permite calcular la cotizacion de las cryptomonedas, utiliza una API para obtener los cambios de la criptomoneda a dolares, pesos argentinos y euroes, luego utiliza una funcion en C para realizar la conversion a la cantidad deseada.
El usuario debe ingresar la cantidad de criptomoneda que se desea a convertir.
Dentro de la carpeta python/src se encuentra el archivo converCrypto.c esta el archivo en C que se usa para hacer la multiplicacion entre el tipo de cambio y el valor de la criptomoneda y se lo de vuelve al programa escrito en python.
