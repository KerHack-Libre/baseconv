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

#define  bcv_out(__expression) \
  fprintf(stdout , "%s\n", __expression) 

int main(int ac , char **av) 
{ 
  (void) setvbuf(stdout , (void *)0 , _IONBF ,0) ;  

  //!NOTICE : when no argument was provided  the repl is automaticaly launched
  if (!(ac &~(1)))  
  { 
    bcrepl_shell(__nptr); 
    goto _bcv_end; 

  //!NOTICE : probably -h and -v (help and version)  
  //!NOTICE : long  options are note handled ... 
  }else {
    
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
    }

    goto _bcv_end ; 
  } 

  if(ac == 3)
  {
    char *short_flags =  *(av+(ac-2)) ; 
    int  value = strtol(*(av+(ac-1)) ,  __nptr , 012) ; 
   
    if( !(0x2d ^ *(short_flags)& 0xff))   
    {
      switch( (*(short_flags+1)  &0xff))   
      {
        case 'x': 
          bcv_out(bc_hex(value)); 
          break; 
        case 'o': 
          bcv_out(bc_oct(value)); 
          break; 
        case 'b': 
          bcv_out(bc_bin(value)); 
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
