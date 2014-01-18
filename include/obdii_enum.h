/**
 * \file obdii_enum.h
 * \brief LibOBDII enum file
 * \author Pierre LEROY <leroy.pierre1@gmail.com>
 * \version 0.2 
 * \date December 31 2013
 *
 * Enum file of OBDII lib.
 * 
 */


#ifndef _obdii_enum_h_
#define _obdii_enum_h_

#include<stdlib.h>
#include<stdio.h>


/**
 * \enum obdii_state
 * \brief Describes obdii_handler connection state.
 *
 * This enumeration is used to describe the current connection state between an ECU and the interface.
 */
typedef enum obdii_state{
  ONLINE,  /*!< Connection is UP */
  OFFLINE, /*!< Connection is DOWN */
  UNKNOWN  /*!< Unable to retrieve connection state */
} obdii_state;


/**
 * \enum obdii_speed 
 * \brief Describes obdii_handler connection speed
 *
 * This enumeration is used to define serial connection speed. (Usualy set on STANDARD).
 */
typedef enum obdii_speed{
  LOW      = B9600,   /*!< 9600 Bauds */
  MEDIUM   = B19200,  /*!< 19200 Bauds */
  STANDARD = B38400,  /*!< 38400 Bauds */
  HIGH     = B115200, /*!< 1152000 Bauds */
} obdii_speed;


#endif
