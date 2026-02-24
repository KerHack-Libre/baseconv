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

     //!BCV_SUCCESS()
     apply( printf(bpf, line,  prmpt , bcrepl_symbole_prompt) , GREEN) ;  

     if(!(fgets(prompt_buffer ,  bcrepl_buffer_limit, stdin)))
       continue ; 
    
     char *n  = strchr(prompt_buffer , 0xa) ;
     if (n)  *n  = 0;    
     
     if (0==strlen(prompt_buffer)) continue ; 
     bcrepl_compute(prompt_buffer) ; 
     
     bzero(prompt_buffer , bcrepl_buffer_limit) ; 
     fflush(stdin) ; 
   }
   exit(EXIT_SUCCESS) ; 
} 

void bcrepl_customize(user_prompt_custom_shell  custom_prompt  ,  const char *   prompt) 
{
  if(!custom_prompt) 
  {
     bcrepl_shell( prompt )  ; 
     return ; 
  }
     
  custom_prompt(prompt) ; 
} 

char * bcrepl_token_search(const char *  bcrpl_inline_buffer) 
{
  const char token_list[]= BCVRPL_SEPS ; 
  char *token_found = 00 ; 
  unsigned int i = 0 ; 
  
  while(!(token_found = strchr(bcrpl_inline_buffer , *(token_list+i)))) i=-~i ;  
  
  return token_found ; 
}


static uf64_t   bcrepl_analyse_braw(const char *  raw_buffer) 
{
  uf64_t value = strtol(raw_buffer ,  00 , 10); 
  if (!value  &&  is_printable(raw_buffer))
    value = *raw_buffer & 0xff ;  

  return value ; 
}
  
void bcrepl_compute(const char * buffer) 
{

  char *should_be_tokinezed  = 00, 
       *buffer_clone = (char*) buffer , 
       toksymb = 0 ; 

  uf64_t vtok =0 , value =0 ; 

  bcrepl_listen_special_cmd(buffer) ;  
  should_be_tokinezed = bcrepl_token_search(buffer_clone) ;  
  if(0 < strlen(should_be_tokinezed)) 
    vtok = bcrepl_process(buffer_clone , *(should_be_tokinezed) & 0xff);  
  else  
  { 
    value = bcrepl_analyse_braw(buffer_clone);  
    value ?  bcv_print(value) :  bcv_guess_base(buffer_clone) ; 
    bcrepl_show_helper(buffer_clone) ;  
     
    return ;  
  }

  toksymb = (vtok >> 0x20) & 0xff ;
  value = (vtok & 0xffffffff);  
  
  if(!toksymb) 
  {
    bcv_print(value) ; 
    return ; 
  }  


  //bcrepl_inline_out_convertion(toksymb) ; 
   char  *out =  (void *)0 ; 
   switch( toksymb ) 
   {
      case 'x' : 
         out = bc_hex(value); break ; 
      case 'b': 
         out = bc_bin(value); break ; 
      case 'o': 
         out = bc_oct(value); break ; 
      case 'd':
         out = bc_dec(value); break ; 
      case 'c':  
         out = bc_chr(value); break ;  
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


uf64_t bcrepl_process(const char * buffer , const char ftokn) 
{ 
  char *token = 00,  *buffer_clone = (char *) buffer , 
       scan_limite=3; 
  uf64_t vtok=0; 
  
  
  while( --scan_limite && __nptr != (token = strtok(buffer_clone,  (const char []) { ftokn , 00 } )))
  {
    if(buffer_clone) buffer_clone=00;  

    if(2 == scan_limite)  
    {
      char *s = 0 ; 
      asprintf(&s , "%i" ,  (*token & 0xff)) ; 
      vtok= (uf64_t) strtol(s, 00 , 0xa) << 0x20;  
      free(s) , s=0 ;  
    }
    else 
      vtok|=(uf64_t)(strtol(token , __nptr , 0xa))  ; 
  }
  return vtok ;
}

static void bcrepl_show_helper(const char  repl_buffer[static 1]) 
{
  switch( *repl_buffer  & 0xff)
  {
    case '?':  
    case 'h': fprintf(stdout , "%s%s\12" ,  USAGE ,  BCV_VERSION_STR); break; 
    case '!': 
    case 'v': fprintf(stdout , "%s\012", BCV_STARTUP_MESG) ; break ;   
  }

}
