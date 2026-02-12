/* @file  bcvrepl.c
 * @brief  base convertion  with interactive  repl  
 * @author Umar Ba <jUmarB@protonmail.com>  <github/Jukoo> 
 */ 

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <ctype.h>
#include <errno.h> 

#include "bcvrepl.h" 
#include "baseconv.h"


void bcrepl_shell(const char *  prompt)
{
   const char * prmpt =  !prompt ? pname :  prompt ;  
   int proceed =1 ; 
   char prompt_buffer[bcrepl_buffer_limit]={0}; 
   int  line = 0; 
   fprintf(stdout , "%s" , BCV_STARTUP_MESG) ; 
   while (proceed, ++line) 
   { 
     //!repl_promt 

     apply( printf(bpf, line,  prmpt , bcrepl_symbole_prompt) , GREEN) ;  

     if(!(fgets(prompt_buffer ,  bcrepl_buffer_limit, stdin)))
       continue ; 
    
     char *n  = strchr(prompt_buffer , 0xa) ;
     if (n)  *n  = 0;    
     
     if (0==strlen(prompt_buffer)) continue ; 
     bcrepl_compute(prompt_buffer) ; 
     /* NOTICE :always clean the repl buffer */
     bzero(prompt_buffer , bcrepl_buffer_limit) ; 

     fflush(stdin) ; 
   }
} 

void bcrepl_customize(user_prompt_custom_shell  custom_prompt  ,  const char *   prompt) 
{
  if(!custom_prompt) 
     bcrepl_shell( prompt ) ; 
   else  
     custom_prompt(prompt) ; 
}

void bcrepl_compute(const char * buffer) 
{

  bcrepl_listen_special_cmd(buffer) ; 
  struct bcv_parse_t {
     char  _sym_instruction:8;  
     int _value ; 
  }  bcv_scaner = { 0,0 };  

  char *buffer_clone =  (char *) buffer, 
       *token = __nptr  ; 
  int  scan_limite= 2 ; 
  while( __nptr != (token = strtok(buffer_clone ,  (const char []) { 0x2f , 00 } )))  
  {
    if(scan_limite & 0x2) 
    {
       bcv_scaner._sym_instruction= (char) *token  & 0xff ;  
       buffer_clone = __nptr; 
    }
    if(scan_limite & 0x1)
    {
      bcv_scaner._value = strtol(token , __nptr  , 0xa) ;  
      if(!bcv_scaner._value) 
        bcv_scaner._value = (unsigned char ) (*(token) & 0xff) ;   

      if(errno!= 0)
      {
         fprintf(stderr , "%s \012",  strerror(*__errno_location())) ; 
         bcv_scaner._value =  0; 
      }
    }

    if(scan_limite ==0) break ;  
    scan_limite+=~(scan_limite^scan_limite)  ; 
  } 
  if(!token) 
    bcv_scaner._sym_instruction='a'; 


   char  *out =  (void *)0 ; 
   switch(bcv_scaner._sym_instruction & 0xff ) 
   {
      case 'x' : 
         out = bc_hex(bcv_scaner._value); break ; 
      case 'b': 
         out = bc_bin(bcv_scaner._value); break ; 
      case 'o': 
         out = bc_oct(bcv_scaner._value); break ; 
      case 'd':
         out = bc_dec(bcv_scaner._value);break ; 
      case 'c':  
         out = bc_chr(bcv_scaner._value); break ; 
         //bcv_print(value , DEC | HEX | OCT | BIN); break ;  
      case '?':  
      case 'h': fprintf(stdout , "%s%s\12" ,  USAGE ,  BCV_VERSION_STR); break; 

      case '!': 
      case 'v': fprintf(stdout , "%s\012", BCV_STARTUP_MESG) ; break ; 
      default :
                //BCV_WARN("|-> W: Unknow operation type 'h' or '?' to print the usage\n") 
                 
         apply(fprintf(stderr ,"|-> W: Unknow operation type 'h' or '?' to print the usage\n")
             ,YELLOW) ;
         break ; 
   }
   if (!out)  
     return ;  
   //BCV_ERR() 
   apply(printf(" |-> %s\012", out) , RED) ; 
} 

void bcrepl_listen_special_cmd(const char * buffer) 
{
   char * cmd =  (char *) buffer;  
   __trimlower(cmd) ; 
    
   if(0 == strcmp(cmd, "quit") || \
      0 == strcmp(cmd, "exit")) 
     exit(0) ; 

}

void __trimlower(char* bcv_cmd) 
{
  size_t len=strlen(bcv_cmd) << 8  ; 
  int j=0; 
  char auto_format_cmd[0x14] ={0}; 

  while(  (len&0xff) <  (len >> 8)  )  
  {
     if(isspace(*(bcv_cmd+(len&0xff)) & 0xff)) 
     {
       len=-~len ; 
       continue ; 
     }
      
    *(auto_format_cmd+j++) = tolower(*(bcv_cmd+(len & 0xff))) ;  
    len=-~len ;  

  }

  bzero(bcv_cmd, (len >>8))  ; 
  memcpy(bcv_cmd , auto_format_cmd ,  j) ; 
}
