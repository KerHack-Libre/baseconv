/* @file baseconv.h 
 * @brief base convertion header 
 * @author Umar Ba <jUmarB@protonmail.com> <github/Jukoo> 
 */

#if !defined(__BASECONV)
#define  __BASECONV 

#include <stdio.h> 
#if defined(__linux__) 
# if __glibc_has_attribute(warn_unused_result)  
#   define  __mustcheck __attribute__((warn_unused_result)) 
# else
#   define  __mustcheck /*  NOTHING */ 
# endif // __glibc_has_attribute 
#else  
# define  __mustcheck  /* NOTHING */ 
#endif //! __linux__  

#if defined(__cpluscplus)
# define  __BCEXPORT  extern "C" 
#else 
# define  __BCEXPORT  /* !NOTHING */ 
#endif 

#define  __BCX(__type_return_function)\
  __BCEXPORT __type_return_function 

#if !defined(__symbole_sep)   
# define __symbole_sep  0x2e  
#endif  


#define BYTE_UNIT sizeof(void *)  
#define _SIZE(__value)  sizeof(__value) * BYTE_UNIT  
#define BITSET(__value , __index)  (  ((__value) >> (__index -1 ))   & 0x1)
#define SHOWBITREP(__expr) printf("%i",__expr)  

#define SHOWBASE_EXPR(__expr, __it , __prefix ,__fmt, __out){\
  strcat(__out , __prefix); \
  int i =strlen(__prefix); \
  while(0 != __it){\
    sprintf( (__out+i) ,__fmt, *(__expr+ __it-1));\
    __it+=~(__it^__it),  i=-~i ;\
  }\
  }

#define SHOWHEX(__expr, __it ,__out) \
  SHOWBASE_EXPR(__expr ,__it, "0x","%c", __out) 

#define SHOWOCT(__expr ,__it , __out) \
  SHOWBASE_EXPR(__expr ,__it, "0o","%i", __out) 
  
#define SHOWBIN(__expr , __it,__out)\
  SHOWBASE_EXPR(__expr ,__it, "0b","%i",  __out) 


#define  USAGE "\
  Usage : bcv [OPTION] ... <NUMBER>\n\
  Convert Number to specific base\n\
  inline      | interactive | description\n\
  -b <number>   b/<number>    Convert to binary Base\n\
  -x <number>   x/<number>    Convert to hexadecimal Base\n\
  -o <number>   o/<number>    Convert to Octal Base\n\
                exit or quit  To exit  interactive shell\n\
  ---------\n\
  -v, 'v' or '!' Version of the Program\n\
  -h, 'h' or '?' Print  this help\n\
  "

struct __bcb_t 
{
  char _buff[0xff]; 
  int  _index ; 
};

extern char bc_global_buffer[0xff] ; 

/* @fn detect_bit_section_starting_group(int) 
 * @brief  detect wich section group of binary  contain the first value  
 *         e.g  0000.0000.0000.0010.0000.0111  
 *              |xxxxxxxxxxxxx|--------------|
 *                  escaped     conserved 
 *         This function is used by bc_binv2 
 * @param  int - the value 
 * @return int - the section(th) index that contain the value 
 */
static __inline__ int detect_bit_section_starting_group(int value) 
{
  
  size_t vsize =  _SIZE(value) ; 
  int group = 0 , section = 1, section_start_bit =0 ; 
  while( 0 < vsize  )   
  { 
    if(group == 4)
    { 
       group&=~group ; 
       section=-~section; 
    } 
    section_start_bit = BITSET(value , vsize) ;  
    if (section_start_bit == 1)  
        break ; 

    group=-~group ; 
    vsize+=~(vsize^vsize);
  }

  return section +(~0);  

}

/* @fn print_dot() 
 * @brief  Just print "."  e.g : 0000.0000. ..... 
 *         This function is used by bc_binv2 
 */
static __inline__ void print_symbol_seperation(void) 
{
   static int i = 0;
   if (i==4)
   {
     printf("%c",  __symbole_sep) ;
     i&=~i ; 
   }
   i=-~i; 
}  



/* @fn __common_prototype_base_convertion(int  , int  , struct __bcb_t*) 
 * @brief  common logic  used by the bc_* function to convert  
 * @param  int  - the value 
 * @param  int  - the base 
 * @param  struct __bcb_t *  - bcb data structure  hold the buffer in  the length 
 */ 
static void __common_prototype_base_convertion(int value , int base ,  struct __bcb_t  *  bcb)  
{ 
   int  remain  = 0;  
   while (0!= value) 
   {
     remain = value % base, value/=base ; 
     if(base ==  0x10) 
       remain+=  0xa > remain? 0x30 : 0x37 ;  

     *(bcb->_buff+bcb->_index++) =  remain ; 
   } 
}

/* the exposed function */  


/* @fn bc_binv2(int  , int ) 
 * @brief  binray  convertion  version 2 
 * @param   int  -  the value  
 * @param   int  -  would doyou like to show annotation dot "."
 */ 
__BCX(void) bc_binv2(int __value, int __show_notation) ; 

__BCX(__mustcheck char *) bc_bin(int value) ;  
__BCX(__mustcheck char *) bc_oct(int __value) ; 
__BCX(__mustcheck char *) bc_hex(int __value)  ; 



#endif //!__BASECONV 
