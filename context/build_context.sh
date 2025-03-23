#!/bin/bash 
#+ This File is dedicated for building context 
#+ The building context  allow Testers or users 
#+ to launch a quick isolated environment and secure 
#+ Author Umar Ba <jUmarB@protonmail.com> <github/jukoo> 
#-------------------------------------------------------
# Please make sure  to have tar and xz package for extraction  
# 

readonly target_rootfs_file="rootfs.tar.xz"
readonly image_name="bcv:testing"

context_folder=$1  

if [[ -z ${context_folder} ]]  ; then 
   # If no argument was give it'll search for context  file  
   context_folder=${target_rootfs_file}  
   [[ -f ${context_folder} ]] || { 
     echo  -e "Looking  for Context folder but missing : specify the new context folder as argument " 
     exit 1  
   } 
   # TODO :  check if is a valid context folder 
fi 

[[ "Deprecated ::  NOTE:: TO be Remove on next release" ]]
virtual_rootfs_extraction()
{
  echo -e "Please Wait ..." 
  echo -n "Making virtual rootfs extraction ["
  tar -Jxf  $1  --checkpoint=100 --checkpoint-action=dot 
  test $? -eq 0   || {
    echo -e "Fail to make extraction"
  } && {
    echo -e "] [\x1b[1;32mDONE\x1b[0m]"
  }
}

[[ "This Build context for docker environment" ]]
build_context_for_docker() 
{  
   local context_dir=$1 
   virtual_rootfs_extraction ${context_dir}  
   local rootfs=${context_dir%.tar*}
   if [[ -d  ${rootfs}  ]] ; then 
     echo -ne "Importing to Docker Images Registry:\n\t|-> Will be  saved as <\x1b[1;33m${image_name}\x1b[0m>\n\t|"
     tar -C  ${rootfs}  -c . --checkpoint=.50 | docker import - ${image_name} 2>&1 /dev/null
     test  $? -eq 0  && {
       echo -en  "\r[\x1b[1;32mDONE\x1b[0m]"
       echo -e   "\t-> New Docker image available <${image_name}>"  
       echo -e   "\t-> Type  docker images  to  see it" 
       echo -e   "\t-> Launch it in interactive  mode e.g :\n\t\t\x1b[3;5;35m docker run -it ${image_name} bash\x1b[0m" 
     }||{
        echo -e "Fail to Export to Docker"  
        exit 1 
     }
   fi
} 

build_context_for_docker ${context_folder} 
