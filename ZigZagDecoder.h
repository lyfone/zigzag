//
// Created by zzhfeng on 2018/3/3.
//

#ifndef ZIGZAG_ZIGZAGDECODER_H
#define ZIGZAG_ZIGZAGDECODER_H

#pragma once

#include "ZigZag.h"

/**
 * ZigZagDecoder
 */
class  ZigZagDecoder{
public:
    //构造函数
    ZigZagDecoder(int step);

    //解码操作
    void decode(int &num);

    //设置数据缓冲区
    void setBuffer(uint8_t *buffer, int max_size);

private:
    //待读的已编码好的数据流对象
    ZigZagReadStream zigzagReadStream;

    //ZigZag格式转换操作对象
    ZigZag zigzag;

    //分组步长 zigzag中恒为7
    int per_offset;

    //解码器函数
    int Decoder();
};

/**
 * ZigZagDecoder 构造函数
 * @param step  在zigzag中step恒为7
 */
ZigZagDecoder::ZigZagDecoder(int step) {
    per_offset = step;
}

/**
 * decode
 * @param num 解码结果
 */
void ZigZagDecoder::decode(int &num) {
    num = Decoder();
}

/**
 * setBuffer 设置待解码数据存放的缓冲区
 * @param buffer
 * @param max_size
 */
void ZigZagDecoder::setBuffer(uint8_t *buffer, int max_size) {
    zigzagReadStream.setBuffer(buffer,max_size);
}

/**
 * Decoder 解码器
 * @return
 */
int ZigZagDecoder::Decoder() {
    int result_num = 0;
    int offset = 0;

    uint8_t  byte = zigzagReadStream.getByte();
    uint8_t temp = byte & 0x80;

    while (temp == 0x80){
        result_num |= ((byte & 0x7f) << offset);
        offset += per_offset;
        byte = zigzagReadStream.getByte();
        temp = byte & 0x80;
    }

    result_num |= (byte << offset);

    return  zigzag.zigzag_to_int(result_num);
}

#endif //ZIGZAG_ZIGZAGDECODER_H
