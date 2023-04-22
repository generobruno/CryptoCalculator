############################################################################################################
# 
# 	Makefile CryptoCalculator (C)
# 
############################################################################################################

# Carpetas
SRC := src
DRIVER := $(SRC)/driver
ASM := $(SRC)/asm
REQS := $(SRC)/requests
UTILS := $(SRC)/utils
INC := inc
CDECL := $(INC)/CDECL
CJSON := $(INC)/CJSON

# Compilador
CC = 			gcc
CFLAGS 	= 		-Wall -Werror -pedantic -Wextra -Wconversion -g -std=gnu11

# Target
default: cryptoCalc

all: clean default

cryptoCalc: mul.o request.o driver.o
	$(CC) -o cryptoCalc -m32 $(DRIVER)/driver.o $(ASM)/asm_io.o $(ASM)/mul.o  
	$(CC) -o requester $(REQS)/request.o $(UTILS)/cJSON.o -lcurl
	@echo "\n"Build terminada!

##########################################################################################################
##								Creamos los objetos y librerías

request.o:
	$(CC) -c $(REQS)/request.c $(CFLAGS) -o $(REQS)/request.o 

driver.o: mul.o cJSON.o
	$(CC) -c -m32 $(DRIVER)/driver.c $(CFLAGS) -o $(DRIVER)/driver.o

asm_io.o:
	nasm -g -f elf32 -d ELF_TYPE $(ASM)/asm_io.asm -o $(ASM)/asm_io.o

mul.o: asm_io.o
	nasm -g -f elf32 $(ASM)/mul.asm -o $(ASM)/mul.o

cJSON.o: 
	$(CC) -c $(UTILS)/cJSON.c $(CFLAGS) -o $(UTILS)/cJSON.o

#########################################################################################################
# Eliminar todos los objetos, dependencias y ejecutables
clean:
	rm $(DRIVER)/*.o
	rm $(ASM)/*.o
	rm $(REQS)/*.o
	rm $(UTILS)/*.o
	rm cryptoCalc
	rm requester
	@echo "\n"Limpieza terminada!