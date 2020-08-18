# lpcnet_wasm

[LPCNet](https://github.com/mozilla/LPCNet) is a neural network based low-bandwith
speech synthesizer developed by xiph.org. The encoded bitrate achieved by
this library is 1.6kb/s. More information about LPCNet can be found at xiph.org [here](https://jmvalin.ca/demo/lpcnet_codec/).

This repository contains code for setting up xiph.org's LPCNet library in
WebAssembly. The library can then be used in the browser through the included wrapper code.

Currently, this wrapper only includes decoding support.

# Building

First, grab LPCNet through git submodules:

```
git submodule init
git submodule update
```

For wasm compilation, this library uses Emscripten. Running `./compile.sh` requires
being inside a shell with the emsdk environment loaded. Instructions for this can be found
[here](https://emscripten.org/docs/getting_started/downloads.html).

Then the steps are:

```
# Configure LPCNet for building (download model data, etc).
cd LPCNet
./autogen.sh
cd ..

# Run Emscripten (this requires being in an emsdk environment)
./compile.sh
```

This produces the wasm library `lpcnet_wasm.wasm` and the Javascript code `lpcnet_wasm.js` which
can be included to interact with the wasm library in the browser.

# Usage

An example of library usage can be found in `testlib.html`. This example requires the compiled
`lpcnet_wasm.js` and `lpcnet_wasm.wasm` to be in the same directory as `testlib.html`, as well as the sample
encoded file `compressed_test.bin`.

