#!/bin/bash

set -e
set -x

if [[ "$(uname -s)" == 'Darwin' ]]; then
    brew update || brew update
    brew outdated pyenv || brew upgrade pyenv
    brew install pyenv-virtualenv
    brew install cmake || true

    if which pyenv > /dev/null; then
        eval "$(pyenv init -)"
    fi

    pyenv install 2.7.10
    pyenv virtualenv 2.7.10 conan
    pyenv rehash
    pyenv activate conan
fi

# python 3
python3 -m venv .venv3 
source .venv3/bin/activate
pip install --upgrade pip
pip install -r ../requirements_3_5.txt

pip install conan --upgrade
pip install conan_package_tools

conan user
