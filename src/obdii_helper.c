#include"../include/obdii_helper.h"


int _hex_to_int(char* data){
  return (int)strtol(data, NULL, 16);
}

double maf(char* data){
  return _hex_to_int(data)*C_MAF;
}

double throttle_position(char* data){
  return _hex_to_int(data)*100./255.;
}


double intake_pressure(char* data){
  return _hex_to_int(data)/ C_INTAKE_PRESSURE;
}

double rpm(char* data){
  return _hex_to_int(data)/C_RPM;
}


double speed(char* data){
  return _hex_to_int(data)/C_SPEED;
}


double percent_scale(char* data){
  return _hex_to_int(data)*100./255.;
}


double ignition_timming_advance(char* data){
  return  (_hex_to_int(data)-128.)/2.;
}

double coolant_temperature(char* data){
  return _hex_to_int(data)-40.;
}

double fuel_trim_percent(char* data){
  return  (_hex_to_int(data)-128.)*100./128.;
}

int convert_to_min(char* data){
  return _hex_to_int(data)/60;
}

