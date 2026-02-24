/* @file baseconv.h 
 * @brief base convertion header 
 * @author Umar Ba <jUmarB@protonmail.com> <github/Jukoo> 
 */

#if !defined(__BASECONV)
#define  __BASECONV 

#include <stdio.h> 
#include <stdint.h> 

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


#define  BIN (0x62) 
#define  CHR (0x63<<8)
#define  OCT (0x6f<<16) 
#define  HEX (0x78<<24)
#define  DEC (0x64<<32)

#define  ALLBASE_ENABLE (BIN|CHR|OCT|HEX|DEC)  

#define MASK_BIN 0xff 
#define MASK_CHR (0xff00)>>8 
#define MASK_OCT (0Xff0000)>> 16
#define MASK_HEX (0xff000000) >> 24 
#define MASK_DEC (0xff00000000)>> 32

#define GET_BASE(TARGETED_BASE) \
  ((ALLBASE_ENABLE  & (MASK_##TARGETED_BASE)) & 0xff)



#define BYTE_UNIT sizeof(void *)  
#define _SIZE(__value)  sizeof(__value) * BYTE_UNIT  
#define BITSET(__value , __index)  (  ((__value) >> (__index -1 ))   & 0x1)
#define SHOWBITREP(__expr) printf("%i",__expr)  

#define SHOWBASE_EXPR(__expr, __it , __prefix ,__fmt, __out){\
  strcat(__out , __prefix); \
  size_t i =strlen(__prefix); \
  while(0 != __it){\
    sprintf( (__out+i) ,__fmt, *(__expr+ __it-1));\
    __it+=~0,  i=-~i ;\
  }\
  }


#define SHOWHEX(__expr, __it ,__out) \
  SHOWBASE_EXPR(__expr ,__it, "0x","%c", __out) 

#define SHOWOCT(__expr ,__it , __out) \
  SHOWBASE_EXPR(__expr ,__it, "0o","%i", __out) 
  
#define SHOWBIN(__expr , __it,__out)\
  SHOWBASE_EXPR(__expr ,__it, "0b","%i",  __out) 


#define  UMAX_LONG   ~((0ULL)>>1) 
#define  bcv_out(__expression ,__annotation) \
      fprintf(stdout , "%s: %s\012", #__annotation ,  __expression)   



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

__extension__ 
typedef  unsigned long long int  uf64_t  ; 

struct __bcb_t 
{
  char _buff[0xff]; 
  int  _index ; 
};

//!TODO : Use memory stream  instead
extern char bc_global_buffer[0xff] ; 
extern  uf64_t __allbase_enable__;    


/* @fn detect_bit_section_starting_group(int) 
 * @brief  detect wich section group of binary  contain the first value  
 *         e.g  0000.0000.0000.0010.0000.0111  
 *              |xxxxxxxxxxxxx|--------------|
 *                  escaped     conserved 
 *         This function is used by bc_binv2 
 * @param  int - the value 
 * @return int - the section(th) index that contain the value 
 */
static __inline__ int detect_bit_section_starting_group(uf64_t  value) 
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
   static unsigned char  i =~0;
   if (!( (i=-~i)^4)) 
     putchar(__symbole_sep) , i&=~i;  
  
}  

/* @fn __common_prototype_base_convertion(int  , int  , struct __bcb_t*) 
 * @brief  common logic  used by the bc_* function to convert  
 * @param  int  - the value 
 * @param  int  - the base 
 * @param  struct __bcb_t *  - bcb data structure  hold the buffer in  the length 
 */ 
static void __common_prototype_base_convertion(uf64_t  value , int base ,  struct __bcb_t  *  bcb)  
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

///////!NOTE : for all the different variations of the ASCII table,
//             Only  printable characters, represent letters, digits, punctuation marks, and a few miscellaneous symbols.
//             You will find almost every character on your keyboard.
/////!WARNING : The extended ASCII code are not yet supported 

static __inline__ unsigned char  is_printable(const char *character) 
{
  unsigned char ascii_code =  (*character & 0xff) ; 
  return (0x20 < ascii_code)? (0x7ff >  ascii_code)  : 0; 
}
/* the exposed function */  


/* @fn bc_binv2(int  , int ) 
 * @brief  binray  convertion  version 2 
 * @param   int  -  the value  
 * @param   int  -  would doyou like to show annotation dot "."
 */ 
__BCX(void) bc_binv2(uf64_t  __value, int __show_notation) ; 

__BCX(char *) bc_bin(uf64_t  value) ;  
__BCX(char *) bc_oct(uf64_t  value) ; 
__BCX(char *) bc_hex(uf64_t  value) ; 
__BCX(char *) bc_dec(uf64_t  value) ; 
__BCX(char *) bc_chr(uf64_t  value) ;
__BCX(void)   bcv_print(uf64_t value) ;  
__BCX(void) bcv_guess_base(const char * rawinput) ; 


#endif //!__BASECONV 
