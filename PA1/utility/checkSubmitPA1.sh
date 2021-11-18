#!/bin/bash

#############################################################################
# File       [ checkSubmitPA1.sh ]
# Author     [ funnymean ]
# Modified   [ 2020/09/21 by Yu-Sheng Lu]
# Synopsis   [ simple test for algorithm PA1 homework format program ]
# Date       [ Ver. 1.5 started 2020/09/21 ]
#############################################################################


if [ "$1" == "" ]; then
    echo "Usage:   ./checkSubmitPA1.sh <fileName>"
    echo "Example: ./checkSubmitPA1.sh b09901000_pa1.tgz"
    echo "This program will build a dir name checkSubmitPA1_$$ env"
    exit
fi

binaryFileName='NTU_sort'
fileName=$1

echo "Target file $fileName"
if [ ! -f $fileName ]; then
    echo "Cannot find tgz file $filename!"
    exit
fi
if [ -d check_$$ ]; then
    echo "Directory check_$$ exists"
    echo "Please delete the directory and try again"
    exit
fi

mkdir check_$$
cd check_$$


tar zxvf ../$fileName

stuid=`basename $fileName | sed -e 's/_.*//'`
echo "$fileName"
echo "$stuid"


if [ ! -d ${stuid}_pa1 ]; then
    echo "**ERROR Cannot find directory <student id>_pa1"
    cd ..
    rm -rf check_$$
    exit
fi

cd ${stuid}_pa1
echo "checking README ..."
if [ ! -f README ]; then
    echo "**ERROR Cannot find README"
    cd ../../
    rm -rf check_$$
    exit
fi

echo "checking src/ ..."
if [ ! -d src ]; then
    echo "Cannot find src dir"
    cd ../../
    rm -rf check_$$
    exit
fi

echo "checking doc/ ..."
if [ ! -d doc ]; then
    echo "Cannot find doc dir"
    cd ../../
    rm -rf check_$$
    exit
fi

echo "checking report ..."
report_exist=`ls doc | grep report.pdf`
if [ "${report_exist}" = "" ]; then
    echo "Connot find doc/report.pdf"
    cd ../../
    rm -rf check_$$
    exit
fi

echo "checking inputs/ ..."
if [ -d inputs ]; then
    echo "Directory inputs exists"
    echo "Please delete the inputs directory and try again"
    exit
fi

rm -f bin/$binaryFileName
make clean
make

if [ ! -f bin/$binaryFileName ]; then
    echo "Connot find bin/$binaryFileName"
    cd ../../
    rm -rf check_$$
    exit
fi

echo "Congratulations!  Passed submission checking!"
cd ../../
rm -rf check_$$

