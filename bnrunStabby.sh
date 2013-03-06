#!/bin/sh

make clean > /dev/null

make > /dev/null

if [ $? -eq 0 ]
    then
        echo 'Build finished, running...'
    else
        echo 'Build fail.'
        exit
fi

cd bin && ./stabby