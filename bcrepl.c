/* @file  bcrepl.c
 * @brief  base convertion  with interactive  repl  
 * @author Umar Ba <jUmarB@protonmail.com>  <github/Jukoo> 
 */ 


#define __USE_GNU  
#include <stdlib.h> 
#include <stdio.h>
#include <libgen.h>
#include <errno.h>  
#include <string.h>
#include <err.h>
#include <ctype.h> 
#include <unistd.h> 
#include "baseconv.h" 

#define bcv_version "baseconverter version 0.1\nGLL Production\n"

#define  _Nullable   
#define  _NonNullable  [static 0x1]  
#define  __nptr  (void *) 0   
#define  bcrepl_symbole_prompt  0x3e 
#define  bcrepl_buffer_limit    0x50
#define  __bcrepl_prompt_format  "[%i] %s %c "
#define  bpf __bcrepl_prompt_format  

#define  __USE_PROGNAME  0 
extern char * program_invocation_short_name ; 
#if __USE_PROGNAME 
# define  pname   program_invocation_short_name 
#else 
# define  pname  "bcv" 
#endif 
 

#define  USAGE "\
Usage : bcv [OPTION] ... <NUMBER>\n\
Convert Number to specific base\n\
-b,  Convert to binary Base\n\
-x,  Convert to hexadecimal Base\n\
-o,  Convert to Octal Base\n\
-v,  Version of the Program\n\
-h,  Print  this help\n\
"

/* @fn bcrepl_shell(const char * _Nullable) 
 * @brief  define the shell prompt 
 * @param  const char  * - if Null  the default shell prompt is used 
 * */
void bcrepl_shell(const char * _Nullable  __prompt)  ; 

/* @fn bcrepl_compute(const char *  _NonNullable) 
 * @brief  compute the input 
 * @param  const char * _NonNullable - buffer  
 */
void bcrepl_compute(const char __buffer _NonNullable)  ; 

/* @fn bcrepl_listen_cmd(const char * _NonNullable)
 * @brief listen basic command   instruction like exit quit  
 * @param  const char *  _NonNullable  - buffer 
  */ 
static  void  bcrepl_listen_cmd(const char __buffer _NonNullable) ; 

/* @fn __trimlower(char * _NonNullable) 
 * @brief  trim empty space left and right  and make it lower case 
 * @param  char  * command 
 */ 
static void  __trimlower(char  __cmd _NonNullable); 

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

void bcrepl_shell(const char *  prompt)
{
   const char * prmpt =  !prompt ? pname :  prompt ;  
   int proceed =1 ; 
   char prompt_buffer[bcrepl_buffer_limit]={0}; 
   int  line = 0; 
   while (proceed, ++line) 
   { 
     printf(bpf, line,  prmpt , bcrepl_symbole_prompt) ;  
     if(!(fgets(prompt_buffer ,  bcrepl_buffer_limit, stdin)))
       continue ; 
    
     char *n  = strchr(prompt_buffer , 0xa) ;
     if (n)  *n  = 0;    
     
     bcrepl_compute(prompt_buffer) ; 
     /* NOTICE :always clean the repl buffer */
     bzero(prompt_buffer , bcrepl_buffer_limit) ; 

     fflush(stdin) ; 
   }
} 


void bcrepl_compute(const char * buffer) 
{

  bcrepl_listen_cmd(buffer) ; 
  struct bcv_parse_t {
     char  _sym_instruction:8;  
     int _value ; 
  }  bcv_scaner = { 0,0 };  

  char *buffer_clone =  (char *) buffer, 
       *token = __nptr  ; 
  int  scan_limite= 2 ; 
  while( __nptr != (token = strtok(buffer_clone , "/" ))) 
  {
    if(scan_limite & 0b10) 
    {
       bcv_scaner._sym_instruction= (char) *token  & 0xff ;  
       buffer_clone = __nptr; 
    }
    if(scan_limite & 0b01)
      bcv_scaner._value = strtol(token , __nptr  , 0xa) ;  

    if(scan_limite ==0) break ;  
    scan_limite+=~(scan_limite^scan_limite)  ; 
  }

  if(0==bcv_scaner._value) 
    return ;  //!TODO :  print message instead 

   printf(" |-> "); 
   switch(bcv_scaner._sym_instruction & 0xff ) 
   {
      case 'x' : 
         bc_hex(bcv_scaner._value); break ; 
      case 'b': 
         bc_binv2(bcv_scaner._value, 1); break ; 
      case 'o': 
         bc_oct(bcv_scaner._value); break ; 
      default : 
         warn("Unknow operation") ;
         break ; 
   }
} 

static void bcrepl_listen_cmd(const char * buffer) 
{
   char * cmd =  (char *) buffer;  
   __trimlower(cmd) ; 
    
   if(0 == strcmp(cmd, "quit") || \
      0 == strcmp(cmd, "exit")) 
     exit(EXIT_SUCCESS) ; 

}

static void __trimlower(char* bcv_cmd) 
{
  int len  = strlen(bcv_cmd) , i =~0, j=0 ;  
  char auto_format_cmd[0x14] ={0}; 

  while( ++i < len )  
  {
     if(isspace(*(bcv_cmd+i) & 0xff)) 
       continue ; 
      
    *(auto_format_cmd+j++) = tolower(*(bcv_cmd+i)) ;  
  }

  bzero(bcv_cmd, len) ; 
  memcpy(bcv_cmd , auto_format_cmd ,  j) ; 
}
