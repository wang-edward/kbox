#!/bin/bash

# remove existing git data
# rm -rf .git
# rm init.sh

# git init
# add allolib as a submodule
# git submodule add https://github.com/AlloSphere-Research-Group/allolib.git
# git submodule add https://github.com/wang-edward/allolib.git
# git submodule add https://github.com/AlloSphere-Research-Group/al_ext.git

git submodule update --recursive --init #--depth=50
