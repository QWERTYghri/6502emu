/*
 * 6502emu.c
 *
 * 6502 Emulator Source File
 * File to store most of the important parts of the emulator
 */
 
/* libc */ 
#include <stdint.h>
#include <stdlib.h>

/* local */
#include "../public/define.h"
#include "../public/6502emu.h"

/* Make CPU struct */
cpu*
newcpu ( uint16_t pc )
{
	cpu* returnCpu = calloc ( 1, sizeof ( cpu ) );
	
	if ( returnCpu == NULL )
		return NULL;
		
	/* Initialize CPU */
	returnCpu -> pc = pc;
	returnCpu -> sp = START_STACK;
	
	returnCpu -> memory = calloc ( MAX_16_BIT, sizeof ( uint8_t ) );
	
	return returnCpu;
}

/* Free CPU Struct */
void
delcpu ( cpu* processor )
{
	free ( processor );
}

/*
 * ** NOTE **
 * "write" and "read" functions are not the same as fetch, fetch handles clock differences and
 * other functions.
 */

/* Write to memory */
void write ( cpu* processor, uint16_t address, uint8_t data )
{
	processor -> memory[address] = data;
}

/* Read from memory */
uint8_t read ( cpu* processor, uint16_t address )
{
	return processor -> memory[address];
}

/****************************************/

/* FETCH byte from memory */
uint8_t fetch ( cpu* processor, uint32_t* cycles )
{
	uint8_t data = processor -> memory[processor -> pc];
	processor -> pc++;
	*cycles--;
	
	return data;
}

void execute ( cpu* processor, uint32_t cycles )
{
	while ( cycles > 0 )
	{
		uint8_t opcode = fetch ( processor, &cycles );
		
		switch ( opcode )
		{
			case 10:
				break;
		}
	}
}



