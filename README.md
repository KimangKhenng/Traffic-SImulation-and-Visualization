 #  Road  Intersection  Simulation  and  Visulization  
   
![Logo](https://github.com/KimangKhenng/Traffic-SImulation-and-Visualization/blob/master/Image/logo_inter.png?raw=true)  
  
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) ![Version](https://img.shields.io/badge/Qt-5.12.10-41cd52.svg)  
  
![Binary Release Windows x86x64](https://github.com/KimangKhenng/Traffic-SImulation-and-Visualization/workflows/Binary%20Release%20Windows%20x64/badge.svg?branch=master)  
  
I've  decided  to  open-source  this  source  code  under  **GPLv3(GNU  General  Public  License,  version  3)** after  my  graduation  from  the  university.  
  
  
This  is  a  intersection  simulation  software  capable  of  generating  the  arriving  vehicles  in  varying  controllable  rate.  The  vehicle  behavior  can  be  changed  in  realtime  in  the  following  mode:  
  
Obey  the  traffic  lights  or  not,  treat  front  vehicles  are  invisible  or  not.  
**Demo** : https://www.youtube.com/watch?v=yKl4c4eQUy8
  
```sh   
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
RISV  requires  [Qt  5.0.0+](https://download.qt.io/archive/qt/)  to  to  complie  and  run.  The  source  code  can  be  compiled  using  one  of  these  options.  
#### Clone the source code  
```sh   
$ git  clone  https://github.com/KimangKhenng/Traffic-SImulation-and-Visualization.git  
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
##  Contributors  
 - **KimAng Kheang**, TFD ( Software Architect, AI Developer)   
 - **Sokchea Kor**, ITED, FE, RUPP ( Advisor, Initiator)   

Interested in becoming one of the contributors? Wanna take part in our community? Send me an email detaling how you would like to add features, fixe certain part, or whatever on your mind to kimangkheang@gmail.com 
## Acknowledgement  
[![Logo](https://i.imgur.com/VRomAuU.jpg)](https://www.rupp.edu.kh/fe/) [![Logo](https://i.imgur.com/UyGOhnf.png)](https://www.rupp.edu.kh/) [![Logo](https://i.imgur.com/LW2lDla.png)](https://www.youtube.com/c/TeachingForDevelopment)  
 - Thanks to **endrll**  for providing [CQtDeployer](https://github.com/QuasarApp/CQtDeployer) packaging system to ship this software in production.
 - Thanks to **jurplel** for providing [install-qt-action](https://github.com/jurplel/install-qt-action) that helps us in creating automating build process.
