# About

Pretty much the Teenage Engineering OP-1 but worse

![doom_gif](https://user-images.githubusercontent.com/53409587/165104248-1447658f-bb47-44e4-80aa-21c08de183ec.gif)

Progress: https://wang-edward.github.io/box-(OP-1-Clone)/

# Installation

gbox currently requires:
 * bash shell
 * git
 * cmake version 3.0 or higher

## MacOS dependencies
Install xcode command line tools (if it doesn't work try install full xcode):

    xcode-select --install

Install homebrew ([brew.sh](https://brew.sh)), then:

    brew install git git-lfs cmake libsndfile
    
## Ubuntu / Debian dependencies
    sudo apt install build-essential git git-lfs cmake libsndfile1-dev libassimp-dev libasound-dev libxrandr-dev libopengl-dev libxinerama-dev libxcursor-dev libxi-dev
    
Note: requires gcc >= 7

Also, make sure to comment out line 2 in CMakeLists.txt (still might not work though)   
      
    gbox/CMakeLists.txt
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -target x86_64-apple-darwin20.3.0") # -target is for m1 mac only
      # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread") # USE THIS FOR UBUNTU/DEBIAN

## Initialization
On a bash shell:

    git clone https://github.com/wang-edward/gbox.git
    cd gbox
    ./init.sh

This will prepare the project as a fresh git repository and will add allolib and al_ext as submodules.

## How to compile / run
The src/ folder contains the initial main.cpp starter code.

On a bash shell you can run:

    ./configure.sh
    ./run.sh

This will configure and compile the project, and run the binary if compilation is successful.

Alternatively, you can open the CMakeLists.txt proeject in an IDE like VS Code, Visual Studio or Qt Creator and have the IDE manage the configuration and execution of cmake.

You can also generate other IDE projects through cmake.

## How to perform a distclean
If you need to delete the build,

    ./distclean.sh

should recursively clean all the build directories of the project including those of allolib and its submodules.
