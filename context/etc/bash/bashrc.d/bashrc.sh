# .bashrc

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

declare  symbol_level_access="$" 

if [[ ${UID} -eq 0 ]] ; then 
  symbol_level_access="#"
fi 
alias ls='ls --color=auto'

export  PATH="/bin:/usr/local/bin:/usr/bin"
PS1='${symbol_level_access}<\033[1;2;36m\W\033[0m>:: '
