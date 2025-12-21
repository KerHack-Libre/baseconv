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

#define  bcv_out(__expression ,__mode) \
  fprintf(stdout , "%s : %s\012", #__mode ,  __expression)   

#define  BIN (0x62) 
#define  OCT (0x6f<<8) 
#define  HEX (0x78<<16)
#define  DEC (0x64<<24)  

#define  ALLBASE_ENABLE (BIN|OCT|HEX|DEC)  

void bcv_usage(unsigned char const) ;            /* [[noreturn]] */
void bcv_guess_base(const char * __restrict__) ; /* [[noreturn]] */
void bcv_print(unsigned int value, int) ;

int main(int ac , char **av) 
{ 
  (void) setvbuf(stdout , (void *)0 , _IONBF ,0) ;  

  //!NOTICE : when no argument was provided  the repl is automaticaly launched
  if (!(ac &~(1)))  
  { 
    //! launch interactive shell 
    bcrepl_shell(__nptr);    
    goto _bcv_end;
  }
  
  //!NOTICE : long  options are note handled ... 
  //!NOTICE : probably -h and -v (help and version)  
  if( ac == 2 )
  {
    char * short_flags = *(av+(ac-1)) ; 
    
    if( !(0x2d ^ (*(short_flags)& 0xff) ) )  
      bcv_usage(*(short_flags+1) & 0xff); 
  
    if(!(0x30 ^ (*(short_flags) & 0xff))) 
      bcv_guess_base(short_flags) ;  
      
    unsigned int  value =  strtol(short_flags , (void  *)00 , 10) ;  
   if (!value)
      value = (unsigned char)(*(short_flags)&0xff);

   bcv_print(value , DEC | HEX | OCT | BIN) ;
    
    goto _bcv_end ; 
  } 

  if(ac == 3)
  {
    char *short_flags =  *(av+(ac-2)) ; 
    unsigned int value = strtol(*(av+(ac-1)) ,  __nptr , 012) ; 
    if(!value)  
      value =(unsigned char) (**(av+(ac-1))  & 0xff ); 

    if( !(0x2d ^ (*(short_flags)& 0xff)))   
    {
      switch( (*(short_flags+1)  &0xff))   
      {
        case 'x': 
          bcv_out(bc_hex(value),HEX); 
          break; 
        case 'o': 
          bcv_out(bc_oct(value),OCT); 
          break; 
        case 'b': 
          bcv_out(bc_bin(value),BIN); 
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


void bcv_print(unsigned int value  , int base_option)
{
    if(base_option &  DEC)
      bcv_out(bc_dec(value), DEC);

    if(base_option &  HEX)
      bcv_out(bc_hex(value), HEX);

    if(base_option & OCT)
      bcv_out(bc_oct(value) , OCT);

    if(base_option & BIN)
      bcv_out(bc_bin(value) , BIN);
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

  unsigned int  options = ALLBASE_ENABLE, 
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
     default : 
       goto _end; 
  }

   
  if(options  & DEC) 
    bcv_out(bc_dec(value) , DEC) ; 

  if(options & HEX)  
    bcv_out(bc_hex(value) , HEX) ; 

  if(options & OCT) 
    bcv_out(bc_oct(value) , OCT) ; 

  if(options & BIN) 
    bcv_out(bc_bin(value), BIN) ; 

_end: 
  exit(EXIT_SUCCESS) ; 
}


