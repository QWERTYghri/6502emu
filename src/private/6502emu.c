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
read ( cpu* processor, int32_t* cycles, uint16_t address )
{
	#pragma GCC diagnostic ignored "-Wunused-value"
	*cycles--;
	return processor -> memory[address];
}

uint16_t
readWord ( cpu* processor, int32_t* cycles, uint16_t address )
{
	uint8_t low = read ( processor, cycles, address );
	uint8_t high = read ( processor, cycles, address + 1 );
	
	return low | ( high << 8 );
}

/****************************************/

/* FETCH byte from memory */
uint8_t
fetch ( cpu* processor, int32_t* cycles )
{
	uint8_t data = processor -> memory[processor -> pc];
	
	#pragma GCC diagnostic ignored "-Wunused-value"
	processor -> pc++;
	*cycles--;
	
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

/* Change bit in CPU flag, why do it this way? I am not remembering the bit order */
/* [CZIDBVN] */
static void
setFlag ( cpu* processor, uint8_t place, uint8_t value )
{
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

/* Special flag changes */
/* Set zero and negative flag according to register value */
static void
setZeroNegative ( cpu* processor, uint8_t data )
{
	setFlag ( processor, FLAG_Z, ( data == 0 ) ? 1 : 0 );
	setFlag ( processor, FLAG_N, ( ( data & NEG_FLAG_BIT ) > 0 ) ? 1 : 0 );
}

/* -- Address Modes -- */
/* Note
 * Some address modes aren't listed
 * Some address modes may have some issues
 */
 
/* Fetch address within $255 */
uint8_t
zeroPage ( cpu* processor, int32_t* cycles )
{
	return read ( processor, cycles, fetch ( processor, cycles ) );
}

/* Same as ZeroPage but + X register */
uint8_t
zeroPageX ( cpu* processor, int32_t* cycles )
{
	return read ( processor, cycles, ( fetch ( processor, cycles ) ) + processor -> x );
}

/* Same as ZeroPage but + Y register */
uint8_t
zeroPageY ( cpu* processor, int32_t* cycles )
{
	return read ( processor, cycles, ( fetch ( processor, cycles ) ) + processor -> x );
}

/* Return 16 bit word for address */
uint16_t
absolute ( cpu* processor, int32_t* cycles )
{
	return fetchWord ( processor, cycles );
}

/* Return 16 bit word for address, but + X register */
uint16_t
absoluteX ( cpu* processor, int32_t* cycles )
{
	return ( uint16_t ) ( fetchWord ( processor, cycles ) + processor -> x );
}

/* Return 16 bit word for address, but + Y register */
uint16_t
absoluteY ( cpu* processor, int32_t* cycles )
{
	return ( uint16_t ) ( fetchWord ( processor, cycles ) + processor -> y );
}

uint16_t
indirectX ( cpu* processor, int32_t* cycles )
{
	uint8_t pageAddress = fetch ( processor, cycles );
	pageAddress += processor -> x;
	
	#pragma GCC diagnostic ignored "-Wunused-value"
	*cycles--;
	
	return readWord ( processor, cycles, pageAddress );
}

uint16_t
indirectY ( cpu* processor, int32_t* cycles )
{
	uint8_t pageAddress = fetch ( processor, cycles );
	uint16_t address = readWord ( processor, cycles, pageAddress );
	
	return address + processor -> y;
}

/* Potential instructions */
static void
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

static void
and ( cpu* processor, uint8_t data )
{
	processor -> a &= data;
	setZeroNegative ( processor, processor -> a );
}

/* Execute program in memory */
void
execute ( cpu* processor, int32_t cycles )
{
	while ( cycles > 0 )
	{
		uint8_t opcode = fetch ( processor, &cycles );
		
		switch ( opcode )
		{
			/* ADC Instructions */
			/* Honestly, do not even asking about the repeating code */
			case OP_ADC_IMM:
				adc ( processor, fetch ( processor, &cycles ) );
				break;
			case OP_ADC_ZP:
				adc ( processor, zeroPage ( processor, &cycles ) );
				break;
			case OP_ADC_ZPX:
				adc ( processor, zeroPageX ( processor, &cycles ) );
				break;
			case OP_ADC_AB:
				adc (
					processor,
					read ( processor, &cycles, absolute ( processor, &cycles ) )
				);
				break;
			case OP_ADC_ABX:
				adc (
					processor,
					read ( processor, &cycles, absoluteX ( processor, &cycles ) )
				);
				break;
			case OP_ADC_ABY:
				adc (
					processor,
					read ( processor, &cycles, absoluteY ( processor, &cycles ) )
				);
				break;
			case OP_ADC_INX:
				adc (
					processor,
					read ( processor, &cycles, indirectX ( processor, &cycles ) )
				);
				break;
			case OP_ADC_INY:
				adc (
					processor,
					read ( processor, &cycles, indirectY ( processor, &cycles ) )
				);
				break;
			
			/* AND Instructions */
			case OP_AND_IMM:
				and ( processor, fetch ( processor, &cycles ) );
				break;
			case OP_AND_ZP:
				and ( processor, zeroPage ( processor, &cycles ) );
				break;
			case OP_AND_ZPX:
				and ( processor, zeroPageX ( processor, &cycles ) );
				break;
			case OP_AND_AB:
				and ( processor, absolute ( processor, &cycles ) );
				break;
			case OP_AND_ABX:
				and ( processor, absoluteX ( processor, &cycles ) );
				break;
			case OP_AND_ABY:
				and ( processor, absoluteY ( processor, &cycles ) );
				break;
			case OP_AND_INX:
				and ( processor, indirectX ( processor, &cycles ) );
				break;
			case OP_AND_INY:
				and ( processor, indirectY ( processor, &cycles ) );
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



