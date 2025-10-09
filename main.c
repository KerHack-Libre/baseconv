/* @file  main.c  
 * @brief entry  program 
 * @author Umar Ba <jUmarB@protonmail.com> <github/Jukoo> 
 */ 
#define __USE_GNU  
#include <stdlib.h> 
#include <stdio.h>
#include <errno.h>  
#include <string.h>
#include <err.h>
#include <ctype.h> 
#include <unistd.h> 

#include "baseconv.h" 
#include "bcvrepl.h"



//!TODO : Build  argparse library  that handle arguments 
//!NOTICE : I'it will be a seperate project 


#define  bcv_out(__expression ,__mode) \
  fprintf(stdout , "%s : %s\012", __mode ,  __expression)   

int main(int ac , char **av) 
{ 
  (void) setvbuf(stdout , (void *)0 , _IONBF ,0) ;  

  //!NOTICE : when no argument was provided  the repl is automaticaly launched
  if (!(ac &~(1)))  
  { 
    bcrepl_shell(__nptr); 
    goto _bcv_end; 

  } 

  //!NOTICE : long  options are note handled ... 
  //!NOTICE : probably -h and -v (help and version)  
  if( ac == 2 )
  {
    
    char * short_flags = *(av+(ac-1)) ; 
    if( !(0x2d ^  *(short_flags)& 0xff))  
    {
      switch((*(short_flags+1)  & 0xff)) 
      {
        case 'h': printf("%s\012%s\12",USAGE, BCV_VERSION_STR) ;break; 
        case 'v': printf("%s\012%s\012", BCV_STARTUP_MESG , BCV_VERSTRLONG);break; 
        default:
                 fprintf(stderr, "unknow option \n");
                 printf("%s\012%s\012",USAGE,  BCV_STARTUP_MESG) ;break; 
                 break ; 
      }
      goto _bcv_end;  
    }

    unsigned int  value =  strtol(short_flags , (void  *)00 , 10) ;  
    if (!value)  
      value = (unsigned char)( *(short_flags) & 0xff) ;   

    bcv_out(bc_hex(value),"HEX"); 
    bcv_out(bc_oct(value),"OCT");  
    bcv_out(bc_bin(value),"BIN"); 
    
    goto _bcv_end ; 
  } 

  if(ac == 3)
  {
    char *short_flags =  *(av+(ac-2)) ; 
    unsigned int value = strtol(*(av+(ac-1)) ,  __nptr , 012) ; 
    if(!value)  
      value =(unsigned char) (**(av+(ac-1))  & 0xff ); 

    if( !(0x2d ^ *(short_flags)& 0xff))   
    {
      switch( (*(short_flags+1)  &0xff))   
      {
        case 'x': 
          bcv_out(bc_hex(value), "HEX"); 
          break; 
        case 'o': 
          bcv_out(bc_oct(value) ,"OCT"); 
          break; 
        case 'b': 
          bcv_out(bc_bin(value) ,"BIN"); 
          break; 
        case 'h': printf("%s\012%s\012",USAGE, BCV_VERSION_STR) ;break; 
        case 'v': printf("%s\012%s\012", BCV_STARTUP_MESG , BCV_VERSTRLONG);break; 
        default:
                 fprintf(stderr, "unknow option \n");
                 printf("%s\012%s\012",USAGE,BCV_VERSION_STR) ;break; 
                 break ; 
      }
    }
  }

_bcv_end: 

  return EXIT_SUCCESS ; 
}
