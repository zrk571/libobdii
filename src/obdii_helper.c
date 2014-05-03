#include"../include/obdii_helper.h"


int _hex_to_int(char* data){
  return (int)strtol(data, NULL, 16);
}

void maf(char* data){
    if (data != NULL && strlen(data) > 4) {
        char* value = data+4;
        
        char A[2]; 
        A[0] = value[0];
        A[1] = value[1];
        
        char B[2]; 
        B[0] = value[2];
        B[1] = value[3];
        
        int iA = _hex_to_int(A);
        int iB = _hex_to_int(B);
        
        int result = ((iA*256)+iB)/100;
        printf("%d\n", result);
    } 
}

void throttle_position(char* data){
    printf("-%s#\n",data);
    if(data != NULL && strlen(data) > 2){
        char* value = data+2;
        
        char A[2]; 
        A[0] = value[0];
        A[1] = value[1];
        
        int iA = _hex_to_int(A);
        
        int result = (iA*100)/255;
        printf("%d\n", result);
    }
}


double intake_pressure(char* data){
  return _hex_to_int(data)/ C_INTAKE_PRESSURE;
}

void rpm(char* data){
    if (data != NULL && strlen(data) > 4) {
        char* value = data+4;
        
        char A[2]; 
        A[0] = value[0];
        A[1] = value[1];
        
        char B[2]; 
        B[0] = value[2];
        B[1] = value[3];
        
        int iA = _hex_to_int(A);
        int iB = _hex_to_int(B);
        
        int result = ((iA*256)+iB)/4;
        printf("%d\n", result);
    }
}


void engine_oil_temp(char* data){
    if (data != NULL && strlen(data) > 4) {
        char* value = data+4;
        
        char A[2]; 
        A[0] = value[0];
        A[1] = value[1];
    
        int iA = _hex_to_int(A);
        
        int result = iA-40;
        printf("%d\n", result);
    }
}


void engine_coolant_temp(char* data){
    if (data != NULL && strlen(data) > 4) {
        char* value = data+4;
        
        char A[2]; 
        A[0] = value[0];
        A[1] = value[1];
    
        int iA = _hex_to_int(A);
        
        int result = iA-40;
        printf("%d\n", result);
    }
}


void engine_intake_temp(char* data){
    if (data != NULL && strlen(data) > 4) {
        char* value = data+4;
        
        char A[2]; 
        A[0] = value[0];
        A[1] = value[1];
    
        int iA = _hex_to_int(A);
        
        int result = iA-40;
        printf("%d\n", result);
    }
}


void load(char* data){
    if (data != NULL && strlen(data) > 4) {
        char* value = data+4;
        
        char A[2]; 
        A[0] = value[0];
        A[1] = value[1];
    
        int iA = _hex_to_int(A);
        int result = (iA*100)/255;
       
        printf("%d\n", result);
    }
}


void speed(char* data){
    if (data != NULL && strlen(data) > 4) {
        char* value = data+4;
        
        char A[2]; 
        A[0] = value[0];
        A[1] = value[1];
    
        int result = _hex_to_int(A);
       
        printf("%d\n", result);
    }
}


double percent_scale(char* data){
  return _hex_to_int(data)*100./255.;
}


double ignition_timming_advance(char* data){
  return  (_hex_to_int(data)-128.)/2.;
}


double fuel_trim_percent(char* data){
  return  (_hex_to_int(data)-128.)*100./128.;
}

int convert_to_min(char* data){
  return _hex_to_int(data)/60;
}

