git clone https://github.com/giaf/hpipm
cd hpipm
mkdir build && build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DHPIPM_TESTING=OFF
make -j4
sudo make install -j
cd ../..
rm -rf hpipm
echo export LD_LIBRARY_PATH=/opt/hpipm/lib:$LD_LIBRARY_PATH >> ~/.bashrc
source ~/.bashrc