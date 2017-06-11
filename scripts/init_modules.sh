#!/usr/bin/env bash

SCRIPT_DIR=$(realpath $(dirname $0))
ROOT_DIR=${SCRIPT_DIR}/../
echo ROOT_DIR $ROOT_DIR

git submodule add -f modules/googletest https://github.com/google/googletest.git
git submodule add -f modules/biicode https://github.com/biicode/biicode.git
git submodule update --init --recursive


echo "----------------------------------"
echo  "Google test"
echo "----------------------------------"
pushd
cd ${ROOT_DIR}/modules/googletest
cmake -rf  .
make .
# Currently using google gest in a local folder
# sudo -s make install
popd

exit 0

echo "----------------------------------"
echo  "Biicode"
echo "----------------------------------"

sudo apt install virtualenv python-pip -y 
pip install --upgrade pip

cd ${ROOT_DIR}

virtualenv ${ROOT_DIR}/modules/biicode/.venv27 

echo Install python dependencies
cd ${ROOT_DIR}/modules/biicode  
source ${ROOT_DIR}/modules/biicode/.venv27/bin/activate 
pip install -r ${ROOT_DIR}/modules/biicode/client/requirements.txt 
pip install -r ${ROOT_DIR}/modules/biicode/common/requirements.txt
