#!/usr/bin/env bash

# Initial script to install biicode from source code
# TODO: Install the python graph library from google
#-----------------------------------------------------------------------------

SCRIPT_DIR=$(realpath $(dirname $0))
ROOT_DIR=${SCRIPT_DIR}/../
echo $ROOT_DIR
sudo apt install virtualenv python-pip -y 
pip install --upgrade pip

cd ${ROOT_DIR}
git submodule update --init --recursive
virtualenv ${ROOT_DIR}/modules/biicode/.venv27 

echo Install python dependencies
cd ${ROOT_DIR}/modules/biicode  
source ${ROOT_DIR}/modules/biicode/.venv27/bin/activate 
pip install -r ${ROOT_DIR}/modules/biicode/client/requirements.txt 
pip install -r ${ROOT_DIR}/modules/biicode/common/requirements.txt
