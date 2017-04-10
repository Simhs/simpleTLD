# Introduction

파이썬에서 TLD코드를 사용하고자 openTLD 코드를 수정하여 `simpleTLD` 를 만들었다.

# Install 
```
sudo apt-get update
sudo apt-get upgrade
```
## Opencv2.4.10 이하 설치.
```
cd
wget https://sourceforge.net/projects/opencvlibrary/files/opencv-unix/2.4.10/opencv-2.4.10.zip
unzip opencv-2.4.10.zip
cd opencv-2.4.10
mkdir build && cd build
cmake ..
make -j8
sudo make install
```
## simpleTLD 설치.
```
cd 
git clone https://github.com/Simhs/simpleTLD.git
cd simpleTLD
sudo chmod +x install.sh
sudo ./install.sh
```

# Usage
## 객체 생성 방법 


* `b` remember current frame as background model / clear background
* `c` clear model and stop tracking  git
* `l` toggle learning
* `a` toggle alternating mode (if true, detector is switched off when tracker is available)
* `e` export model to file specified in configuration parameter "modelExportFile"
* `i` import model from file specified in configuration parameter "modelPath"
* `r` clear model, let user reinit tracking

## TLD 함수.
### Synopsis
`opentld [option arguments] [arguments]`
* `getData()` return (x1,y1,x2,y2)  설명: 추적되는 영역의 좌표를 반환(좌상,우하). 실패시 return(0,0,0,0)

* `getData()` return (x1,y1,x2,y2)  설명: 추적되는 영역의 좌표를 반환(좌상,우하). 실패시 return(0,0,0,0)

* `getData()` return (x1,y1,x2,y2)  설명: 추적되는 영역의 좌표를 반환(좌상,우하). 실패시 return(0,0,0,0)

### option arguments
* `[-a <startFrameNumber>]` video starts at the frameNumber _startFrameNumber_
* `[-b <x,y,w,h>]` Initial bounding box
* `[-d <device>]` select input device: _device_=(IMGS|CAM|VID|STREAM)  
	_IMGS_: capture from images  
	_CAM_: capture from connected camera  
	_VID_: capture from a video  
	_STREAM_: capture from RTSP stream
* `[-e <path>]` export model after run to _path_
* `[-f]` shows foreground
* `[-i <path>]` _path_ to the images or to the video.
* `[-j <number>]` show trajectory for the last _number_ frames
* `[-h]` shows help
* `[-m <path>]` if specified load a model from _path_. An initialBoundingBox must be specified or selectManually must be true.
* `[-n <number>]` Specifies the video device to use (defaults to 0). Useful to select a different camera when multiple cameras are connected.
* `[-p path]` prints results into the file _path_
* `[-s]` if set, user can select initial bounding box
* `[-t <theta>]` threshold for determining positive results
* `[-z <lastFrameNumber>]` video ends at the frameNumber _lastFrameNumber_.
	If _lastFrameNumber_ is 0 or the option argument isn't specified means
	all frames are taken.

### Arguments
`[CONFIG_FILE]` path to config file

## Config file
Look into the [sample-config-file](https://github.com/gnebehay/OpenTLD/blob/master/res/conf/config-sample.cfg) for more information.

# Building
## Dependencies
* OpenCV
* CMake
* libconfig++ (optional)
* Qt4 (optional)

## Compiling
### CMake
OpenTLD uses CMake to create native build environments such as make, Eclipse, Microsoft Visual Studio.
If you need help look at [Running CMake](http://www.cmake.org/cmake/help/runningcmake.html).

You can use `cmake-gui`, if you need a graphical user interface.

Use CMake to build the project. You can use "cmake-gui", if you need a graphical user interface.

__Gui__  
* Specify the source path (root path of the dictionary) and the binary path (where to build the program, out
	  of source build recommended)
* Configure
* Select compiler
* Adjust the options (if needed)
* Configure
* Generate

__Command line__  
If you have uncompressed the source in $OPENTLD, type in a console:
```bash
cd $OPENTLD
mkdir ../build
cd ../build
cmake ../$OPENTLD -DBUILD_QOPENTLD=ON -DUSE_SYSTEM_LIBS=OFF
```

__CMake options__  
* `BUILD_QOPENTLD` build the graphical configuration dialog (requieres Qt)
* `USE_SYSTEM_LIBS` don't use the included cvblob version but the installed version (requieres cvblob)

### Windows (Microsoft Visual Studio)
Navigate to the binary directory and build the solutions you want (You have to compile in RELEASE mode):
* `opentld` build the project
* `INSTALL` install the project

_Note_: `vcomp.lib` is necessary when you try to compile it with OpenMP support and the
Express versions of MSVC. This file is included in the Windows Server SDK.

### Linux (make)
Navigate with the terminal to the build directory
* `make` build the project
* `make install` build and install the project

### Mac
* `brew install python`
* `brew install gfortran`
* `easy_install numpy`
* `brew install cmake`
* `brew install opencv`
* `cmake` build the project

# Debian package
* Navigate with the terminal into the root dictionary of OpenTLD (OpenTLD/)
* Type `debuild -us -uc`
* Delete the temporary files in the source tree with `debuild clean`

