""" 
This file is an example  
"""
from pybcv  import  *  


def main(): 
    bcbin(12)     # convert 12 to binnary notation 
    bcbinv2(100)  # convert 12 to binnary notation with  dot separation  
    bcoct(392)    # convert 392 to octal  repesentation 
    bchex(33)     # convert 33  to hexadecimal  representation 
    print("----------------------------------------") 
     
    bcv_repl()    # Launch interactive console   

if __name__.__eq__("__main__") : 
    main()

