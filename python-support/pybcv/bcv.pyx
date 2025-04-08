#cython: language_level=3
#Author  Umar Ba <jUmarB@protonmail.com> 

from bcv cimport * 


cpdef   bcbin(int value) :
    cdef  char * r = bc_bin(value); 
    return r.decode() ;  

cpdef   void bcbinv2(int value)  : 
    cdef int __always_show_notation =True; 
    bc_binv2(value ,  __always_show_notation) 

cpdef bcoct(int value) : 
    cdef char *r=  bc_oct(value) ;  
    return r.decode() ; 

cpdef bchex(int value) :
    cdef char * r = bc_hex(value); 
    print("hex -> ", r) ; 
    return r.decode() ; 


def  bcv_repl(*args): 
    if args.__len__().__eq__(0) :
        bcrepl_shell(NULL)
    else : 
        bcrepl_shell(args.__getitem__(0)) ;  


""" 
TODO: allow user to define his own  interactive repl 
def  bcv_custom_replshell(__callable__) : 
    def  __intergrate_callable(*argv , **kwargs) :
        if argv.__len__().__eq__(0): 
            bcrepl_customize(__callable__ , NULL) ; 
            return 
        prompt = argv.__getitem__(0) ; 
        bcrepl_customize(__callable__, prompt.encode()) ; 
        return 
    return 
"""

