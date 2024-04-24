/*
 * 6502emu.c
 *
 * 6502 Emulator Source File
 * File to store most of the important parts of the emulator
 */
 
/* libc */ 
#include <stdio.h>
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

/****************************************/
/* Write to memory */
void
writeByte ( cpu* processor, int32_t* cycles, uint16_t address, uint8_t data )
{
	#pragma GCC diagnostic ignored "-Wunused-value"
	*cycles--;
	processor -> memory[address] = data;
}

/* Read from memory */
uint8_t
readByte ( cpu* processor, int32_t* cycles, uint16_t address )
{
	#pragma GCC diagnostic ignored "-Wunused-value"
	*cycles--;
	return processor -> memory[address];
}

uint16_t
readWord ( cpu* processor, int32_t* cycles, uint16_t address )
{
	uint8_t low = readByte ( processor, cycles, address );
	uint8_t high = readByte ( processor, cycles, address + 1 );
	
	return low | ( high << 8 );
}

/* FETCH byte from memory */
uint8_t
fetchByte ( cpu* processor, int32_t* cycles )
{
	uint8_t data = readByte ( processor, cycles, processor -> pc );
	processor -> pc++;
	
	return data;
}

/* Fetch word (16-bits) */
uint8_t
fetchWord ( cpu* processor, int32_t* cycles )
{
	uint16_t data = processor -> memory[processor -> pc];
	processor -> pc++;
	
	data |= processor -> memory[processor -> pc] << 8;
	processor -> pc++;
	
	cycles -= 2;
	return data;
}

/****************************************/

/* Change bit in CPU flag, why do it this way? I am not remembering the bit order */
/* [CZIDBVN] */
static void
setFlag ( cpu* processor, uint8_t place, uint8_t value )
{
	value = ( value ) ? 1 : 0;

	uint8_t* status = &processor -> status;
	uint8_t mask = 1 << place;
	
	*status = ( ( *status & ~mask ) | ( value << place ) );
}

static uint8_t
getFlag ( cpu* processor, uint8_t place )
{
	uint8_t* status = &processor -> status;
	return ( *status >> place ) & 0x01;
}

/****************************************/
/* Addressing Functions */
/* They mostly all return address values */

/* Notations of this typedef
 * describe an addressing mode that wouldn't really
 * be useful.
 */
 
/* IMPLICIT */
/************/

/* ACCUMULATOR */
/************/

/* ZERO PAGE */
static uint8_t
zeroPage ( cpu* processor, int32_t* cycles )
{
	return fetchByte ( processor, cycles );
}

/* ZERO PAGE X */
static uint8_t
zeroPageX ( cpu* processor, int32_t* cycles )
{
	*cycles--;
	return fetchByte ( processor, cycles ) + processor -> x;
}

/* ZERO PAGE Y */
static uint8_t
zeroPageY ( cpu* processor, int32_t* cycles )
{
	*cycles--;
	return fetchByte ( processor, cycles ) + processor -> y;
}

/* RELATIVE */
/************/

/* ABSOLUTE */
static uint16_t
absolute ( cpu* processor, int32_t* cycles )
{
	return fetchWord ( processor, cycles );
}

/* ABSOLUTE X */
static uint16_t
absoluteX ( cpu* processor, int32_t* cycles )
{
	return fetchWord ( processor, cycles ) + processor -> x;
}

/* ABSOLUTE Y */
static uint16_t
absoluteY ( cpu* processor, int32_t* cycles )
{
	return fetchWord ( processor, cycles ) + processor -> y;
}

/* INDIRECT */
/************/

/* INDIRECT X */
static uint16_t
indirectX ( cpu* processor, int32_t* cycles )
{
	uint8_t page = fetchByte ( processor, cycles );
	uint16_t address = readWord ( processor, cycles, page );
	
	return address + processor -> y;
}

/* INDIRECT Y */
static uint16_t
indirectY ( cpu* processor, int32_t* cycles )
{
	uint8_t page = fetchByte ( processor, cycles );
	page += processor -> x;
	*cycles--;
	
	return readWord ( processor, cycles, page );
}

/****************************************/
/* Instructions */
static void
adcOperation ( cpu* processor, uint8_t data )
{
	uint16_t sum = processor -> a;
	sum += data;
	sum += getFlag ( processor, FLAG_C );
	processor -> a = sum & 0xFF;
	
	setFlag ( processor, FLAG_C, sum > 0xFF );
}

/****************************************/
/* Execute program in memory */

void
execute ( cpu* processor, int32_t cycles )
{
	while ( cycles > 0 )
	{
		uint8_t opcode = fetchByte ( processor, &cycles );
		
		switch ( opcode )
		{
			OP_ADC_IMM:
				
				break;
			OP_ADC_ZP:
			
				break;
			OP_ADC_ZPX:
			
				break;
			OP_ADC_AB:
			
				break;
			OP_ADC_ABX:
			
				break;
			OP_ADC_ABY:
			
				break;
			OP_ADC_INX:
			
				break;
			OP_ADC_INY:
			
				break;
		}
		
		/* Debug Text */
		printf (
			STATUS_TEXT,
			processor -> a,
			processor -> x,
			processor -> y,
			processor -> sp,
			processor -> pc,
			processor -> status,
			opcode,
			0
		);
		
		getchar ();
	}
}



