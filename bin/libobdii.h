/**
 * \file libobdii.h
 * \brief LibOBDII header file
 * \author Pierre LEROY <leroy.pierre1@gmail.com>
 * \version 0.2 
 * \date December 31 2013
 *
 * Main header file of OBDII lib.
 * This librairy enables to dialog with an ECU and retrieves sensors data through an ELM327 interface via CAN-BUS protocol.
 * 
 */


#ifndef _obdii_h_
#define _obdii_h_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<termios.h>


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

/* Some constants */
#define C_MAF 0.00132276
#define C_INTAKE_PRESSURE 0.14504
#define C_RPM 4
#define C_SPEED 1.609


/**
 * OBDII Pids definition.
 */
#define SUPPORTED_PIDS           0
#define ENGINE_LOAD              1
#define ENGINE_RPM               2
#define ENGINE_UPTIME            3
#define TEMP_COOLANT             4
#define TEMP_AIR_INTAKE          5
#define PRESSURE_FUEL_RAIL       6
#define PRESSURE_INTAKE_MANIFOLD 7
#define VEHICULE_SPEED           8
#define TIMING_ADVANCE           9
#define MASS_AIR_FLOW            10
#define THROTTLE_POSITION        11


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
  const char* name;                 /*!< PID name */
  const char* unit;                 /*!< PID units */
  void* (*fct_helper) (char* data); /*!< Pointer to helper function which need to be used */
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
 * \fn obdii_handler* obdii_get_handler(char* device, obdii_speed speed, unisgned short int timeout, unsigned short int retry) 
 * \brief Get a new handler to communicate with the ECU.
 *
 * \param device path to the interface descriptor (ie: /dev/ttyUSB0).
 * \param speed communication speed.
 * \param timeout delay beforce timeout.
 * \param retry Number of allowed retry.
 *
 * \return a macro descriptor which allow to dialog with the ECU.
 */
obdii_handler* obdii_get_handler(char* device, obdii_speed speed, unsigned short int timeout, unsigned short int retry);


/**
 * \fn Returns a well malloced obdii_response.
 * 
 * \return a well malloced obdii_response.
 */
obdii_response* obdii_malloc_response();


/**
 * \fn Returns an array of all eligible devices.
 * \brief Returns an array of all eligible devices..
 * 
 * \param device_count pointer to an addresse which will contain the exact number of devices.
 * \return an array of all eligible devices.
 */
char** obdii_eligible_device_list(ssize_t* device_count);


/**
 * \fn Initialize connection with the ECU.
 * \brief Initialize the connection between the ECU and the ELM interface.
 *
 * \param handler obdii handler.
 */
short int obdii_init(obdii_handler* handler);


/**
 * \fn Close connection with the ECU.
 * \brief Close the connection between the ECU and the ELM interface.
 *
 * \param handler obdii handler.
 */
short int obdii_close(obdii_handler* handler);


/**
 * \fn Free malloced handler.
 * \brief Free malloced memory used as handler.
 *
 * \param handler obdii handler.
 */
short int obdii_free_handler(obdii_handler* handler);


/**
 * \fn Suitable to free obdii_response.
 * \brief Free malloced memory used as obdii_response.
 *
 * \param response obdii response. 
 */
short int obdii_free_response(obdii_response* response);


/**
 * \fn Suitable to free obdii_request.
 * \brief Free malloced memory used as obdii_response.
 *
 * \param request obdii request. 
 */
short int obdii_free_request(obdii_request* request);


/**
 * \fn Ask ECU with a specific request.
 * \brief Ask ECU with a specific obdii request and put response into obdii_response.
 *
 * \param request obdii request.
 * \param response obdii response.   
 * 
 * \return request status  > 0 OK ; <0 KO  
 */
short int obdii_ask(obdii_handler* handler, obdii_request* request, obdii_response* response);


/**
 * \fn Send raw data to ECU.
 * \brief Send raw data to ECU.
 *
 * \param handler obdii handler.
 * \param cmd data to send.   
 * 
 * \return request status  > 0 OK ; <0 KO  
 */
short int obdii_send_raw(obdii_handler* handler, char* cmd);


/**
 * \fn Send raw data to ECU.
 * \brief Send raw data to ECU.
 *
 * \param handler obdii handler.
 * \param buffer data to send.   
 * 
 * \return request status  > 0 OK ; <0 KO  
 */
short int obdii_retrieve_raw(obdii_handler* handler, char* buffer); 


/**
 * \fn Retrieve ELM interface version.
 * \brief etrieve ELM interface version.
 *
 * \param handler obdii handler.
 * 
 * \return request status  > 0 OK ; <0 KO  
 */
short int obdii_retrieve_elm_version(obdii_handler* handler);


/**
 * \fn Retrieve error string from response.
 * \brief Retrieve error string from response.
 *
 * \param response obdii response.
 *     
 * \return Pointer to error string. 
 */
char* obdii_err_str(obdii_response response);


/**
 * \fn Retrieve PID list.
 * \brief Retrieve PID list. 
 * 
 * \return Pointer to a obdii_pid tab.
 */
obdii_pid* obdii_get_pid_list();


/**
 * \fn Retrieve a pid from pid_no
 * \brief REtrieve a pid from pid_no.
 *
 * \param pid_no pid number. 
 * 
 * \return obdii_pid.
 */
obdii_pid obdii_get_pid(unsigned short int pid_no);


/**
 * \fn Retrieve PID name.
 * \brief Retrieve PID name.
 *
 * \param pid_no pid number. 
 * 
 * \return Pointer to pid name string.  
 */
const char* obdii_get_name_from_pidno(unsigned short int pid_no);


/**
 * \fn Retrieve PID name.
 *
 * \param pid PID.
 *
 * \return PID name.
 */
const char* obdii_get_name(obdii_pid pid);


/**
 * \fn Retrieve PID unit.
 *
 * \param pid PID.
 *
 * \return PID unit.
 */
const char* obdii_get_unit(obdii_pid pid);


/**
 * \fn Retrieve PID function helper.
 *
 * \param pid PID.
 *
 * \return PID function helper.
 */
void* obdii_get_fct_helper(obdii_pid pid);


/**
 * \fn Prcedure which prints PID info on stdout.
 *
 * \param pid PID.
 *
 */
void print_pid_info(obdii_pid pid);


/**
 * \fn Procedure which prints PID info on stdout.
 *
 * \param pid_no  PID Number.
 *
 * \return PID unit.
 */
void print_pid_info_no(short int pid_no);


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




extern obdii_pid* standard_pid_list;


#endif
