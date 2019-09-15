#!/bin/bash

# get current directory-path and the path of the parent-directory
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PARENT_DIR="$(dirname "$DIR")"

# create build-directory
BUILD_DIR="$PARENT_DIR/build"
mkdir -p $BUILD_DIR

# create directory for the final result
RESULT_DIR="$PARENT_DIR/result"
mkdir -p $RESULT_DIR

#-----------------------------------------------------------------------------------------------------------------

# clone libKitsuneCommon
git clone  git@gitlab.com:tobiasanker/libKitsuneCommon.git "$PARENT_DIR/libKitsuneCommon"
cd "$PARENT_DIR/libKitsuneCommon"
git chekcout 0.5.2

# create build directory for libKitsuneCommon and go into this directory
LIB_KITSUNE_COMMON_DIR="$BUILD_DIR/libKitsuneCommon"
mkdir -p $LIB_KITSUNE_COMMON_DIR
cd $LIB_KITSUNE_COMMON_DIR

# build libKitsuneCommon library with qmake
/usr/lib/x86_64-linux-gnu/qt5/bin/qmake "$PARENT_DIR/libKitsuneCommon/libKitsuneCommon.pro" -spec linux-g++ "CONFIG += optimize_full"
/usr/bin/make -j4

# copy build-result and include-files into the result-directory
cp "$LIB_KITSUNE_COMMON_DIR/src/libKitsuneCommon.so.0.5.2" "$RESULT_DIR/"
cp -r "$PARENT_DIR/libKitsuneCommon/include" "$RESULT_DIR/"

#-----------------------------------------------------------------------------------------------------------------

# create build directory for libKitsuneJson and go into this directory
LIB_KITSUNE_JSON_DIR="$BUILD_DIR/libKitsuneJson"
mkdir -p $LIB_KITSUNE_JSON_DIR
cd $LIB_KITSUNE_JSON_DIR

# build libKitsuneJson library with qmake
/usr/lib/x86_64-linux-gnu/qt5/bin/qmake "$PARENT_DIR/libKitsuneJson/libKitsuneJson.pro" -spec linux-g++ "CONFIG += optimize_full"
/usr/bin/make -j4

# copy build-result and include-files into the result-directory
cp "$LIB_KITSUNE_JSON_DIR/src/libKitsuneJson.so.0.4.0" "$RESULT_DIR/"
cp -r "$PARENT_DIR/libKitsuneJson/include" "$RESULT_DIR/"

#-----------------------------------------------------------------------------------------------------------------

# recreate symlinks
cd "$RESULT_DIR/"
ln -s libKitsuneCommon.so.0.5.2 libKitsuneCommon.so.0.5
ln -s libKitsuneCommon.so.0.5.2 libKitsuneCommon.so.0
ln -s libKitsuneCommon.so.0.5.2 libKitsuneCommon.so

ln -s libKitsuneJson.so.0.4.0 libKitsuneJson.so.0.4
ln -s libKitsuneJson.so.0.4.0 libKitsuneJson.so.0
ln -s libKitsuneJson.so.0.4.0 libKitsuneJson.so
