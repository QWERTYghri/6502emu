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

/*
 * ** NOTE **
 * "write" and "read" functions are not the same as fetch, fetch handles clock differences and
 * other functions.
 */

/* Write to memory */
void
write ( cpu* processor, uint16_t address, uint8_t data )
{
	processor -> memory[address] = data;
}

/* Read from memory */
uint8_t
read ( cpu* processor, uint16_t address )
{
	return processor -> memory[address];
}

/****************************************/

/* FETCH byte from memory */
uint8_t
fetch ( cpu* processor, int32_t* cycles )
{
	uint8_t data = processor -> memory[processor -> pc];
	processor -> pc++;
	*cycles--;
	
	return data;
}

/* Change bit in CPU flag, why do it this way? I am not remembering the bit order */
/* [CZIDBVN] */
void
setFlag ( cpu* processor, uint8_t place, uint8_t value )
{
	uint8_t* status = &processor -> status;
	uint8_t mask = 1 << place;
	
	*status = ( ( *status & ~mask ) | ( value << place ) );
}

uint8_t
getFlag ( cpu* processor, uint8_t place )
{
	uint8_t* status = &processor -> status;
	return ( *status >> place ) & 0x01;
}

/* Special flag changes */

/* Set zero and negative flag according to register value */
void
setZeroNegative ( cpu* processor, uint8_t data )
{
	setFlag ( processor, FLAG_Z, ( data == 0 ) ? 1 : 0 );
	setFlag ( processor, FLAG_N, ( ( data & NEG_FLAG_BIT ) > 0 ) ? 1 : 0 );
}

/* Potential instructions */
void
adc ( cpu* processor, uint8_t data )
{
	uint16_t sum = processor -> a;
	uint8_t same = !( ( processor -> a ^ data ) & NEG_FLAG_BIT );
	
	sum += data;
	sum += getFlag ( processor, FLAG_C );
	
	processor -> a = ( sum & 0xFF );
	setZeroNegative ( processor, processor -> a );
	setFlag ( processor, FLAG_C, ( sum > 0xFF ) ? 1 : 0 );
	setFlag (
		processor,
		FLAG_V,
		( same && ( ( processor -> a ^ data) & NEG_FLAG_BIT ) ) ? 1 : 0
	);
}

void
execute ( cpu* processor, int32_t cycles )
{
	while ( cycles > 0 )
	{
		uint8_t opcode = fetch ( processor, &cycles );
		
		switch ( opcode )
		{
			case OP_ADC_IMM:
				adc ( processor, fetch ( processor, &cycles ) );
				cycles = -1;
				break;
			case OP_ADC_ZP:
					
				
				break;
			case OP_ADC_ZPX:
				break;
			case OP_ADC_AB:
				break;
			case OP_ADC_ABX:
				break;
			case OP_ADC_ABY:
				break;
			case OP_ADC_INX:
				break;
			case OP_ADC_INY:
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
			opcode
		);
	}
}



