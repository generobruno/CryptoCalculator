'''
    Calculadora de cotización de crypto
'''

import requests, json, ctypes, sys
import numpy as np

def CryptoCalc(cant):
    # BTC a USD,ARS,EUR
    OriginalUrl = 'https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=CRYPTO&to_currency=PAPER&apikey=EG7JWLOAMEKIU3IR'

    # Monedas
    crypto = 'BTC'
    url = OriginalUrl.replace('CRYPTO',crypto)

    # Hacemos request para obtener el cambio a dolares
    toUSD = url.replace('PAPER', 'USD')
    rUSD = requests.get(toUSD)
    if rUSD:
        print('Response to USD OK.')
    else:
        print('Response to USD Failed.')
        exit(1)
    dataUSD = rUSD.json()

    # Hacemos request para obtener el cambio a dolares
    toARS = url.replace('PAPER', 'ARS')
    rARS = requests.get(toARS)
    if rUSD:
        print('Response to ARG OK.')
    else:
        print('Response to ARG Failed.')
        exit(1)
    dataARS = rARS.json()

    # Hacemos request para obtener el cambio a dolares
    toEUR = url.replace('PAPER', 'EUR')
    rEUR = requests.get(toEUR)
    if rUSD:
        print('Response to EUR OK.')
    else:
        print('Response to EUR Failed.')
        exit(1)
    dataEUR = rEUR.json()

    # Formateamos el json
    json.dumps(dataUSD, indent=3)
    json.dumps(dataARS, indent=3)
    json.dumps(dataEUR, indent=3)

    # Agregamos al array de resultados
    results = []
    results.append(float(dataUSD['Realtime Currency Exchange Rate']['5. Exchange Rate']))
    results.append(float(dataARS['Realtime Currency Exchange Rate']['5. Exchange Rate']))
    results.append(float(dataEUR['Realtime Currency Exchange Rate']['5. Exchange Rate']))

    print('\nResultados de request')
    print(results)
    print()

    # Cargamos la libreria
    libconversion = ctypes.CDLL('./lib/libconverter.so')

    # Definimos los tipos de args de la función
    libconversion._convert.argtypes = (ctypes.c_float, ctypes.c_float,)

    # Definimos el tipo de retorno de la función convert
    libconversion._convert.restype = ctypes.c_float

    # Creamos la función factorial que hace de wrapper para llamar a la función en C
    def convert(num, cant):
        return libconversion._convert(num, cant)

    # Finalmente llamamos a la función
    print('La conversión de %s a USD es:' % crypto)
    print(convert(results[0], cant))
    
    print('La conversión de %s a ARS es:' % crypto)
    print(convert(results[1], cant))
    
    print('La conversión de %s a EUR es:' % crypto)
    print(convert(results[2], cant))


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("\nDebe ingresar un valor entero o de punto flotante como argumento\n")
        exit(1)
    
    # Tomamos el argumento ingresado por el usuario como la cantidad a convertir
    cant = float(sys.argv[1])
    
    # Ejecutamos la función de conversión
    CryptoCalc(cant)
    
      
