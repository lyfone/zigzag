//
// Created by zzhfeng on 2018/3/3.
//

#include "ZigZag.h"

/**
 * ZigZagBuffer
 */
ZigZagBuffer::ZigZagBuffer(){
    buffer = nullptr;
    pos = 0;
    bytes_count = 0;
    max_size = 0;
}

uint8_t ZigZagBuffer::getByte() {
    uint8_t byte = buffer[pos];
    pos++;
    return  byte;
}

void ZigZagBuffer::putByte(uint8_t byte) {
    buffer[pos] = byte;
    pos++;
    bytes_count++;
}

/**
 * ZigZag to Int
 * @param n
 * @return
 */
int ZigZag::zigzag_to_int(int n) {
    return (((unsigned int)n) >>1) ^ -(n & 1);
}

/**
 * Int to ZigZag
 * @param n
 * @return
 */
int ZigZag::int_to_zigzag(int n) {
    return (n <<1) ^ (n >>31);
}


/**
 * ZigZagWriteStream
 */


/**
 * putByte
 * @param byte
 */
void ZigZagWriteStream::putByte(uint8_t byte) {
  zigzagBuffer.putByte(byte);
};

/**
 * setBuffer
 * @param buffer
 * @param max_size
 */
void ZigZagWriteStream::setBuffer(uint8_t *buffer, int max_size) {
    zigzagBuffer.buffer = buffer;
    zigzagBuffer.max_size = max_size;
}

/**
 * free_length
 * @return
 */
uint64_t ZigZagWriteStream::free_length() {
    return zigzagBuffer.max_size - zigzagBuffer.bytes_count;
}

/**
 * get_total_count
 * @return
 */
uint64_t ZigZagWriteStream::get_total_count() {
    return zigzagBuffer.bytes_count;
}

/**
 * ZigZagReadStream
 */

/**
 * getByte
 * @param byte
 */
uint8_t ZigZagReadStream::getByte() {
    return zigzagBuffer.getByte();
}

/**
 * setBuffer
 * @param buffer
 * @param max_size
 */
void ZigZagReadStream::setBuffer(uint8_t *buffer, int max_size) {
    zigzagBuffer.buffer = buffer;
    zigzagBuffer.max_size = max_size;
}






