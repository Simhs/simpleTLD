# Introduction

파이썬에서 TLD코드를 사용하고자 openTLD 코드를 수정하여 `simpleTLD` 를 만들었다.

# LINUX Install 
```
$ sudo apt-get update
$ sudo apt-get upgrade
```
## Opencv2.4.10 이하 설치.
```
$ cd
$ wget https://sourceforge.net/projects/opencvlibrary/files/opencv-unix/2.4.10/opencv-2.4.10.zip
$ unzip opencv-2.4.10.zip
$ cd opencv-2.4.10
$ mkdir build && cd build
$ cmake ..
$ make -j8
$ sudo make install
```
## simpleTLD 설치.
```
$ cd 
$ git clone https://github.com/Simhs/simpleTLD.git
$ cd simpleTLD
$ sudo chmod +x install.sh
$ sudo ./install.sh
```

# Usage
## 객체 생성 방법 
```
import TLD
tld = TLD(1)
time.sleep(1)
print tld.getData()

tld.tracking((100,100,200,200))
time.sleep(1)
print tld.getData()
time.sleep(1)
print tld.getData()
time.sleep(1)
print tld.getData()
time.sleep(1)
print tld.getData()

tld.clearTracking()
print tld.getData()

tld.close()
```

## TLD 함수.
### Synopsis

* `tld = TLD(mode)` 
param mode = 0 or 1
설명: mode = 0 -> without GUI  
     mode = 1 can see GUI for debug  
     
* `tld.getData()` 
return (x1,y1,x2,y2)  
설명: 추적되는 영역의 좌표를 반환(좌상,우하). 실패시 return(0,0,0,0)

* `tld.tracking(area)` 
param area=(x,y,w,h) 
설명: 추적할 영상의 영역(x,y,w,h)(좌상좌표2개 가로 세로)을 지정할 수 있다.

* `tld.clearTracking()`
설명: 트레킹 영역 제거

* `tld.close()`
설명: 객체 제거


# Raspberry Pi 3 Install

## SWAP 영역 할당
`$ sudo dd if=/dev/zero of=/home/swapfile bs=1024 count=1000000`

(한번에 1024바이트씩 1000000번 (1GB) /home/swapfile을 쓴다음 /dev/zero에 마운트 한다는뜻)


`$ sudo mkswap /home/swapfile`

(swapfile을 swap영역으로 포맷)


`$ sudo swapon /home/swapfile`

(swapfile을 swap으로서 활성화)

## 기본 업뎃
```
$ sudo apt-get update
$ sudo apt-get upgrade
$ sudo rpi-update
```
## 개발 툴
`$ sudo apt-get install build-essential git cmake pkg-config`

`$ sudo apt-get install libgtk2.0-dev libavcodec-dev  libavformat-dev libswscale-dev`

`$ sudo apt-get install libjpeg-dev libpng12-dev libtiff5-dev libjasper-dev libdc1394-22-dev`

## Opencv2.4.10 이하 설치.
https://defendtheplanet.net/2014/05/04/howto-opencv-2-4-9-on-raspberry-pi-from-source/
```
$ cd
$ wget https://sourceforge.net/projects/opencvlibrary/files/opencv-unix/2.4.10/opencv-2.4.10.zip
$ unzip opencv-2.4.10.zip
$ cd opencv-2.4.10
$ mkdir build && cd build
$ cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D BUILD_NEW_PYTHON_SUPPORT=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON  -D BUILD_EXAMPLES=ON -D WITH_FFMPEG=OFF ..
$ make
```
### make timing
* `make -j1` 5 ~ 9시간 

* `make -j4` 1시간 미만 
```
$ sudo make install
$ sudo ldconfig
```
## simpleTLD 설치.
```
$ cd 
$ git clone https://github.com/Simhs/simpleTLD.git
$ cd simpleTLD
$ sudo chmod +x install.sh
$ sudo ./install.sh
