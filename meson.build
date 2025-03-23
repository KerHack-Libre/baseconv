# Meson project File 
# Author Umar Ba <jUmarB@protonmail.com> <github/Jukoo> 

project('bcv', 'c',
  version : '0.1',
  # TODO : Add License 
  default_options : ['c_std=gnu99','warning_level=3','bindir=/usr/local/bin'])

cc = meson.get_compiler('c') 

add_project_arguments( 
  cc.get_supported_arguments( 
     '-Wformat',
     '-Wunused-parameter',
     '-Warray-parameter'
     ) ,
  language:'c'
  )


bcv_sources=[
  'baseconv.c',  # Contain the convertion  methode 
  'bcvrepl.c'    # Contain the repl  shell 
  ]

#NOTICE : The logic  of  baseconv  is builded as External  to make it portable  to 
#         other architecture  and languages protability  
baseconv_shared_lib  = library('bcv', bcv_sources, version:'0.0.1', soversion:'1') 

executable(meson.project_name(),
           'main.c',
           link_with: baseconv_shared_lib,
           install : true)
