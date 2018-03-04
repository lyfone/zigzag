//
// Created by zzhfeng on 2018/3/3.
//

#ifndef ZIGZAG_ZIGZAG_H
#define ZIGZAG_ZIGZAG_H

#pragma once

#include <cstdint>

/**
 * ZigZag数据缓冲区结构
 */
struct ZigZagBuffer{
    //缓冲区buffer
    uint8_t *buffer;
    //当前数据存放位置
    int pos;
    //存放的数据总数
    int bytes_count;
    //最大存放数量（缓冲区大小）
    int max_size;

    //构造函数
    ZigZagBuffer();

    //读取一个字节
    uint8_t getByte();

    //写入一个字节
    void putByte(uint8_t byte);
};

/**
 *  ZigZag数据格式转换
 */
class ZigZag{
public:
    //zigzag_to_int
    int zigzag_to_int(int n);
    //int_to_zigzag
    int int_to_zigzag(int n);
};

/**
 * ZigZagWriteStream 写入流，编码时使用
 */
class ZigZagWriteStream{
public:
    //写入一个字节
    void putByte(uint8_t byte);

    //设置写入的已编码数据的buffer以及buffer最大空间
    void setBuffer(uint8_t *buffer, int max_size);

    //获取剩余空间
    uint64_t free_length();

    //获取写入的数量
    uint64_t get_total_count();

private:
    //zigzagBuffer结构
    ZigZagBuffer zigzagBuffer;
};

/**
 * ZigZagReadStream 读取流，从缓冲区中读取编码的数据
 */
class ZigZagReadStream{
public:
    //读取一个字节
    uint8_t getByte();

    //设置缓冲区
    void setBuffer(uint8_t *buffer, int max_size);

private:
    //zigzagBuffer
    ZigZagBuffer zigzagBuffer;
};

#endif //ZIGZAG_ZIGZAG_H
