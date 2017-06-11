#!/usr/bin/env bash

# Initial script to install biicode from source code
# TODO: Install the python graph library from google
#-----------------------------------------------------------------------------

SCRIPT_DIR=$(realpath $(dirname $0))
ROOT_DIR=${SCRIPT_DIR}/../
echo ROOT_DIR $ROOT_DIR

rm -rf modules/*
git submodule add -f  https://github.com/google/googletest.git ./modules/googletest
git submodule add -f  https://github.com/biicode/biicode.git ./modules/biicode
git submodule add -f https://github.com/pmatiello/python-graph ./modules/python-graph
git submodule 
echo "----------------------------------"
echo  "Init recursive"
echo "----------------------------------"
git submodule update --init --recursive

echo "----------------------------------"
echo  "Python 2.7"
echo "----------------------------------"

if ! which virtualenv > /dev/null; then
    sudo apt install virtualenv -y 
fi

if ! which pip > /dev/null; then
    sudo apt install python-pip -y 
fi

pip install --upgrade pip

cd ${ROOT_DIR}

virtualenv ${ROOT_DIR}/modules/.venv27 
source ${ROOT_DIR}/modules/.venv27/bin/activate 

echo "----------------------------------"
echo  "Python graph"
echo "----------------------------------"
pushd .
cd ${ROOT_DIR}/modules/python-graph
sudo make install-core
make install-dot
popd 

echo "----------------------------------"
echo  "Google test"
echo "----------------------------------"
pushd .
cd ${ROOT_DIR}/modules/googletest
cmake -rf  .
make .
# Currently using google gest in a local folder
# sudo -s make install
popd

echo "----------------------------------"
echo  "Biicode"
echo "----------------------------------"

echo Install python dependencies
cd ${ROOT_DIR}/modules/biicode  
pip install -r ${ROOT_DIR}/modules/biicode/client/requirements.txt 
# Skip python-graph it does not install correctly using pip
cat ${ROOT_DIR}/modules/biicode/common/requirements.txt | grep -v "python-graph" | xargs -n1 pip install

