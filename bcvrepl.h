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

#if defined(__linux__) 
#include <term.h> 
#include <curses.h> 
/* @fn  init_tty(void) 
 * @brief  setting up terminal for curses attribute 
 * */
static inline  __attribute__((constructor)) void init_tty(void)  
{
   
  int erret = OK ; 
  if(ERR  == setupterm((void *)0 ,1, &erret)) 
  {
    fprintf(stderr , "Fail to  setup the current terminal \n"); 
    return ; 
  } 
}

#define  setaf ((TERMTYPE*)cur_term)->Strings[359] 
#define  reset ((TERMTYPE*)cur_term)->Strings[39] 

#define  __SETAF(__color)  tputs(tparm(setaf , __color) , 1 ,putchar)
#define  GREEN   __SETAF(COLOR_GREEN) 
#define  RED     __SETAF(COLOR_RED) 
#define  YELLOW  __SETAF(COLOR_YELLOW) 
#define  __reset tputs(reset,  1, putchar ) 

#define  apply(__statement , __color_attr)  \
  __color_attr;__statement; __reset 

#else /* NOTICE : NO SUPPORT FOR  WINDOW*/  

# define GREEN 
# define RED 
# define YELLOW 
# define  apply(__statement , __color_attr /*!ignored*/)  __statement
#endif   


#define BCV_STARTUP_MESG \
  BCV_VERSION_STR\
  BCV_DISCLAIMER


#define  __nptr  (void *) 0   
#define  _Nullable   
#define  _NonNullable  [static 0x1]  
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


/* @fn bcrepl_shell(const char * _Nullable) 
 * @brief  define the shell prompt 
 * @param  const char  * - if Null  the default shell prompt is used 
 * */
bcvrepl_export void 
bcrepl_shell(const char * _Nullable  __prompt)  ; 


bcvrepl_export void  
bcrepl_customize(void(*__custom_user_shell)(const char * __user_custom_prompt) ,  const char  * __prompt) ; 

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
bcvrepl_export void 
__trimlower(char  __cmd _NonNullable); 



#endif //!bcv_repl_h 
