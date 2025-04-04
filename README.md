# Baseconv  <img src="https://img.shields.io/badge/With%20Python%20Support-yellow?style=for-the-badge&logo=python" width="152"  height="" alt="Python-Support" style="margin-right:20px"  align="right"/>

Converts to different numerical bases such as binary (2), octal (8)  and hexadecimal (16)  with built-in interactive shell. 

- base 2 -> for binary representation 0 to 1  
- base 8 -> for octal representation 0 to 7 base 
- base 16 -> for hexadecimal representation 0 to 15 (f) 

#### Setting Up Ecosystem or Testing Environment 

There are two alternatives:  

**1** - Build On your direct host 

**2** - Or on a dedicated environment (for testing and a quick tour).  

**The ecosystem chosen to build the project is based on the [meson build system](https://mesonbuild.com/index.html)**

1 - Direct Host 
---
It is therefore strongly recommended to have meson build available on your machine.
Here are a few commands to type 
```bash 
$ > meson setup build # to build the project 
$ > meson compile -C build # to compile the project  
```
The Executable w'ill be stored in build directory `./build/bcv`  

2 - Pre-build or Dedicated Environment 
---  
By the way, there's already a minimalistic **pre-build environment** for those who want to test in Docker or Chroot.
As you may have noticed, there's no Docker file in the repository, because we want to launch the environment quickly 
without doing a full Docker command. 

We've already provided a script to export the environment to a local Docker image.~(no Docker build , no Docker pull  no Docker anything)~
Here's a script named `build_context.sh` in the `context` directory. 
Just run the script. 
```bash 
# go to the context directory and I assume you've given the right permission 
$ > ./build_context.sh 
```  
To clarify This  script  export the `rootfs.tar.xz` archive  directly to  Local Docker images and at the end generate a folder named `rootfs`,
that you can use also. See (2- A Change Root or ...). 

This script will generate 2 environments of your choice: 
1 - docker image directly available on your host, no need to docker pull 
just run... 
```bash 
$ docker run -ti bcv:testing bash # to run
``` 
2 - A Change Root or chroot environment is available in most Unix environments. 
    After `build_context.sh` has finished running, a `rootfs` directory will be available. 

To lock in : 
```bash 
$ > sudo  chroot rootfs bash 
``` 
And there you are!  The command is available in whole environment 
just type  `bcv -h` 

See [USE](#USE) section bellow for more info .

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
