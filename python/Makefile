############################################################################################################
# 
# 	Makefile CryptoCalculator (Python)
# 
############################################################################################################

# Carpetas
SRC := src
ASM := $(SRC)/ASM
LIB := lib

# Compilador
CC = 			gcc
CFLAGS 	= 		-Wall -Werror -pedantic -Wextra -Wconversion -std=gnu11

# Target
default: libconverter

all: clean default

##########################################################################################################
##									Creamos los objetos y librerías



mul.o: 
	nasm -f elf64 $(ASM)/mul.asm

convertCrypto: $(SRC)/convertCrypto.c mul.o
	$(CC) -c  $(SRC)/convertCrypto.c $(CFLAGS) -o $(SRC)/protocols.o

# libconverter
libconverter: convertCrypto $(SRC)/protocols.o mul.o
	@mkdir -p lib
	$(CC)  -shared -W $(ASM)/mul.o $(SRC)/protocols.o -o $(LIB)/libconverter.so
	@echo "\n"Build Donde!"\n"

#########################################################################################################
# Eliminar todos los objetos, dependencias y ejecutables
clean:
	rm $(SRC)/*.o
	rm $(LIB)/*
	@echo "\n"Limpieza terminada!
