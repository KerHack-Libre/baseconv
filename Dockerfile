#

FROM  python:3.13.2-alpine3.21
MAINTAINER    Umar Ba <jUmarB@protonmail.com>  <github/Jukoo>  

RUN apk add --no-cache  gcc meson musl-dev bash  &&\
pip install --no-cache-dir --upgrade pip setuptools wheel cython   

ADD   ./  baseconv/  

WORKDIR  baseconv  
 
# build and install bcv  
RUN  meson setup  build  &&  meson  compile -C  build  
RUN  meson install -C build  

# build for python3 support package 
WORKDIR   python-support 

RUN  chmod +x  build.sh & ./build.sh 

WORKDIR  /baseconv  
CMD ["bcv"]
