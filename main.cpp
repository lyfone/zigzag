//
// Created by zzhfeng on 2018/3/3.
//

#include <iostream>
#include "ZigZagDecoder.h"
#include "ZigZagEncoder.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    uint8_t buffer[1024];
    int max_size = 1024;
    int test = 64;
    int res = 0;

    std::cout << "test : " <<  test << std::endl;

    ZigZagEncoder encoder(7);
    encoder.setBuffer(buffer,max_size);
    encoder.encoder(test);

    std::cout << "encode complete !" << std::endl;

    ZigZagDecoder decoder(7);
    decoder.setBuffer(buffer,max_size);
    decoder.decode(res);

    std::cout << "result : " << res << std::endl;

    return 0;
}