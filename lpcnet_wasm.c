#include "emscripten.h"
#include "LPCNet/include/lpcnet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EMSCRIPTEN_KEEPALIVE
uint8_t* create_buffer(int size) {
    return malloc(size * sizeof(char));
}


EMSCRIPTEN_KEEPALIVE
int min_out_samples(int size) {
    int num_writes = size/LPCNET_COMPRESSED_SIZE;
    return num_writes * LPCNET_PACKET_SAMPLES;
}

LPCNetDecState *net;

// 0 on success
EMSCRIPTEN_KEEPALIVE
int try_create_decoder() {
    if (net != NULL) {
        return 1;
    }
    net = lpcnet_decoder_create();
    return 0;
}

// 0 on success 
EMSCRIPTEN_KEEPALIVE
int try_destroy_decoder() {
    if (net == NULL) {
        return 1;
    }
    lpcnet_decoder_destroy(net);
    net = NULL;
    return 0;
}

EMSCRIPTEN_KEEPALIVE
int decode(uint8_t* in_buf, int in_size, short* out_buf, int out_size) {
    int pos = 0;
    int samples_written = 0;
    for (int i = 0;; ++i) {
        unsigned char buf[LPCNET_COMPRESSED_SIZE];
        short pcm[LPCNET_PACKET_SAMPLES];
        if (pos + LPCNET_COMPRESSED_SIZE > in_size || samples_written + LPCNET_PACKET_SAMPLES > out_size) {
            break;
        }
        lpcnet_decode(net, in_buf + pos, out_buf + samples_written);
        pos += LPCNET_COMPRESSED_SIZE;
        samples_written += LPCNET_PACKET_SAMPLES;
    }
    return pos;
}
