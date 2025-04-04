# @file setup.py 
# @brief setup configuration  to build cython package 
# @author Umar Ba <jUmarB@protonmail.com>  <github/Jukoo> 

import os 
from setuptools import setup ,Extension 
from Cython.Build import cythonize 


extension_module = [
    Extension("pybcv" , 
              language="c",
              extra_compile_args=["-std=c99"],
              sources=["bcv.pyx"],
              include_dirs=["../../" ,  "../../build"],
              library_dirs=["../../build"], 
              libraries=["bcv"], 
              runtime_library_dirs=["../../build"])
    ]
setup(
        name="Pybcv",
        ext_modules=cythonize(extension_module), 
        author="Umar ba",
        author_email="jUmarB@protonmail.com",
        version="0.1.1"
        ) 
