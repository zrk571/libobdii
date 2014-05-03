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

#include<sys/types.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<sys/select.h>

#include<dirent.h>
#include<unistd.h>

#include<fcntl.h>
#include<termios.h>

#include"obdii_type.h"
#include"obdii_pid.h"


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
 * \fn Returns a well malloced obdii_available_pid.
 * 
 * \return a well malloced obdii_available_pid.
 */
obdii_available_pid* obdii_malloc_available_pid();


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
 * \fn Suitable to free obdii_request.
 * \brief Free malloced memory used as obdii_response.
 *
 * \param available_pid  available pid list. 
 */
short int obdii_free_available_pid(obdii_available_pid* available_pid);


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
 * \brief retrieve ELM interface version.
 *
 * \param handler obdii handler.
 * 
 * \return request status  > 0 OK ; <0 KO  
 */
short int obdii_retrieve_elm_version(obdii_handler* handler);


/**
 * \fn Retrieve available pid.
 * \brief retrieve all available pid for the current car.
 *
 * \param handler obdii handler.
 * \param available obdii pid list.
 * 
 * \return request status  > 0 OK ; <0 KO  
 */
short int obdii_retrieve_available_pid(obdii_handler* handler, obdii_available_pid* available_pid);


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
 * \fn Retrieve PID code.
 *
 * \param pid PID.
 *
 * \return PID code.
 */
const char* obdii_get_code(obdii_pid pid);


/**
 * \fn Retrieve PID unit.
 *
 * \param pid PID.
 *
 * \return PID unit.
 */
const char* obdii_get_unit(obdii_pid pid);


/**
 * \fn Retrieve PID range.
 *
 * \param pid PID.
 *
 * \return PID range.
 */
short int obdii_get_range(obdii_pid pid);


/**
 * \fn Retrieve PID function helper.
 *
 * \param pid PID.
 *
 * \return PID function helper.
 */
void* obdii_get_fct_helper(obdii_pid pid);


/**
 * \fn Retrieve reponse value.
 *
 * \param response request response.
 *
 * \return Request response value.
 */
char* obdii_get_response_value(obdii_response response);


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
 * \fn Check if specified pid is available.
 *
 * \param available_pid  available pid list. 
 * \param pid PID.
 *
 * \return request status  > 0 OK ; <=0 KO 
 */
short int obdii_pid_is_available(obdii_available_pid* available_pid, obdii_pid* pid);


#endif
