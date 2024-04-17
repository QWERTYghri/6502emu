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

/* All instructions... */
enum instructions
{
	/* ADC Instructions */
	OP_ADC_IMM = 0x69,
	OP_ADC_ZP  = 0x65,
	OP_ADC_ZPX = 0x75,
	OP_ADC_AB  = 0x6D,
	OP_ADC_ABX = 0x7D,
	OP_ADC_ABY = 0x79,
	OP_ADC_INX = 0x61,
	OP_ADC_INY = 0x71,
	
	/* AND Instructions */
	OP_AND_IMM = 0x29,
	OP_AND_ZP  = 0x25,
	OP_AND_ZPX = 0x35,
	OP_AND_AB  = 0x2D,
	OP_AND_ABX = 0x3D,
	OP_AND_ABY = 0x39,
	OP_AND_INX = 0x21,
	OP_AND_INY = 0x31,

	/* ASL Instructions */
	OP_ASL_ACC = 0x0A,
	OP_ASL_ZP  = 0x06,
	OP_ASL_ZPX = 0x16,
	OP_ASL_AB  = 0x0E,
	OP_ASL_ABX = 0x1E,
	
	/* BCC Instructions */
	OP_BCC_REL = 0x90,
	
	/* BCS Instructions */
	OP_BCS_REL = 0xB0,
	
	/* BEQ Instructions */
	OP_BEQ_REL = 0xF0,
	
	/* BIT Instruction */
	OP_BIT_ZP  = 0x24,
	OP_BIT_AB  = 0x2C,
	
	/* BMI Instruction */
	OP_BMI_REL = 0x30,
	
	/* BNE Instruction */
	OP_BNE_REL = 0xD0,
	
	/* BPL Instruction */
	OP_BPL_REL = 0x10,
	
	/* BRK Instruction */
	OP_BRK_IMP = 0x00,
	
	/* BVC Instruction */
	OP_BVC_REL = 0x50,
	
	/* BVS Instruction */
	OP_BVS_REL = 0x70,
	
	/* CLC Instruction */
	OP_CLC_IMP = 0x18,
	
	/* CLD Instruction */
	OP_CLD_IMP = 0xD8,
	
	/* CLI Instruction */
	OP_CLI_IMP = 0x58,
	
	/* CLV Instruction */
	OP_CLV_IMP = 0xB8,
	
	/* CMP Instruction */
	OP_CMP_IMM = 0xC9,
	OP_CMP_ZP  = 0xC5,
	OP_CMP_ZPX = 0xD5,
	OP_CMP_AB  = 0xCD,
	OP_CMP_ABX = 0xDD,
	OP_CMP_ABY = 0xD9,
	OP_CMP_INX = 0xC1,
	OP_CMP_INY = 0xD1,
	
	/* CPX Instruction */
	OP_CPX_IMM = 0xE0,
	OP_CPX_ZP  = 0xE4,
	OP_CPX_AB  = 0xEC,
	
	/* CPY Instruction */
	OP_CPY_IMM = 0xC0,
	OP_CPY_ZP  = 0xC4,
	OP_CPY_AB  = 0xCC,
	
	/* DEC Instruction */
	OP_DEC_ZP  = 0xC6,
	OP_DEC_ZPX = 0xD6,
	OP_DEC_AB  = 0xCE,
	OP_DEC_ABX = 0xDE,
	
	/* DEX Instruction */
	OP_DEX_IMP = 0xCA,
	OP_DEY_IMP = 0x88,
	
	/* EOR Instruction */
	OP_EOR_IMM = 0x49,
	OP_EOR_ZP  = 0x45,
	OP_EOR_ZPX = 0x55,
	OP_EOR_AB  = 0x4D,
	OP_EOR_ABX = 0x5D,
	OP_EOR_ABY = 0x59,
	OP_EOR_INX = 0x41,
	OP_EOR_INY = 0x51,

	/* INC Instruction */
	OP_INC_ZP  = 0xE6,
	OP_INC_ZPX = 0xF6,
	OP_INC_AB  = 0xEE,
	OP_INC_ABX = 0xFE,

	/* INX Instruction */
	OP_INX_IMP = 0xE8,
	
	/* INY Instruction */
	OP_INY_IMP = 0xC8,
	
	/* JMP Instruction */
	OP_JMP_AB  = 0x4C,
	OP_JMP_IND = 0x6C,
	
	/* JSR Instruction */
	OP_JSR_AB  = 0x20,
	
	/* LDA Instruction */
	OP_LDA_IMM = 0xA9,
	OP_LDA_ZP  = 0xA5,
	OP_LDA_ZPX = 0xB5,
	OP_LDA_AB  = 0xAD,
	OP_LDA_ABX = 0xBD,
	OP_LDA_ABY = 0xB9,
	OP_LDA_INX = 0xA1,
	OP_LDA_INY = 0xB1,
	
	/* LDX Instruction */
	OP_LDX_IMM = 0xA2,
	OP_LDX_ZP  = 0xA6,
	OP_LDX_ZPY = 0xB6,
	OP_LDX_AB  = 0xAE,
	OP_LDX_ABY = 0xBE,

