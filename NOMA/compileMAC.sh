"/Applications/Xcode.app/Contents/Developer/usr/bin/make" -f nbproject/Makefile-Debug_Mac_.mk QMAKE= SUBPROJECTS= .build-conf
"/Applications/Xcode.app/Contents/Developer/usr/bin/make"  -f nbproject/Makefile-Debug_Mac_.mk dist/Debug_Mac_/GNU-MacOSX/noma
mkdir -p dist/Debug_Mac_/Resources
mkdir -p dist/noma.app
mkdir -p dist/noma.app/Contents
mkdir -p dist/noma.app/Contents/Resources
mkdir -p dist/noma.app/Contents/MacOS
cp -a "`pwd`"/resources/* dist/noma.app/Contents/Resources
cp -a "`pwd`"/resources/* dist/Debug_Mac_/Resources    
cp dist/Debug_Mac_/GNU-MacOSX/noma dist/noma.app/Contents/MacOS