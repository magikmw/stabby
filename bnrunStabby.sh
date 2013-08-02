#!/bin/sh

make clean > /dev/null
if [ $? -eq 0 ]
    then
        echo 'Cleanup finished, building...'
    else
        echo 'Cleanup fail.'
        exit
fi

if [ "$1" = "DEBUG" ]
then
    echo 'DEBUG BUILD'
    make debug > /dev/null

    if [ $? -eq 0 ]
        then
            echo 'Build finished, running...'
        else
            echo 'Build fail.'
            exit
    fi

    cd bin && gdb ./stabby
else
    make > /dev/null

    if [ $? -eq 0 ]
        then
            echo 'Build finished, running...'
        else
            echo 'Build fail.'
            exit
    fi

    cd bin && ./stabby
fi