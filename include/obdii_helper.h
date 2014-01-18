/**
 * \file obdii_helper.h
 * \brief LibOBDII pid helper header file
 * \author Pierre LEROY <leroy.pierre1@gmail.com>
 * \version 0.2 
 * \date December 31 2013
 *
 * PID helpers header file of OBDII lib.
 * 
 */


#ifndef _obdii_helper_h_
#define _obdii_helper_h_

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
         
/* Some constants */
#define C_MAF 0.00132276
#define C_INTAKE_PRESSURE 0.14504
#define C_RPM 4
#define C_SPEED 1.609


/**
 * \fn Convert HEX value into Integer. 
 * \brief Convert HEX value into Integer.
 *
 * \param data to convert.
 *
 * \return converted hex value.
 */
int _hex_to_int(char* data);


/**
 * \fn Convert time into min. 
 * \brief Convert time into min.
 *
 * \param data to convert.
 *
 * \return converted time in min.
 */
int convert_to_min(char* data);


/**
 *
 *
 *
 */
double maf(char* data);


/**
 *
 *
 *
 */
double throttle_position(char* data);


/**
 *
 *
 *
 */
double intake_pressure(char* data);


/**
 *
 *
 *
 */
double rpm(char* data);


/**
 *
 *
 *
 */
double speed(char* data);


/**
 *
 *
 *
 */
double percent_scale(char* data);


/**
 *
 *
 *
 */
double ignition_timming_advance(char* data);


/**
 *
 *
 *
 */
double coolant_temperature(char* data);


/**
 *
 *
 *
 */
double fuel_trim_percent(char* data);


#endif
