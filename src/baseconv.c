/* @file baseconv.c 
 * @brief base convertion  (base 2-8-16)
 */ 
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "baseconv.h" 

char bc_global_buffer[0xff]={0} ;  

char *  bc_hex(int value) 
{ 
  bzero(bc_global_buffer, 0xff) ; 
  struct __bcb_t  xrep ={0};   
  __common_prototype_base_convertion(value , 0x10, &xrep) ; 
   SHOWHEX(xrep._buff , xrep._index , bc_global_buffer) ; 
   return bc_global_buffer ;  
}
char * bc_oct(int value)
{
   bzero(bc_global_buffer, 0xff) ; 
   struct __bcb_t  orep = {0} ;  
   __common_prototype_base_convertion(value , 0x8, &orep) ;  
   SHOWOCT(orep._buff , orep._index  , bc_global_buffer) ; 
   return  bc_global_buffer; 
}

char * bc_bin(int value) 
{ 
   bzero(bc_global_buffer, 0xff) ; 
   struct __bcb_t  brep ={0};  
   __common_prototype_base_convertion(value , 0x2 , &brep) ; 
   SHOWBIN(brep._buff , brep._index , bc_global_buffer) ;  
  
   return bc_global_buffer ; 
}

char * bc_dec(int value) 
{
  bzero(bc_global_buffer , 0xff); 
  sprintf(bc_global_buffer,  "%i" ,  value); 
  return bc_global_buffer ; 
}

void  bc_binv2(int value , int show_notation) 
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

