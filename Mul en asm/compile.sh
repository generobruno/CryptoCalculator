#!/bin/bash

OUTDIR=./out
BINDIR=./bin

if [ ! -d "$OUTDIR" ]; then
	mkdir "$OUTDIR"
else
	rm "$OUTDIR"/*
fi

if [ ! -d "$BINDIR" ]; then
	mkdir "$BINDIR"
else
	rm "$BINDIR"/*
fi


nasm -f elf32 -d ELF_TYPE asm_io.asm
mv asm_io.o ./out/

nasm -f elf32 mul.asm
mv mul.o ./out/

gcc -o mul ./out/mul.o -m32 driver.c ./out/asm_io.o
mv ./mul ./bin/
