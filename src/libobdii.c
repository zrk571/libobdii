#include"../include/libobdii.h"

obdii_handler* obdii_get_handler(char* device, obdii_speed speed, unsigned short int timeout, unsigned short int retry)
{
  // Initialisation.
  obdii_handler* handler = NULL;
  handler = malloc(sizeof(obdii_handler));

  memset(handler, '\0', sizeof(obdii_handler));
 
  handler->speed = speed;
  handler->device = strdup(device);
  handler->timeout = timeout;
  handler->max_retry = retry;
  handler->state = OFFLINE;

  strncpy(handler->version, OBDII_MSG_VERSION, strlen(OBDII_MSG_VERSION));

  return handler;
}


obdii_response* obdii_malloc_response()
{
  obdii_response* response = NULL;

  response = (obdii_response*) malloc(sizeof(obdii_response));  
  if (response != NULL) {
    response->buffer = (char*) malloc(sizeof(char)*16);
    if(response->buffer == NULL){
      free(response);
      return NULL;
    }
  }

  return response;
}


char** obdii_eligible_device_list(ssize_t* device_count)
{
  ssize_t eligible_devices_count = 0;
  char** devices = NULL;
  struct dirent* entry = NULL;
  DIR* dir = NULL;

  if((devices = (char**) malloc(sizeof(char*)*5)) == NULL){
    perror("Error");
  }

  if((dir = opendir("/dev/")) == NULL){
    perror("Error");
  }

  while((entry=readdir(dir)) != NULL){
    if(strncmp("ttyS", entry->d_name, 4) == 0
       || strncmp("ttyUSB", entry->d_name, 6) == 0){
	devices[eligible_devices_count] = malloc(sizeof(char)*(strlen(entry->d_name)+5));
	if(devices[eligible_devices_count] != NULL){
		
	strcpy(devices[eligible_devices_count], "/dev/");
	strncpy(devices[eligible_devices_count]+5, entry->d_name, strlen(entry->d_name));

	eligible_devices_count++;
	}
	if(eligible_devices_count > 0 && eligible_devices_count % 5 == 0){
		devices = realloc(devices, sizeof(char*)*(eligible_devices_count+5));
 		if(devices == NULL){
			perror("Error");
		}
	}
    }
  }

  closedir(dir);

  *device_count = eligible_devices_count;

  return devices;
}


short int obdii_init(obdii_handler* handler)
{
  if(handler != NULL){
    handler->state = UNKNOWN; 

   
   handler->descriptor = open(handler->device, O_RDWR | O_NOCTTY | O_NDELAY);
   if(handler->descriptor < 0){
     perror(handler->device);
     return -1;
   }

   fcntl(handler->descriptor, F_SETFL, 0);

   tcgetattr(handler->descriptor, &(handler->old_context));
   tcgetattr(handler->descriptor, &(handler->tty));

   handler->tty.c_cflag |= (CLOCAL | CREAD);

   handler->tty.c_lflag &= ~(ICANON|ECHO|ECHOE|ECHOK|ECHONL|ISIG|IEXTEN);
   handler->tty.c_lflag &= ~(ECHOCTL);
   handler->tty.c_lflag &= ~(ECHOKE);

   handler->tty.c_oflag &= ~(OPOST);

   handler->tty.c_iflag &= ~(INLCR|IGNCR|ICRNL|IGNBRK);
   handler->tty.c_iflag &= ~(IUCLC);
   handler->tty.c_iflag &= ~(PARMRK);
  
   handler->tty.c_cflag &= ~CSIZE;
   handler->tty.c_cflag |= CS8;

   handler->tty.c_cflag &= ~(CSTOPB);
   handler->tty.c_iflag &= ~(INPCK|ISTRIP);
   handler->tty.c_cflag &= ~(PARENB|PARODD);
   handler->tty.c_iflag &= ~(IXON|IXOFF|IXANY);
   handler->tty.c_cflag &= ~(CRTSCTS);

   handler->tty.c_cc[VMIN] = 0;
   handler->tty.c_cc[VTIME] = 0;

   //Set communication speed.
   cfsetispeed(&(handler->tty), handler->speed);
   cfsetospeed(&(handler->tty), handler->speed);

   //Bind termios with descriptor.
   tcsetattr(handler->descriptor, TCSANOW, &(handler->tty));
    
   //tcflow(handler->descriptor, TCOON);

   handler->state = ONLINE;	

   obdii_send_raw(handler, "atz");
   sleep(2);

   obdii_retrieve_elm_version(handler);
   
   obdii_send_raw(handler, OBDII_ECHO_OFF);
   sleep(2);
   char buffer[256];

   memset(buffer, '\0', sizeof(char)*256);

   obdii_retrieve_raw(handler, buffer);
   printf("%s\n", buffer);
   //usleep(50000);

  }

  return OBDII_OK;
}


short int obdii_close(obdii_handler* handler)
{
  if(handler == NULL){
    return -1;
  }

  obdii_send_raw(handler, OBDII_CLOSE);

  tcsetattr(handler->descriptor, TCSANOW, &(handler->old_context));
  
  handler->state = OFFLINE;
  memset(handler->version, '\0', sizeof(char)*64);

  return 1;            
}


