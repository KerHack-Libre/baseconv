# Meson project File 
# Author Umar Ba <jUmarB@protonmail.com> <github/Jukoo> 

project('bcv', 'c',
  version : '0.1.1',
  # TODO : Add License 
  default_options : ['c_std=gnu99','warning_level=3','bindir=/usr/local/bin'])

cc = meson.get_compiler('c') 

pkg=import('pkgconfig')
add_project_arguments( 
  cc.get_supported_arguments( 
     '-Wformat',
     '-Wunused-parameter',
     '-Warray-parameter'
     ) ,
  language:'c'
  )


configure_file( 
  output: 'bcv_conf.h', 
  configuration: { 
    'BCV_VERSION': '"bcv version 0.1.1 "' 
    } 
  ) 

curses_dep =  dependency('curses')
bcv_sources=[
  'baseconv.c',  # Contain the convertion  methode 
  'bcvrepl.c'    # Contain the repl  shell 
  ]

#NOTICE : The logic  of  baseconv  is builded as External Shared and static library
#         to make it more extensible 
baseconv_shared_lib  = both_libraries('bcv', bcv_sources, version:meson.project_version(), soversion:meson.project_version(),dependencies:curses_dep, install:true) 

executable(meson.project_name(),
           'main.c',
           link_with: baseconv_shared_lib,
           dependencies:curses_dep,
           install : true)
