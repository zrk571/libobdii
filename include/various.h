/**
 * \file various.h
 * \brief LibOBDII various helpers header file
 * \author Pierre LEROY <leroy.pierre1@gmail.com>
 * \version 0.2 
 * \date December 31 2013
 *
 * Type header file of OBDII lib.
 * 
 */
 

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>


/**
 * \fn Display message into a debug way. 
 * \brief Display message into a debug way.
 *
 * \param message data to display.
 *
 */
void _debug_printf(const char* message);


/**
 * \fn Split a string into tokens delimited with char c. 
 * \brief Split a string into tokens delimited with char c.
 *
 * \param c token delimiter. 
 * \param message data to display.
 *
 * \return tab endded with NULL value. 
 */
char** split_in_array(char c, char* data);


/**
 * \fn reverse bit order from most significant bit to less one. 
 * \brief rever bit order from an unsigned integer from MSB to LSB order.
 *
 * \param num integer to convert
 * \param numBits number of bits to convert.
 *
 * \return number with reversed bit order. 
 */
int msb_to_lsb(unsigned int num, unsigned int numBits);
