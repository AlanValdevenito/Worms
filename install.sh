#!/usr/bash

green=`tput setaf 2`

echo "Instalando dependencias\n"

sudo apt-get install clang -y 
sudo apt-get install make -y 
sudo apt-get -y install cmake -y
sudo apt-get install build-essential -y
sudo apt install -y qtcreator qtbase5-dev qt5-qmake cmake
sudo apt-get install libqt5multimedia5-plugins -y
sudo apt-get install qtmultimedia5-dev -y
sudo apt-get install libyaml-cpp-dev -y

SDL_IMAGE_URL="https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.3/SDL2_image-2.6.3.zip"
SDL_MIXER_URL="https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.6.3/SDL2_mixer-2.6.3.zip"
SDL_TTF_URL="https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2.zip"
SDL2PP_URL="https://github.com/libSDL2pp/libSDL2pp/archive/refs/tags/0.18.1.zip"
SDL_DIR="sdl"

sudo apt-get install libjpeg-dev        \
                     libpng-dev         \
                     libfreetype-dev    \
                     libopusfile-dev    \
                     libflac-dev        \
                     libxmp-dev         \
                     libfluidsynth-dev  \
                     libwavpack-dev     \
                     libmodplug-dev     \
                     libsdl2-dev


mkdir -p "$SDL_DIR"
echo "Descargando SDL image\n"
wget "$SDL_IMAGE_URL" -P "$SDL_DIR"
wget "$SDL_MIXER_URL" -P "$SDL_DIR"
wget "$SDL_TTF_URL" -P "$SDL_DIR"
wget "$SDL2PP_URL" -P "$SDL_DIR"
unzip "$SDL_DIR/SDL2_image-2.6.3.zip" -d "$SDL_DIR"
unzip "$SDL_DIR/SDL2_mixer-2.6.3.zip" -d "$SDL_DIR"
unzip "$SDL_DIR/SDL2_ttf-2.20.2.zip" -d "$SDL_DIR"
unzip "$SDL_DIR/libSDL2pp-0.18.1.zip" -P "$SDL_DIR"

cd "$SDL_DIR/SDL2_image-2.6.3"
mkdir build
cd build
cmake ..
make -j4
sudo make install

cd ../..
cd "$SDL_DIR/SDL2_mixer-2.6.3"
mkdir build
cd build
cmake ..
make -j4
sudo make install

cd ../..
cd "$SDL_DIR/SDL2_ttf-2.20.2"
mkdir build
cd build
cmake ..
make -j4
sudo make install

cd ../..
cd "$SDL_DIR/libSDL2pp-0.18.1"
mkdir build
cd build
cmake ..
make -j4
sudo make install

cd ../..





echo ${green}"Instalando worms\n"


mkdir build
cd build
sudo cmake ..
sudo make
