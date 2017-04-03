mkdir build && cd build
cmake ..
make
cd bin
sudo cp ./opentld /usr/local/bin/opentld

sudo cp ../../TLD.py /usr/local/lib/python2.7/dist-packages/TLD.py
