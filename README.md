# baseconv

Converts to different numerical bases such as binary (2), octal (8)  and hexadecimal (16)  with built-in interactive shell. 


- base 2 -> for binary representation 0 to 1  
- base 8 -> for octal representation 0 to 7 base 
- base 16 -> for hexadecimal representation 0 to 15 (f) 

#### Use

There are 2 modes of use 
An interactive mode &  Simple command-line mode 

*Simple Command-line mode 

just do  
```bash 
bcv [option] <numeric value> 
```  
e.g 
```bash 
$ bcv -o 12 # for octal representation  
``` 

> Type `bcv -h` to display help. 


*For interactive mode  

If no argument is supplied, interactive mode is launched by default. 
here's an example: 

```bash 
$ bcv -b/<number>  
$ bcv -o/<number> 
$ bcv -x/<number>   
```
e.g: 

```bash 
$ bcv # launch in interactive mode 

[1] bcv > x/100
     |-> 0x64
[2] bcv > b/100
     |->0b0110.0100
[3] bcv > ...
```

*To exit, type quit or exit (not case-sensitive).

Feel free to contribute or declare issue to improve  the repository 

We ❤️  Computers at all Levels. 

From Senegal. 🇸🇳
