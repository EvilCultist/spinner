mkdir build
cd build
cmake ..
make
cd ..
__NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia ./spinner
# clear
rm ./spinner
