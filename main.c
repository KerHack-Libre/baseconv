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



#define  USAGE "\
Usage : bcv [OPTION] ... <NUMBER>\n\
Convert Number to specific base\n\
-b,  Convert to binary Base\n\
-x,  Convert to hexadecimal Base\n\
-o,  Convert to Octal Base\n\
-v,  Version of the Program\n\
-h,  Print  this help\n\
"
//!TODO : Build  argparse library  that handle arguments 
//!NOTICE : I'it will be a seperate project 

int main(int ac , char **av) 
{ 
  (void) setvbuf(stdout , (void *)0 , _IONBF ,0) ;  

  //!NOTICE : when no argument was provided  the repl is automaticaly launched
  if (ac == 1 ) 
  {
    bcrepl_shell(__nptr); 
    return EXIT_SUCCESS ;
  }
    
  //!NOTICE : probably -h and -v (help and version)  
  if (ac  == 2) 
  {
    
    char * short_flags = *(av+ac-1) ; 
    if( 0x2d ==  *(short_flags)& 0xff) 
    {
      switch(*(short_flags+1)) 
      {
        case 'h': printf("%s%s",USAGE, bcv_version) ;break; 
        case 'v': printf("%s", bcv_version);break; 
        default:
                 fprintf(stderr, "unknow option \n");
                 printf("%s%s",USAGE, bcv_version) ;break; 
                 break ; 
      }
    }

  }
  if(ac == 3)
  {
    char *short_flags =  *(av+(ac-2)) ; 
    int  value = strtol(*(av+(ac-1)) ,  __nptr , 0xa) ; 
   
    if( 0x2d ==  *(short_flags)& 0xff) 
    {
      switch(*(short_flags+1)) 
      {
        case 'x': bc_hex(value); break; 
        case 'o': bc_oct(value); break; 
        case 'b': bc_bin(value); break; 
        case 'h': printf("%s%s",USAGE, bcv_version) ;break; 
        case 'v': printf("%s", bcv_version);break; 
        default:
                 fprintf(stderr, "unknow option \n");
                 printf("%s%s",USAGE, bcv_version) ;break; 
                 break ; 
      }
    }
  }



  return EXIT_SUCCESS ; 
}
