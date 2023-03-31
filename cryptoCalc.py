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
    dataUSD = rUSD.json()

    # Hacemos request para obtener el cambio a dolares
    '''
    toARS = url.replace('PAPER', 'ARS')
    rARS = requests.get(toARS)
    if rUSD:
        print('Response to ARG OK.')
    else:
        print('Response to ARG Failed.')
    dataARS = rARS.json()

    # Hacemos request para obtener el cambio a dolares
    toEUR = url.replace('PAPER', 'EUR')
    rEUR = requests.get(toEUR)
    if rUSD:
        print('Response to EUR OK.')
    else:
        print('Response to EUR Failed.')
    dataEUR = rEUR.json()
    '''

    # Imprimimos el json
    #print(json.dumps(dataUSD, indent=3))
    #print(json.dumps(dataARS, indent=3))
    #print(json.dumps(dataEUR, indent=3))

    # Hacemos la conversión
    results = float(dataUSD['Realtime Currency Exchange Rate']['5. Exchange Rate'])
    #np.append(results, float(dataUSD['Realtime Currency Exchange Rate']['5. Exchange Rate']))
    #np.append(results, float(dataARS['Realtime Currency Exchange Rate']['5. Exchange Rate']))
    #np.append(results, float(dataEUR['Realtime Currency Exchange Rate']['5. Exchange Rate']))

    print('Resultados de conversión')
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
    print(convert(results, cant))


if __name__ == '__main__':
    # Tomamos el argumento ingresado por el usuario como la cantidad a convertir
    cant = float(sys.argv[1])
    
    # Ejecutamos la función de conversión
    CryptoCalc(cant)
    
      
