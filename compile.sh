#!/usr/bin/env bash
emcc -o lpcnet_wasm.js -O3 -s WASM=1  -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap", "ccall"]' -s ALLOW_MEMORY_GROWTH=1 -s NO_EXIT_RUNTIME=1 -I LPCNet/include lpcnet_wasm.c LPCNet/src/{celt_lpc,ceps_codebooks,common,freq,kiss_fft,lpcnet,lpcnet_dec,nnet,nnet_data,pitch}.c

