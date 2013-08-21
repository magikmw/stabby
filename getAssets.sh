#!/bin/env sh

wget -c https://www.dropbox.com/s/91eh9178d9wttke/assets.tar.gz

mkdir -p bin
cd bin/ && tar -xf ../assets.tar.gz
