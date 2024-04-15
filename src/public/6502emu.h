/*
 * 6502emu.h
 *
 * 6502 Emulator Header File
 * File to store most of the important parts of the emulator
 */
 
#ifndef EMU_6502_H
#define EMU_6502_H

/* libc */
#include <stdint.h>

/* local */
#include "./define.h"

enum
{
	LDA
};

typedef struct
{
	/* Memory Indexing */
	uint16_t pc;
	uint8_t sp;
	
	/* Registers and status */
	uint8_t a, x, y, status; /* *NOTE* [CZIDBON] */
	
	/* Memory */
	uint8_t* memory;
} cpu;

/* CPU Create functions */
cpu* newcpu ( uint16_t pc );
void delcpu ( cpu* processor );

/* -- CPU Data functions -- */
/* Data Handling (No cycle decrement) */
void write ( cpu* processor, uint16_t address, uint8_t data );
uint8_t read ( cpu* processor, uint16_t address );

/* Fetch Data */
uint8_t fetch ( cpu* processor, uint32_t* cycles );

/* Execution */
void execute ( cpu* processor, uint32_t cycles );


#endif /* End */
