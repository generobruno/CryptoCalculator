############################################################################################################
# 
# 	Makefile CryptoCalculator
# 
############################################################################################################

# Carpetas
SRC := src
LIB := lib

# Compilador
CC = 			gcc
CFLAGS 	= 		-Wall -Werror -pedantic -Wextra -Wconversion -std=gnu11

# Target
default: libconverter

all: clean default

##########################################################################################################
##									Creamos los objetos y librerías

# convertCrypto
convertCrypto: $(SRC)/convertCrypto.c
	$(CC) -c $(SRC)/convertCrypto.c $(CFLAGS) -o $(SRC)/protocols.o

# libconverter
libconverter: convertCrypto $(SRC)/protocols.o
	@mkdir -p lib
	$(CC) -shared -W -o $(LIB)/libconverter.so $(SRC)/protocols.o
	@echo "\n"Build Donde!"\n"

#########################################################################################################
# Eliminar todos los objetos, dependencias y ejecutables
clean:
	rm $(SRC)/*.o
	rm $(LIB)/*
	@echo "\n"Limpieza terminada!