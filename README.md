## dependencies

You should have installed gcc and cmake

In ubuntu:

````
sudo apt install build-essential
sudo apt install cmake
````

## compile witnesscalc for local host

````sh
git submodule init
git submodule update
./build_gmp.sh host
mkdir build_witnesscalc && cd build_witnesscalc
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package
make -j$(nproc) && make install
````

## compile witnesscalc for Android

Install Android NDK from https://developer.android.com/ndk or with help of "SDK Manager" in Android Studio.

Set the value of ANDROID_NDK environment variable to the absolute path of Android NDK root directory.

Examples:

````sh
export ANDROID_NDK=/home/test/Android/Sdk/ndk/23.1.7779620  # NDK is installed by "SDK Manager" in Android Studio.
export ANDROID_NDK=/home/test/android-ndk-r23b              # NDK is installed as a stand-alone package.
````

Compilation:

````sh
git submodule init
git submodule update
./build_gmp.sh android
mkdir build_witnesscalc_android && cd build_witnesscalc_android
cmake .. -DTARGET_PLATFORM=ANDROID -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_android
make -j$(nproc) && make install
````

## compile witnesscalc for iOS

Install Xcode.

````sh
git submodule init
git submodule update
./build_gmp.sh ios
mkdir build_witnesscalc_ios && cd build_witnesscalc_ios
cmake .. -GXcode -DTARGET_PLATFORM=IOS -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_ios
````
Open generated Xcode project and compile witnesscalc.


## License

witnesscalc is part of the iden3 project copyright 2022 0KIMS association and published with GPL-3 license. Please check the COPYING file for more details.