	/* LDY Instruction */
	OP_LDY_IMM = 0xA0,
	OP_LDY_ZP  = 0xA4,
	OP_LDY_ZPX = 0xB4,
	OP_LDY_AB  = 0xAC,
	OP_LDY_ABX = 0xBC,
	
	/* LSR Instruction */
	OP_LSR_ACC = 0x4A,
	OP_LSR_ZP  = 0x46,
	OP_LSR_ZPX = 0x56,
	OP_LSR_AB  = 0x4E,
	OP_LSR_ABX = 0x5E,
	
	/* NOP Instruction */
	OP_NOP_IMP = 0xEA,
	
	/* ORA Instruction */
	OP_ORA_IMM = 0x09,
	OP_ORA_ZP  = 0x05,
	OP_ORA_ZPX = 0x15,
	OP_ORA_AB  = 0x0D,
	OP_ORA_ABX = 0x1D,
	OP_ORA_ABY = 0x19,
	OP_ORA_INX = 0x01,
	OP_ORA_INY = 0x11,
	
	/* PHA Instruction */
	OP_PHA_IMP = 0x48,
	
	/* PHP Instruction */
	OP_PHP_IMP = 0x08,
	
	/* PLA Instruction */
	OP_PLA_IMP = 0x68,
	
	/* PLP Instruction */
	OP_PLP_IMP = 0x28,
	
	/* ROL Instruction */
	OP_ROL_ACC = 0x2A,
	OP_ROL_ZP  = 0x26,
	OP_ROL_ZPX = 0x36,
	OP_ROL_AB  = 0x2E,
	OP_ROL_ABX = 0x3E,

	/* ROR Instruction */
	OP_ROR_ACC = 0x6A,
	OP_ROR_ZP  = 0x66,
	OP_ROR_ZPX = 0x76,
	OP_ROR_AB  = 0x6E,
	OP_ROR_ABX = 0x7E,
	
	/* RTI Instruction */
	OP_RTI_IMP = 0x40,
	
	/* RTS Instruction */
	OP_RTS_IMP = 0x60,
	
	/* SBC Instruction */
	OP_SBC_IMM = 0xE9,
	OP_SBC_ZP  = 0xE5,
	OP_SBC_ZPX = 0xF5,
	OP_SBC_AB  = 0xED,
	OP_SBC_ABX = 0xFD,
	OP_SBC_ABY = 0xF9,
	OP_SBC_INX = 0xE1,
	OP_SBC_INY = 0xF1,

	/* SEC Instruction */
	OP_SEC_IMP = 0x38,
	
	/* SED Instruction */
	OP_SED_IMP = 0xF8,
	
	/* SEI Instruction */
	OP_SEI_IMP = 0x78,
	
	/* STA Instruction */
	OP_STA_ZP  = 0x85,
	OP_STA_ZPX = 0x95,
	OP_STA_AB  = 0x8D,
	OP_STA_ABX = 0x9D,
	OP_STA_ABY = 0x99,
	OP_STA_INX = 0x81,
	OP_STA_INY = 0x91,
	
	/* STX Instruction */
	OP_STX_ZP  = 0x86,
	OP_STX_ZPY = 0x96,
	OP_STX_AB  = 0x8E,
	
	/* STY Instruction */
	OP_STY_ZP  = 0x84,
	OP_STY_ZPX = 0x94,
	OP_STY_AB  = 0x8C,
	
	/* TAX Instruction */
	OP_TAX_IMP = 0xAA,
	
	/* TAY Instruction */
	OP_TAY_IMP = 0xA8,
	
	/* TSX Instruction */
	OP_TSX_IMP = 0xBA,
	
	/* TXA Instruction */
	OP_TXA_IMP = 0x8A,
	
	/* TXS Instruction */
	OP_TXS_IMP = 0x9A,
	
	/* TYA Instruction */
	OP_TYA_IMP = 0x9A
};

enum flags
{
	FLAG_N,
	FLAG_V,
	FLAG_B,
	FLAG_D,
	FLAG_I,
	FLAG_Z,
	FLAG_C
};

/* CPU struct */
typedef struct
{
	/* Memory Indexing */
	uint16_t pc;
	uint8_t sp;
	
	/* Registers and status */
	uint8_t a, x, y, status; /* *NOTE* Status [CZIDBVN] */
	
	/* Memory */
	uint8_t* memory;
} cpu;

/* CPU Create functions */
cpu* newcpu ( uint16_t pc );
void delcpu ( cpu* processor );

/* -- CPU Data functions -- */
/* Data Handling (No cycle decrement) */
void write ( cpu* processor, uint16_t address, uint8_t data );
uint8_t read ( cpu* processor, int32_t* cycles, uint16_t address );
uint16_t readWord ( cpu* processor, int32_t* cycles, uint16_t address );

/* Fetch Data */
uint8_t fetch ( cpu* processor, int32_t* cycles );
uint8_t fetchWord ( cpu* processor, int32_t* cycles );

/* Execution */
void execute ( cpu* processor, int32_t cycles );


#endif /* End */
