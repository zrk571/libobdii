/**
 * \file obdii_type.h
 * \brief LibOBDII header file
 * \author Pierre LEROY <leroy.pierre1@gmail.com>
 * \version 0.2 
 * \date December 31 2013
 *
 * Type header file of OBDII lib.
 * 
 */


#ifndef _obdii_type_h_
#define _obdii_type_h_

#include<stdlib.h>
#include<stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

#include"obdii_enum.h"

/* OBDII COMMAND WORDS */
#define OBDII_INITIALIZE "ATZ"
#define OBDII_ECHO_OFF   "AT E0"
#define OBDII_INITCAN    "01 00"
#define OBDII_CLOSE      "ATZ"
#define OBDII_EOC        "\r\n"


/* OBDII RETURN CODES */
#define OBDII_NODATA -1
#define OBDII_ERROR  -2
#define OBDII_OK      1


/* OBDII MESSAGES */
#define OBDII_MSG_VERSION           "Unknown"

#define OBDII_MSG_NODATA            "NODATA"
#define OBDII_MSG_ERROR             "ERROR"
#define OBDII_MSG_OK                "OK"
#define OBDII_MSG_UNABLE_TO_CONNECT "UNABLE TO CONNECT"


/* OBDII START RANGE */
#define OBDII_PID_RANGE_1 "0100"
#define OBDII_PID_RANGE_2 "0120"
#define OBDII_PID_RANGE_3 "0140"
#define OBDII_PID_RANGE_4 "0160"


/**
 * \struct This defines vars used to handle communication data.
 * \brief This defines vars used to handle all needed communication data.
 *
 */
typedef struct obdii_handler{
  char* device;                 /*!< Device descriptor path */
  int descriptor;               /*!< Device descriptor */
  char version[64];             /*!< Device ELM version */
  unsigned short int timeout;   /*!< Timeout in seconds */
  unsigned short int max_retry; /*!< Number of retry */
  obdii_speed speed;            /*!< Dialog speed */
  obdii_state state;            /*!< Dialog state */
  struct termios tty;           /*!< termios old context */
  struct termios old_context;   /*!< termios current context */
} obdii_handler;


/**
 * \struct This defines vars used to describe ECU PID.
 * \brief  This defines vars used to define all needed data for an ECU PID.
 * 
 */
typedef struct obdii_pid{
  unsigned short int pid;           /*!< PID Number */
  const char* code;                 /*!< PID Code */
  const short int range;            /*!< PID Range */
  const char* name;                 /*!< PID name */
  const char* unit;                 /*!< PID units */
  void (*fct_helper) (char* data); /*!< Pointer to helper function which need to be used */
} obdii_pid;


/**
 * \struct This defines vars used to define ECU request.
 * \brief This defines vars used to define ECU request.
 *
 */
typedef struct obdii_request{
  obdii_pid* pid; /*!< Pointer to a PID strcuture */
} obdii_request;


/**
 * \struct This defines vars used to define ECU response.
 * \biref This defines vars used to define ECU response.
 */
typedef struct obdii_response{
  obdii_pid* pid; /*!< Pointer to a PID structure */
  char* buffer;   /*!< ECU response */
  char* err_str;  /*!< ECU error response */
} obdii_response;


/**
 * \struct This defines vars used to define ECU available PID.
 * \biref This defines vars used to define ECU available PID for each range.
 */
typedef struct obdii_available_pid{
  int range[10];   /*!< Tab for each PID range */
} obdii_available_pid;

#endif
