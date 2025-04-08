# @file  bcv.pxd 
# @brief base convertion pxd file 
# @author Umar Ba <jUmarB@protonmail.com> 
#cython: language_level=3

cdef extern  from "baseconv.h": 

    char * bc_bin(int __value);
    char * bc_oct(int __value);
    char * bc_hex(int __value); 
    void bc_binv2(int __value ,  int  __notation_show); 


cdef  extern from "bcvrepl.h": 
    void bcrepl_shell(const char *  __prompt);  
    void __trimlower( char * __command); 
    void bcrepl_customize(void (*__custom_prompt_shell)(const char *  __prompt) , const char  * prompt) ; 
