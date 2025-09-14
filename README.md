 #  Road  Intersection  Simulation  and  Visulization  
   
![Logo](https://github.com/KimangKhenng/Traffic-SImulation-and-Visualization/blob/master/Image/logo_inter.png?raw=true)  
  
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) ![Version](https://img.shields.io/badge/Qt-5.12.10-41cd52.svg) ![CMake](https://img.shields.io/badge/CMake-3.1+-blue.svg)  
  
![Binary Release Windows x86x64](https://github.com/KimangKhenng/Traffic-SImulation-and-Visualization/workflows/Binary%20Release%20Windows%20x64/badge.svg?branch=master)  
  
I've  decided  to  open-source  this  source  code  under  **GPLv3(GNU  General  Public  License,  version  3)** after  my  graduation  from  the  university.  
  
  
This  is  an  intersection  simulation  software  capable  of  generating  the  arriving  vehicles  in  many varying  controllable  rates.  The  vehicle  behavior  can  be  changed  in  realtime  in  the  following  mode:  

whether to respect  the  traffic  lights' existence,  treat  front  vehicles  as  invisible  or  not.  

**Features:**
- Cross-platform Qt5 application
- Real-time traffic simulation and visualization  
- CMake build system support for easy compilation
- Multiple build methods (CMake, qmake, Qt Creator)

**Demo** : https://www.youtube.com/watch?v=yKl4c4eQUy8```sh   
$  git  clone  https://github.com/KimangKhenng/Traffic-SImulation-and-Visualization.git   
```  
##  Gallery
![alt text](https://i.imgur.com/gXGH3w4l.png)
  
##  Tested  Systems  
I have complied the source code and test on the following systems:
  
* Windows  10 20H2 19042  
* macOS  Big Sur 11.2.1
* Ubuntu 20.04.2 LTS  
  
##  Build  Instructions  
RISV  requires  [Qt  5.0.0+](https://download.qt.io/archive/qt/)  to  compile  and  run.  The  source  code  can  be  compiled  using  one  of  these  options.  

#### Clone the source code  
```sh   
$ git  clone  https://github.com/KimangKhenng/Traffic-SImulation-and-Visualization.git  
```  

### Build with CMake (Recommended)
This project now supports CMake build system for better cross-platform compatibility.

#### Prerequisites
- **CMake 3.1.0+** - Install using your system's package manager
- **Qt 5.0.0+** - Download from [Qt Official Website](https://download.qt.io/archive/qt/)
- **GCC/Clang compiler** with C++11 support

#### Ubuntu/Linux
```sh
# Install dependencies
sudo apt update
sudo apt install cmake build-essential

# If Qt is not installed system-wide, skip this step
# sudo apt install qtbase5-dev qt5-qmake qttools5-dev libqt5svg5-dev libqt5opengl5-dev

# Clone and build
git clone https://github.com/KimangKhenng/Traffic-SImulation-and-Visualization.git
cd Traffic-SImulation-and-Visualization

# Create build directory
mkdir build && cd build

# Configure with CMake (adjust Qt path as needed)
cmake -DCMAKE_PREFIX_PATH=/path/to/your/Qt5.x.x/gcc_64 ..

# Build the project
make -j$(nproc)

# Run the application
export LD_LIBRARY_PATH=/path/to/your/Qt5.x.x/gcc_64/lib:$LD_LIBRARY_PATH
./IntersectionRoadSimulationandVisualization
```

#### Windows
```cmd
# Ensure CMake and Qt are in PATH
# Open Command Prompt or PowerShell

git clone https://github.com/KimangKhenng/Traffic-SImulation-and-Visualization.git
cd Traffic-SImulation-and-Visualization

mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH="C:\Qt\5.x.x\msvc2019_64" ..
cmake --build . --config Release

# Run the executable
Release\IntersectionRoadSimulationandVisualization.exe
```

#### macOS
```sh
# Install CMake using Homebrew
brew install cmake

git clone https://github.com/KimangKhenng/Traffic-SImulation-and-Visualization.git
cd Traffic-SImulation-and-Visualization

mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH="/path/to/Qt5.x.x/clang_64" ..
make -j$(sysctl -n hw.ncpu)

# Run the application
export DYLD_LIBRARY_PATH="/path/to/Qt5.x.x/clang_64/lib:$DYLD_LIBRARY_PATH"
./IntersectionRoadSimulationandVisualization
```

#### Creating a Launch Script (Linux/macOS)
Create a script to easily run the application:

```sh
#!/bin/bash
export LD_LIBRARY_PATH="/path/to/your/Qt5.x.x/gcc_64/lib:$LD_LIBRARY_PATH"
cd /path/to/Traffic-SImulation-and-Visualization/build
./IntersectionRoadSimulationandVisualization
```

###  Quick Run on Windows, Mac, and Linux  with  Qt  Creator  
 - Open the project with Qt Creator.  
 - Configure project with either MinGW or Visual Compiler  
 - Run  

###  Manually Build Release on Windows with MingGW 
Make sure you add ***Qt/5.XX/mingw/mingwXXX_64/bin/*** and **Qt/Tools/mingwXXX_64/bin/** to your **PATH** in system environment variables. 
 
```sh  
$ cd Traffic-SImulation-and-Visualization  
$ qmake  
$ mingw32-make  
$ mingw32-make clean  
$ cd release  
$ windeployqt --quick --no-translations .  
```

#### Common Issues and Solutions
- **Qt5 not found**: Make sure to set `CMAKE_PREFIX_PATH` to your Qt installation directory
- **Missing libraries at runtime**: Set the appropriate library path environment variable
- **Build errors**: Ensure you have C++11 compatible compiler and all Qt components are installed  
##  Contributors  
 - **KimAng Kheang**, TFD ( Software Architect, AI Developer)   
 - **Sokchea Kor**, ITED, FE, RUPP ( Advisor, Initiator)   

Interested in becoming one of the contributors? Wanna take part in our community? Send me an email detaling how you would like to add features, fixe certain part, or whatever on your mind to kimangkheang@gmail.com 
## Acknowledgement  
[![Logo](https://i.imgur.com/VRomAuU.jpg)](https://www.rupp.edu.kh/fe/) [![Logo](https://i.imgur.com/UyGOhnf.png)](https://www.rupp.edu.kh/) [![Logo](https://i.imgur.com/LW2lDla.png)](https://www.youtube.com/c/TeachingForDevelopment)  
 - Thanks to **endrll**  for providing [CQtDeployer](https://github.com/QuasarApp/CQtDeployer) packaging system to ship this software in production.
 - Thanks to **jurplel** for providing [install-qt-action](https://github.com/jurplel/install-qt-action) that helps us in creating automating build process.
