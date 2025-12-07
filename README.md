# input-remapper

### Build guide

This install guide will be aimed at MinGW users. 

#### 1. Install SDL3
https://wiki.libsdl.org/SDL3/README-windows
tip (mingw) Install this MinGW package `mingw-w64-x86_64-toolchain` to install prereqs

#### 2. Install SDL3_image

https://github.com/libsdl-org/SDL_image/releases

On MinGW, download lib, extract tarball, and run `make`. 

Follow their instructions.


#### 3. Set SDL3_DIR env variable to your SDL install dir


#### 4. Run `cmake --build .`

#### 5. Run my executable to launch the program

`./mapper.exe`

