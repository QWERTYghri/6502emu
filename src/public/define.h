/*
 * define.h
 *
 * File used to store macros and important values
 */

#ifndef DEFINE_H
#define DEFINE_H

typedef int _;

/* Errors */
#define ERROR_NONEXISTENT ( "ERROR: Invalid Option\n" )
#define ERROR_INVALID ( "Invalid: \"%s\"\n" )
#define ERROR_GETOPT ( "ERROR: Argument Failed\n" )
#define ERROR_NOARG ( "ERROR: No arguments given\n" )

#define ERROR_FILE ( "ERROR: Failed to access file\n" )
#define ERROR_LOGFILE ( "ERROR: Failed to create logfile\n" )
#define ERROR_TOOBIG ( "ERROR: File is too big, must be less than 64K\n" )

#define ERROR_ADDRESS ( "ERROR: Specified address must be from 0 - 65535\n" )
#define ERROR_CLOCK ( "ERROR: Clock speed is less than 0 hertz\n" )

/* Buffer Sizes */
#define MAX_FILEQUE ( 15 )

/* Numbers */
#define START_STACK ( ( uint8_t ) 0x100 )
#define MAX_16_BIT ( ( uint16_t ) 0xFFFF )
#define START_ADDRESS ( ( uint16_t) 0x1FF )
#define CLOCK_SPEED ( 1000000 )
#define MICROSECOND ( 1000000 )
#define NEG_FLAG_BIT ( 0x80 )

/* Other */
#define BASE_10 ( 10 )
#define STATUS_TEXT ( "Status:\n\tA : $%X | X : $%X | Y : $%X\n\tSP: $%X\t\tPC : $%X\n" \
		      "\tFLAG : $%X\tINST : $%X\n\n\tCYCLE : %d" )

#endif /* END */
