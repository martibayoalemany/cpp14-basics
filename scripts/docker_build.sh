#!/usr/bin/env bash

PROJECT_ROOT=${1:?You must pass the path to your file Dockerfile}
PROJECT_ROOT=$(realpath ${PROJECT_ROOT})
[[ $? == 0 ]]; PROJECT_NAME=$(realpath $0 | sed 's/.*\/\(.*\)\/.*\/.*/\1/')

if [ $? == 0 ]
then        
    echo PROJECT_ROOT: $PROJECT_ROOT
    echo PROJECT_NAME: $PROJECT_NAME
    docker build ${PROJECT_ROOT} -t ${PROJECT_NAME}
    docker run -v `pwd`:/git -P -it ${PROJECT_NAME} bash 
fi
