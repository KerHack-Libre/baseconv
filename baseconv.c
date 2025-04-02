/* @file baseconv.c 
 * @brief base convertion  (base 2-8-16)
 */ 
#include <stdlib.h>
#include <stdio.h> 
#include <limits.h> 

#include "baseconv.h" 

void  bc_hex(int value) 
{ 
  struct __bcb_t  xrep ={0};   
  __common_prototype_base_convertion(value , 0x10, &xrep) ; 
   SHOWHEX(xrep._buff , xrep._index) ;  
}
void bc_oct(int value)
{
   struct __bcb_t  orep = {0} ;  
   __common_prototype_base_convertion(value , 0x8, &orep) ; 
   SHOWOCT(orep._buff , orep._index) ;  
}

void bc_bin(int value) 
{ 
   struct __bcb_t  brep ={0};  
   __common_prototype_base_convertion(value , 0x2 , &brep) ; 
   SHOWBIN(brep._buff , brep._index) ;  
} 

void bc_binv2(int value , int show_notation) 
{ 
  int section_bin=_SIZE(value)-(detect_bit_section_starting_group(value) *4);
  while (  0 < section_bin  ) 
  {  
     if(show_notation >0)
        print_symbol_seperation() ; 
     
     SHOWBITREP(BITSET(value , section_bin)); 
     section_bin+=~(section_bin^section_bin) ;  
  }

  puts("") ; 
}
