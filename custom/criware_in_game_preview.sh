#!/bin/sh

cd "$(dirname "$0")"
cd ..

cd external/criware

cp Classes/cricocos2d_initializer_igp.cpp Classes/cricocos2d_initializer.cpp
cp proj.android/criware_cc/Android_igp.mk proj.android/criware_cc/Android.mk
