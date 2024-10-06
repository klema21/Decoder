Install and build:

1. Linux install: sudo apt install libicu-dev
2. Compile and run: clang++ -licuuc decode.cpp

Dont forget to update submodules:
1. git submodule update --init --recursive

Cmake build proccess:

1. mkdir build && cd build
2. cmake ..
3. cmake --build .

Docker:

sudo apt install curl
curl -fsSL https://get.docker.com -o get-docker.sh
sh get-docker.sh

sudo apt remove docker docker-engine docker.io containerd runc

sudo apt update
sudo apt install \
  apt-transport-https \
  ca-certificates \
  curl \
  gnupg-agent \
  software-properties-common -y 

curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -

sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"

sudo apt update

sudo apt install docker-ce docker-compose -y 

sudo systemctl status docker