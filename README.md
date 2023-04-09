# Game Programming in C++ Code

This repository contains the source code for *Game Programming in C++* by Sanjay Madhav.

The source code for the chapters is released under the BSD 3-clause
license. See LICENSE for more details. Note that this license does not apply to
the code in the External directory. Each External project is licensed separately.

# Building the Code

To compile on Linux(Tested on Debian), install [SDL](https://wiki.libsdl.org/SDL2/Installation).  
On debian libsdl2-dev, libsdl2-image-dev packages and other developer packages like Make, and clang(I rather prefer than gcc).   

For now, I am just adding support for Makefiles.   
You can just do `make -j${processors_number}` that will compile all the available chapters. 

- [make -j\<ProcessorsNumber\> flag](https://www.gnu.org/software/make/manual/html_node/Parallel.html)


Code for Chapter 7 and beyond uses the FMOD API for audio. This requires
a separate installation from (https://www.fmod.com/download). Download
and install version 1.09.x of the FMOD Studio API (newer versions are untested).


