""" 
This file is an example  
"""
from pybcv  import  *  


def main(): 
    r= bchex(33)     # convert 33  to hexadecimal  representation 
    print("-> hex :: " , r ) 
    bcbinv2(100)  # convert 12 to binary notation with dot separation  
    
    out = bcbin(12)     # convert 12 to binary notation 
    print("-> bin :: ", out)
    r = bcoct(392)    # convert 392 to octal  representation 
    print("-> oct :: ", r) 

    print("----------------------------------------") 
     
    bcv_repl()    # Launch interactive console   

if __name__.__eq__("__main__") : 
    main()

