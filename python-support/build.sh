#!/bin/bash 

set -o errexit 

readonly target_dirent="pybcv"

## --- create virtual env  --- 
printf "Creating virtual environment  <.dist>\n"
python3 -m venv .dist  

## ---- launch the virtual env --- 

printf "Quick activation virtual env"
source .dist/bin/activate  

printf "Installing requirements ... please wait\n"
python3 -m pip  install -r  ${target_dirent}/requirements.txt 


printf "Building Cython  module for bcv \n"
cd ${target_dirent} 
test $? -eq 0 ||  exit 1  

##---- Build Cython  module extension --- 
python3  setup.py build_ext --inplace  

##---  installing package  in virtual env 

printf "Installing module for current virtual environment modules"
python3 setup.py  install  

## ---- 
cat << ER 
Your environement is Ready 
HINTS : source .dist/bin/activate
Happy Hacking! :) 
ER
