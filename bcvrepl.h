/* @file  bcvrepl.h
 * @brief  base convertion interactive  repl  
 * @author Umar Ba <jUmarB@protonmail.com>  <github/Jukoo> 
 */ 
#if  !defined(bcv_repl_h)
#define bcv_repl_h 

#ifdef __cplusplus
# define bcvrepl_export   extern "C" 
#else 
# define bcvrepl_export  
#endif 

#include "bcv_conf.h"

#define BCV_STARTUP_MESG \
  BCV_VERSION \
  "Copyright 2025 Galsen Low Level.\n"\
  "This is free software with ABSOLUTELY NO WARRANTY.\n"

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

#define bcv_version "baseconverter version 0.1.0\nGLL Production\n"

/* @fn bcrepl_shell(const char * _Nullable) 
 * @brief  define the shell prompt 
 * @param  const char  * - if Null  the default shell prompt is used 
 * */
bcvrepl_export void 
bcrepl_shell(const char * _Nullable  __prompt)  ; 

/* @fn bcrepl_compute(const char *  _NonNullable) 
 * @brief  compute the input 
 * @param  const char * _NonNullable - buffer  
 */
bcvrepl_export void 
bcrepl_compute(const char __buffer _NonNullable)  ; 

/* @fn bcrepl_listen_cmd(const char * _NonNullable)
 * @brief listen basic command   instruction like exit quit  
 * @param  const char *  _NonNullable  - buffer 
  */ 
bcvrepl_export void __attribute__((weak))   
bcrepl_listen_special_cmd(const char __buffer _NonNullable) ; 

/* @fn __trimlower(char * _NonNullable) 
 * @brief  trim empty space left and right  and make it lower case 
 * @param  char  * command 
 */ 
static void  
__trimlower(char  __cmd _NonNullable); 



#endif //!bcv_repl_h 
