## Dependencies

You should have installed gcc and cmake

In ubuntu:

```sh
sudo apt install build-essential cmake m4
```

## Compilation

### Preparation
```sh
git submodule init
git submodule update
```

### Compile witnesscalc for x86_64 host machine

```sh
./build_gmp.sh host
make host
```

### Compile witnesscalc for arm64 host machine

```sh
./build_gmp.sh host
make arm64_host
```

### Compile witnesscalc for Android

Install Android NDK from https://developer.android.com/ndk or with help of "SDK Manager" in Android Studio.

Set the value of ANDROID_NDK environment variable to the absolute path of Android NDK root directory.

Examples:

```sh
export ANDROID_NDK=/home/test/Android/Sdk/ndk/23.1.7779620  # NDK is installed by "SDK Manager" in Android Studio.
export ANDROID_NDK=/home/test/android-ndk-r23b              # NDK is installed as a stand-alone package.
```

Compilation for arm64:

```sh
./build_gmp.sh android
make android
```

Compilation for x86_64:

```sh
./build_gmp.sh android_x86_64
make android_x86_64
```

### Compile witnesscalc for iOS

Requirements: Xcode.

1. Run:
    ````sh
    ./build_gmp.sh ios
    make ios
    ````
2. Open generated Xcode project. 
3. Add compilation flag `-D_LONG_LONG_LIMB` to all build targets.
4. Add compilation flag `-DCIRCUIT_NAME=auth`, `-DCIRCUIT_NAME=sig` and `-DCIRCUIT_NAME=mtp` to the respective targets.
5. Compile witnesscalc.

## Updating circuits
1. Compile a circuit with compile-circuit.sh script in circuits repo as usual.
2. Replace existing <circuitname>.cpp and <circuitname>.dat files with generated ones (e.g. auth.cpp & auth.dat).
3. Enclose all the code inside <circuitname>.cpp file with `namespace CIRCUIT_NAME` (do not replace `CIRCUIT_NAME` with the real name, it will be replaced at compilation), like this:
   ```c++
   #include ... 
   #include ... 
   
   namespace CIRCUIT_NAME {
   
   // millions of code lines here
   
   } // namespace
    
   ```
4. Optional. Remove the `#include <assert.h>` line and replace all accurances of `assert(` with `check(` in .cpp file to switch from asserts to exceptions. In this way it's easier to spot problems in release builds. It has little to no perf impact in our benchmarks and no difference from security perspective (as security comes from proving, not witness calculation).

Alternatively you can patch the `.cpp` circuit file with a `patch_cpp.sh` script. Example how to run it:
```shell
./patch_cpp.sh ../circuits/build/linkedMultiQuery10/linkedMultiQuery10_cpp/linkedMultiQuery10.cpp > ./src/linkedMultiQuery10.cpp
```

## License

witnesscalc is part of the iden3 project copyright 2022 0KIMS association and published with GPL-3 license. Please check the COPYING file for more details.
