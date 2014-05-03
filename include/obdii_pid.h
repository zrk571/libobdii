/**
 * \file obdii_pid.h
 * \brief LibOBDII pid helper header file
 * \author Pierre LEROY <leroy.pierre1@gmail.com>
 * \version 0.2 
 * \date December 31 2013
 *
 * PID  header file of OBDII lib.
 * 
 */

#ifndef _obdii_pid_h_
#define _obdii_pid_h_

#include<stdlib.h>
#include<stdio.h>

#include"obdii_type.h"
#include"obdii_helper.h"


/**
 * OBDII Pids definition.
 */
#define SUPPORTED_PIDS_1         0
#define ENGINE_LOAD              1
#define ENGINE_RPM               2
#define ENGINE_OIL_TEMP          3
#define TEMP_COOLANT             4
#define TEMP_AIR_INTAKE          5
#define PRESSURE_FUEL_RAIL       6
#define PRESSURE_INTAKE_MANIFOLD 7
#define VEHICULE_SPEED           8
#define TIMING_ADVANCE           9
#define MASS_AIR_FLOW            10
#define THROTTLE_POSITION        11


extern obdii_pid standard_pid_list[12];


#endif
