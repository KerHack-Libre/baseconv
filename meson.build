# Meson project File 
# Author Umar Ba <jUmarB@protonmail.com> <github/Jukoo> 

project('bcv', 'c',
  version : '1.0.1',
  # TODO : Add License 
  default_options : ['c_std=gnu99','warning_level=3','bindir=/usr/local/bin'])

bc_short_disclaimer='Copyright(c) 2025 KerHack-Libre.\\012This is free software with ABOSLUTELY NO WARRANTY\\012'


data = configuration_data()  
data.set_quoted('BCV_VERSION',meson.project_version()) 
data.set_quoted('BCV_DISCLAIMER', bc_short_disclaimer) 
data.set_quoted('BCV_VERSION_STR', 'bcv version '+meson.project_version()+'\\012')
data.set_quoted('BCV_VERSTRLONG' , 'baseconverter  version '+meson.project_version()+' by KerHack-Libre')

configure_file( 
  output: 'bcv_conf.h', 
  configuration: data  
  ) 

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


curses_dep =  dependency('curses')
bcv_sources=[
  'baseconv.c',  # Contain the convertion  methode 
  'bcvrepl.c'    # Contain the repl  shell 
  ]

#install_man(['manpage/bcv.1'])
#
#NOTICE : The logic  of  baseconv  is builded as External Shared and static library
#         to make it more extensible 
baseconv_shared_lib  = both_libraries('bcv', bcv_sources, version:meson.project_version(), soversion:meson.project_version(),dependencies:curses_dep, install:true) 

executable(meson.project_name(),
           'main.c',
           link_with: baseconv_shared_lib,
           dependencies:curses_dep,
           install : true)
