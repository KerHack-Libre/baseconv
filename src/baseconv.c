/* @file baseconv.c 
 * @brief base convertion  (base 2-8-16)
 */ 
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "baseconv.h" 

char bc_global_buffer[0xff]={0} ;  
uf64_t __allbase_enable__ = (BIN|CHR|OCT|HEX|429496729600);   

char *  bc_hex( uf64_t value) 
{ 
  bzero(bc_global_buffer, 0xff) ; 
  struct __bcb_t  xrep ={0};   
  __common_prototype_base_convertion(value , 0x10, &xrep) ; 
   SHOWHEX(xrep._buff , xrep._index , bc_global_buffer) ; 
   return bc_global_buffer ;  
}
char * bc_oct(uf64_t value)
{
   bzero(bc_global_buffer, 0xff) ; 
   struct __bcb_t  orep = {0} ;  
   __common_prototype_base_convertion(value , 0x8, &orep) ;  
   SHOWOCT(orep._buff , orep._index  , bc_global_buffer) ; 
   return  bc_global_buffer; 
}

char * bc_bin(uf64_t value) 
{ 
   bzero(bc_global_buffer, 0xff) ; 
   struct __bcb_t  brep ={0};  
   __common_prototype_base_convertion(value , 0x2 , &brep) ; 
   SHOWBIN(brep._buff , brep._index , bc_global_buffer) ;  
  
   return bc_global_buffer ; 
}

char * bc_dec( uf64_t value) 
{
  bzero(bc_global_buffer , 0xff); 
  sprintf(bc_global_buffer,  "%i" ,  value); 
  return bc_global_buffer ; 
}

char * bc_chr( uf64_t value)  
{ 
  size_t byte_size = _SIZE(value) >> 1 ;//! only take  32 bit   
  unsigned char  i = ~7 ,  
                 offset_idx = 0;   
  bzero(bc_global_buffer , 0xff);  
  while ( (i < byte_size) ,  i+=-~7) ;  
  { 
    sprintf((bc_global_buffer+offset_idx), "%c" , (value>>i)  & 0xff) ; 
    offset_idx=-~offset_idx; 
  }  
  
  return bc_global_buffer ;
}
void  bc_binv2( uf64_t value , int show_notation) 
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

