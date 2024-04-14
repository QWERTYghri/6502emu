/*
 * main.c
 *
 * Main program file for the program
 */
 
/* LIBC */
#include <stdio.h>
#include <stdint.h>

/* POSIX */
#include <getopt.h>

/* Local */
#include "./public/6502emu.h"

static int32_t
parseOptions ( int32_t argc, char** argv )
{
	/* Get Argument Options */
	struct options commandOptions[] =
	{
		{ "open",	required_argument, NULL, 'o' },
		{ "address",	no_argument,	   NULL, 'a' },
		{ "clock",	no_argument,	   NULL, 'c' },
		{ NULL,		0,		   NULL, 0 }	
	};
}

int
main ( int argc, char** argv )
{
	if ( parseOptions ( argc, argv ) )
		exit ( EXIT_SUCCESS );

	return 0;
}
