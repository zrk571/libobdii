#include "../include/various.h"

void _debug_printf(const char* message){
  printf("%s(%d) : %s\n", __FILE__, __LINE__, message);
}


char** split_in_array(char c, char* data){
  if(data != NULL && strlen(data) > 0){
    ssize_t index = 0;
    ssize_t count = 0;
    char** result;
    char* bck_data = data;
    char* save;
    char* token;

    while(index< strlen(data)){
      if(data[index] == c){
        count++;
        if(index-1 > 0 && data[index-1] == c){
          count--;
        }
      }
      index++;
    }
    if(index > 0 && data[index-1] != c){
      count++;
    }
    count++;

    if(count==0){
      return NULL;
    }

    result = (char**) malloc(count*sizeof(char*));
    index = 0;    

    while(1){

      token = strtok_r((index > 0 ? NULL : bck_data), &c, &save);

      if (token == NULL){
        break;
      }
      result[index++] = strdup(token);
    }
    result[++index] = NULL;

    return result;
  }

  return NULL;
}


int msb_to_lsb(unsigned int num, unsigned int numBits)
{
    unsigned int reversedNum;
    unsigned int mask = 0;

    mask = (0x1 << (numBits/2)) - 1;

    if (numBits == 1){
        return num;
    }
    reversedNum = msb_to_lsb(num >> numBits/2, numBits/2) | msb_to_lsb((num & mask), numBits/2) << numBits/2;
    
    return reversedNum;
}