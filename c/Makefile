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
default: cryptoCalc

all: clean default

cryptoCalc: mul.o
	$(CC) -c -m32 $(SRC)/driver.c -lcurl -o $(SRC)/driver.o
	$(CC) -o cryptoCalc $(SRC)/mul.o -m32 $(SRC)/driver.o $(SRC)/asm_io.o
	@echo "\n"Build terminada!

##########################################################################################################
##								Creamos los objetos y librerías

asm_io.o:
	nasm -f elf32 -d ELF_TYPE $(SRC)/asm_io.asm

mul.o: asm_io.o
	nasm -f elf32 $(SRC)/mul.asm

#########################################################################################################
# Eliminar todos los objetos, dependencias y ejecutables
clean:
	rm $(SRC)/*.o
	@echo "\n"Limpieza terminada!