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
#include "bcvrepl.h"

#define  UMAX_LONG   ~((0ULL)>>1) 

#define  bcv_out(__expression ,__annotation) \
  fprintf(stdout , "%s: %s\012", #__annotation ,  __expression)   



void bcv_usage(unsigned char const) ;            /* [[noreturn]] */
void bcv_guess_base(const char * __restrict__) ; /* [[noreturn]] */
void bcv_print(uf64_t value) ;

int main(int ac , char **av) 
{ 
  (void) setvbuf(stdout , (void *)0 , _IONBF ,0) ; 
   
  //!NOTICE : when no argument was provided  the repl is automaticaly launched 
  //if(bcv_launch_iteractive_repl_on(!(ac ~ &(1))))  
    //goto _bcv_end ; 
  if (!(ac &~(1)))  
  { 
    //! launch interactive shell 
    (void) setlinebuf(stdin) ; 
    bcrepl_shell(__nptr);    
    goto _bcv_end;
  }
  
  //!NOTICE : long  options are note handled ... 
  //!NOTICE : probably -h and -v (help and version)  
  //!TODO   : make support for  long option  
  if( ac == 2 )
  {
    char * short_flags = *(av+(ac-1)) ; 
    
    if( !(0x2d ^ (*(short_flags)& 0xff) ) )  
      bcv_usage(*(short_flags+1) & 0xff); 
  
    if(!(0x30 ^ (*(short_flags) & 0xff))) 
      bcv_guess_base(short_flags) ;  
      
    uf64_t  value =  strtol(short_flags , (void  *)00 , 10) ;  
   if (!value)
      value = (unsigned char)(*(short_flags)&0xff);

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


void bcv_print(uf64_t value)
{
    if((__allbase_enable__ >> 32)&  0x64)
      bcv_out(bc_dec(value), DEC);

    if(__allbase_enable__ &  HEX)
      bcv_out(bc_hex(value), HEX);

    if(__allbase_enable__ & OCT)
      bcv_out(bc_oct(value) , OCT);

    if(__allbase_enable__ & BIN)
      bcv_out(bc_bin(value), BIN); 

    if(__allbase_enable__ & CHR)  
      bcv_out(bc_chr(value), CHR) ; 

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


void bcv_guess_base(const char * restrict num) 
{ 

  uf64_t  options = __allbase_enable__, 
                resolve_option=__allbase_enable__,  
                value   = 0  ; 
  char indicator = tolower(*(num+1)  & 0xff ) ; 
  
  switch(indicator) 
  {
     case 'x' :  
       options&=~HEX; 
       value = strtol((num+2), (void *)0 , 0x10) ;
       break; 
     case 'o' :
       options&=~OCT ;  
       value = strtol((num+2), (void *)0 , 010);
       break; 
     case 'b' :
       options&=~BIN ;
       value = strtol((num+2), (void *)0 , 2) ;
       break;  
     case 'c':
       options &=~CHR; 
       value = strtol((num+2), (void*)0 , 10) ; 
       break; 
     default : 
       //! it's highly a decimal 
       options&=~429496729600 ; 
       value = strtol(num, (void*)0 , 10) ; 
       goto _end; 
  }
 
  
  uf64_t exclude= (__allbase_enable__ ^  options) ;  
  __allbase_enable__^=exclude; 
  bcv_print(value)  ;  
  
  __allbase_enable__ = resolve_option ; 

_end: 
  exit(EXIT_SUCCESS) ; 
}