short int obdii_send_raw(obdii_handler* handler, char* cmd)
{
  if(handler != NULL && handler->state == ONLINE && cmd != NULL){
    ssize_t count = 0;
    ssize_t index;

    ssize_t retry = 0;

    int ret_code = -1;

    struct timeval tv;
    tv.tv_sec = handler->timeout;
    tv.tv_usec = 0;

    fd_set fd_write; 
    FD_ZERO(&fd_write);
    FD_SET(handler->descriptor, &fd_write);

    while(retry < handler->max_retry){
      ret_code = select(handler->descriptor+1, NULL, &fd_write, NULL, &tv);

      if(ret_code > 0){
        //Flush IO buffers.   
        tcflush(handler->descriptor, TCIFLUSH);
        tcflush(handler->descriptor, TCOFLUSH);

        for(index = 0; index< strlen(cmd); index++){
          count += write(handler->descriptor, cmd+index, sizeof(char));       
          //printf("%c : %d\n", *(cmd+index), count);
        }

        count += write(handler->descriptor, "\r", sizeof(char)*1);
        count += write(handler->descriptor, "\n", sizeof(char)*1);

        if(count == strlen(cmd)+2){
          return OBDII_OK;
        }
      }
      else if(ret_code == 0){
          printf("no writted data\n");
          retry++;
      }
    }
  }
  return OBDII_ERROR;
}

  
short int obdii_retrieve_raw(obdii_handler* handler, char* buffer)
{
  if(handler != NULL && handler->state == ONLINE && buffer != NULL){
    ssize_t count = 0;
    ssize_t index = 0;

    ssize_t retry = 0;

    int ret_code = -1;

    struct timeval tv;
    tv.tv_sec = handler->timeout;
    tv.tv_usec = 0;

    fd_set fd_read; 
    FD_ZERO(&fd_read);
    FD_SET(handler->descriptor, &fd_read);

    while(retry < handler->max_retry){
      ret_code = select(handler->descriptor+1, &fd_read, NULL, NULL, &tv);

      if(ret_code > 0){
        count += read(handler->descriptor, buffer+index, sizeof(char));    
        if(*(buffer+index) == '>' && count > 0){
          buffer[index] = '\0';
          break;
        }
        else if(*(buffer+index) != '>' || *(buffer+index) != ' '){
          index = index++ % 254;
        }
      }
      else if(ret_code == 0){
        printf("No readable data\n");
        retry++;
      }
    }

    if(retry < handler->max_retry && count > 0){
      return OBDII_OK;
    }
  }
  return OBDII_ERROR;
}


short int obdii_retrieve_elm_version(obdii_handler* handler)
{
  if(handler != NULL && handler->state == ONLINE){
    return obdii_retrieve_raw(handler, handler->version);
  }
  return OBDII_NODATA;
}


short int obdii_free_handler(obdii_handler* handler)
{
  if(handler != NULL && handler->state == OFFLINE || handler->state == UNKNOWN){
    if(handler->device != NULL){
      free(handler->device);
    }
    free(handler);
  }

  return 1;
}


short int obdii_free_response(obdii_response* response)
{
  if(response != NULL){
    if(response->buffer !=  NULL){
      free(response->buffer);
    }
    free(response);
  }
  return 1;
}


short int obdii_free_request(obdii_request* request)
{
  if(request != NULL){
      free(request);
  }
  return 1;
}


short int obdii_ask(obdii_handler* handler, obdii_request* request, obdii_response* response)
{
  if((handler != NULL && handler->state == ONLINE) && request != NULL && response != NULL){
    ssize_t retry = 0;
    ssize_t index = 0;
    ssize_t processed = 1;

    if(response->buffer != NULL){
      response->buffer = malloc(sizeof(char)*32);
    }

    while(retry < handler->max_retry){
      //Erase buffer content.
      memset(response->buffer, '\0', sizeof(char)*32);

      char* buffer = response->buffer;
      obdii_send_raw(handler, (char*)request->pid->code);
      obdii_retrieve_raw(handler, buffer);

      if(strncmp(buffer+strlen(buffer)-6, OBDII_MSG_NODATA, 6) == 0){
        response->err_str = response->buffer;
      }
      else if(strncmp(response->buffer, OBDII_MSG_UNABLE_TO_CONNECT, 6) == 0){ //TODO: Need to be fixed.
        printf("Unable to connect to ECU\n");
        return OBDII_ERROR;
      }
      else if(retry+1 == handler->max_retry && strlen(response->buffer) == 0){
	response->err_str = response->buffer;
        return OBDII_ERROR;
      }
      else if(strlen(response->buffer) > 0){
	//TODO: Process with helper ned to be done here.


        return OBDII_OK;
      }
      retry++;
  }
 }
  return OBDII_NODATA;
}


char* obdii_err_str(obdii_response response)
{
  if(response.err_str != NULL && strlen(response.err_str) > 0){
    return response.err_str;
  }
  return NULL;
}


obdii_pid* obdii_get_pid_list()
{
  extern obdii_pid standard_pid_list[12];

  return (obdii_pid*)standard_pid_list;
}


obdii_pid obdii_get_pid(unsigned short int pid_no)
{  
  extern obdii_pid standard_pid_list[12];

  return standard_pid_list[pid_no];
}


const char* obdii_get_name_from_pidno(unsigned short int pid_no)
{
  extern obdii_pid standard_pid_list[12];

  return standard_pid_list[pid_no].name;
}


const char* obdii_get_name(obdii_pid pid)
{
  return pid.name;
}


const char* obdii_get_unit(obdii_pid pid)
{
  return pid.unit;
}


void* obdii_get_fct_helper(obdii_pid pid)
{
  return pid.fct_helper;
}


void print_pid_info(obdii_pid pid)
{
  fprintf(stdout, "PID No : %d\n\
-------\n\
Summary : %s\n\
Code    : %s\n\
Units   : %s\n", pid.pid, pid.name, pid.code, pid.unit);
}


void print_pid_info_no(short int pid_no)
{
  extern obdii_pid standard_pid_list[12];

  obdii_pid pid  = standard_pid_list[pid_no];
 
  print_pid_info(pid);
}
