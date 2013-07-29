#!/bin/sh

make clean > /dev/null
if [ $? -eq 0 ]
    then
        echo 'Cleanup finished, building...'
    else
        echo 'Cleanup fail.'
        exit
fi

make debug > /dev/null

if [ $? -eq 0 ]
    then
        echo 'Build finished, running...'
    else
        echo 'Build fail.'
        exit
fi

cd bin && ./stabby