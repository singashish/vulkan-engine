#!/bin/bash
# Build all
set echo on

echo "Building all projects..."


pushd engine
source build.sh
popd

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Engine build failed! Error:"$ERRORLEVEL && exit
fi

pushd testengine
source build.sh
popd
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "TestEngine build failed! Error:"$ERRORLEVEL && exit
fi

echo "All projects built successfully."