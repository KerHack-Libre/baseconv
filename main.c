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
#include <limits.h> 
#include <stdint.h> 

#include "baseconv.h" 

#define NO_ARGS  !(ac &~(1)) 

void bcv_usage(unsigned char const) ;            /* [[noreturn]] */

int main(int ac , char **av) 
{ 
  (void) setvbuf(stdout , (void *)0 , _IONBF ,0) ; 
   
  //!NOTICE : when no argument was provided  the repl is automaticaly launched 
 
  if(bcv_launch_interactive_repl_on(NO_ARGS))  
    goto _bcv_end ;

 
  //!NOTICE : long  options are note handled ... 
  //!NOTICE : probably -h and -v (help and version)  
  //!TODO   : make support for  long option  
  if( ac == 2 )
  {
    char * short_flags = *(av+(ac-1)) ; 
    
    if( !(0x2d ^ (*(short_flags)& 0xff) ) )  
      bcv_usage(*(short_flags+1) & 0xff); 
  
    if(!(0x30 ^ (*(short_flags) & 0xff))) 
    {
      bcv_guess_base(short_flags) ;  
      return EXIT_SUCCESS ; 
    }
      
    uf64_t  value = bcvtol(short_flags,10) ;  
    if (!value && is_printable(short_flags))
      value = (*short_flags & 0xff) ;  

    bcv_print(value);  
    goto _bcv_end ; 
  } 

  if(ac == 3)
  {
    char *short_flags =  *(av+(ac-2)) ; 
    uf64_t value = strtol(*(av+(ac-1)) ,  __nptr , 012) ; 
    if(!value)  
      value =(unsigned char) (**(av+(ac-1))  & 0xff ); 

    if( !(0x2d ^ (*(short_flags)& 0xff)))   
    {
      switch( (*(short_flags+1)  &0xff))   
      {
        case 'x': 
          bcv_out(bc_hex(value),HEX);break; 
        case 'o': 
          bcv_out(bc_oct(value),OCT);break; 
        case 'b':  
          bcv_out(bc_bin(value),BIN);break; 
        case 'd':
          bcv_out(bc_dec(value),DEC);break; 
        case 'c':  
          bcv_out(bc_chr(value),CHR);break; 
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

void bcv_usage(unsigned char const char_flag) 
{
  switch(char_flag) 
  {
    case 'h': printf("%s\012%s\12",USAGE, BCV_VERSION_STR) ;break; 
    case 'v': printf("%s\012%s\012", BCV_STARTUP_MESG , BCV_VERSTRLONG);break; 
    default:  fprintf(stderr, "unknow option \n");
              printf("%s\012%s\012",USAGE,  BCV_STARTUP_MESG) ;
              break; 
  }

  exit(EXIT_SUCCESS) ; 
} 

