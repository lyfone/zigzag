//
// Created by zzhfeng on 2018/3/3.
//

#ifndef ZIGZAG_ZIGZAGENCODER_H
#define ZIGZAG_ZIGZAGENCODER_H

#pragma once

#include "ZigZag.h"

/**
 * ZigZagEncoder 编码器
 */
class ZigZagEncoder {
public:
    //构造函数
    ZigZagEncoder(int step);

    //编码操作
    bool encoder(int num);

    //设置数据存放的缓冲区和缓冲去大小
    void setBuffer(uint8_t *buffer, int max_size);

    //获取写入的字节数量
    uint64_t get_total_count() {
        return zigzagWriteStream.get_total_count();
    }

private:
    //写入流对象
    ZigZagWriteStream zigzagWriteStream;

    //ZigZag格式转换操作对象
    ZigZag zigzag;

    //分组步长 zigzag中恒为7
    int per_offset;

    //编码器函数
    uint64_t Encoder(int num);
};

/**
 * ZigZagEncoder 构造函数
 * @param step 在zigzag中step恒为7
 */
ZigZagEncoder::ZigZagEncoder(int step) {
    per_offset = step;
};

/**
 * encoder
 * @param num 待编码的数值
 * @return
 */
bool ZigZagEncoder::encoder(int num) {
    uint64_t free_len = Encoder(num);
    return free_len > 0;
}

/**
 * 设置编码数据存放的缓冲区
 * @param buffer
 * @param max_size
 */
void ZigZagEncoder::setBuffer(uint8_t *buffer, int max_size) {
    zigzagWriteStream.setBuffer(buffer, max_size);
}

/**
 * 编码器
 * @param num 被编码的数值
 * @return
 */
uint64_t ZigZagEncoder::Encoder(int num) {
    int new_num = zigzag.int_to_zigzag(num);
    int temp = (new_num & (~0x7f));

    while(temp != 0){
        uint8_t byte = (uint8_t)((new_num & 0x7f) | 0x80);
        zigzagWriteStream.putByte(byte);
        new_num = ((unsigned int)new_num) >> per_offset;
        temp = (new_num & (~0x7f));
    }
    zigzagWriteStream.putByte((uint8_t)new_num);
    return zigzagWriteStream.free_length();
}

#endif //ZIGZAG_ZIGZAGENCODER_H
