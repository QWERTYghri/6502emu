/*
 * main.c
 *
 * Main program file for the program
 */
 
/* LIBC */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* POSIX */
#include <getopt.h>

/* Local */
#include "./public/6502emu.h"
#include "./public/define.h"

/* Global Variables */

/* File Que List */
FILE* fileQue[MAX_FILEQUE] = { 0 };
int32_t queIndex = 0;

/* Emulator Options */
FILE* logFile = NULL;
uint32_t startAddress = START_ADDRESS;
uint64_t clockSpeed = CLOCK_SPEED;

/*****************************************/

/* Error with Message */
static void
exitMessage ( char* message )
{
	fprintf ( stderr, "%s\n", message );
	exit ( EXIT_FAILURE );
}

/* Close Files */
static void
closeFiles ( void )
{
	for ( int32_t i = 0; i < MAX_FILEQUE; i++ )
	{
		if ( fileQue[i] != 0 )
			fclose ( fileQue[i] );
	}
	
	if ( logFile )
		fclose ( logFile );
}

/* Parse Options */
static int32_t
parseOptions ( int32_t argc, char** argv )
{
	/* Get Argument Options */
	struct option commandOptions[] =
	{
		{ "open",	required_argument, NULL, 'o' },
		{ "address",	required_argument, NULL, 'a' },
		{ "clock",	required_argument, NULL, 'c' },
		{ "log",	required_argument, NULL, 'l' },
		{ NULL,		0,		   NULL, 0 }
	};
	
	int32_t code;
	int32_t index = 0;
	
	if ( argc == 1 )
		exitMessage ( ERROR_NOARG );
	
	while ( ( code = getopt_long ( argc, argv, "o:a:c:l:", commandOptions, &index ) ) != -1 )
	{		
		switch ( code )
		{
			/* Open file and add it to que */
			case 'o':
				fileQue[queIndex] = fopen ( optarg, "r+" );
				
				if ( fileQue[queIndex] == NULL )
					exitMessage ( ERROR_FILE );
				
				break;
			
			/* Get specified address */
			case 'a':
				startAddress = strtol ( optarg, NULL, BASE_10 );
				
				if ( startAddress > MAX_16_BIT )
					exitMessage ( ERROR_ADDRESS );
				
				break;
				
			/* Get clock speed in hertz */
			case 'c':
				clockSpeed = strtol ( optarg, NULL, BASE_10 );
				
				if ( clockSpeed > CLOCK_SPEED )
					exitMessage ( ERROR_CLOCK );
				
				break;
				
			/* Specify output file name */
			case 'l':
				if ( ( logFile = fopen ( optarg, "w+" ) ) == NULL )
					exitMessage ( ERROR_LOGFILE );
				
				break;
			default:
				fprintf ( stderr, ERROR_GETOPT );
				
				return -1;
		}
	}
	
	if ( optind < argc )
	{
		fprintf ( stderr, ERROR_NONEXISTENT );
		
		while ( optind < argc )
			fprintf ( stderr, ERROR_INVALID, argv[optind++] );
		printf ( "\n" );
		
		return -1;
	}
	
	return 0;
}

/* Execute list of object files with the 6502 emulator */
static void
executeFiles ( void )
{

}

int
main ( int argc, char** argv )
{
	if ( parseOptions ( argc, argv ) )
		exit ( EXIT_SUCCESS );

	executeFiles ();

	closeFiles ();	

	return 0;
}
