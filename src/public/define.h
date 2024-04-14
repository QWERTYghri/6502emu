/*
 * define.h
 *
 * File used to store macros and important values
 */

/* Errors */
#define ERROR_NONEXISTENT ( "ERROR: Invalid Option\n" )
#define ERROR_INVALID ( "Invalid: \"%s\"\n" )
#define ERROR_GETOPT ( "ERROR: Argument Failed\n" )

#define ERROR_FILE ( "ERROR: Failed to access file\n" )
#define ERROR_LOGFILE ( "ERROR: Failed to create logfile\n" )

#define ERROR_ADDRESS ( "ERROR: Specified address must be from 0 - 65535\n" )
#define ERROR_CLOCK ( "ERROR: Clock speed is less than 0 hertz\n" )

/* Buffer Sizes */
#define MAX_FILEQUE ( 15 )

/* Numbers */
#define MAX_16_BIT ( ( uint16_t ) 0xFFFF )
#define START_ADDRESS ( ( uint16_t) 0x1FF )
#define CLOCK_SPEED ( 1000000 )

/* Other */
#define BASE_10 ( 10 )
