#include "bit.h"
#include <stdio.h>
#include <string.h>

int bit_greet() {
        printf("This is bit stream rw library.\n");
        return 0;
}

int init_writer(bit_writer * writer, void* buffer, size_t bufsize) {
        writer->buffer = buffer;
        writer->bufsize = bufsize;
        writer->avail = bufsize << 3;
        writer->cursor = buffer;
        writer->bufend = buffer + bufsize;
        writer->pos = 0;
        memset(buffer, 0, bufsize);
        return 0;
}

int write_bit(bit_writer * writer, int bit) {
        if (writer->avail == 0) {
                return -1;
        }
        bit = (bit & 1) << writer->pos;
        *(uint8_t*) writer->cursor |= bit;
        writer->cursor += (writer->pos + 1) >> 3;
        writer->pos = (writer->pos + 1) & 0x7;
        writer->avail --;
        return 0;
}

int write_bits(bit_writer* writer, uint64_t bits, size_t len) {
        if (len > writer->avail || len > 64) {
                return -1;
        }
        size_t rest = writer->bufend - writer->cursor;
        bits = bits << (64-len) >> (64-len);
        uint_u tmp;
        tmp.u64 = bits << writer->pos;
        if (rest > 8) {
                ((uint64_t*) writer->cursor)[0] |= tmp.u64;
                size_t written = 64 - writer->pos;
                if (len > written) {
                        tmp.u64 = bits >> written;
                        ((uint8_t*) writer->cursor)[8] = tmp.u8[0];
                } 
        } else {
                switch (rest)
                {
                case 8:
                        ((uint64_t*) writer->cursor)[0] |= tmp.u64;
                        break;
                case 7:
                        ((uint32_t*) writer->cursor)[0] |= tmp.u32[0];
                        ((uint16_t*) writer->cursor)[2] |= tmp.u16[2];
                        ((uint8_t*) writer->cursor)[6] |= tmp.u8[6];
                        break;
                case 6:
                        ((uint32_t*) writer->cursor)[0] |= tmp.u32[0];
                        ((uint16_t*) writer->cursor)[2] |= tmp.u16[2];
                        break;
                case 5:
                        ((uint32_t*) writer->cursor)[0] |= tmp.u32[0];
                        ((uint8_t*) writer->cursor)[4] |= tmp.u8[4];
                        break;
                case 4:
                        ((uint32_t*) writer->cursor)[0] |= tmp.u32[0];
                        break;
                case 3:
                        ((uint16_t*) writer->cursor)[0] |= tmp.u16[0];
                        ((uint8_t*) writer->cursor)[2] |= tmp.u8[2];
                        break;
                case 2:
                        ((uint16_t*) writer->cursor)[0] |= tmp.u16[0];
                        break;
                case 1:
                        ((uint8_t*) writer->cursor)[0] |= tmp.u8[0];
                        break;
                default:
                        break;
                }
        }
        writer->cursor += (len + writer->pos) >> 3; 
        writer->pos = (len + writer->pos) & 0x7;
        writer->avail -= len;
        return len;
}

int init_reader(bit_reader * reader, void* buffer, size_t bit_len) {
        reader->buffer = buffer;
        reader->bufsize = (bit_len + 7) >> 3;
        reader->avail = bit_len;
        reader->cursor = buffer;
        reader->bufend = buffer + reader->bufsize;
        reader->pos = 0;
        return 0;
}

int read_bit(bit_reader* reader) {
        if (reader->avail == 0) {
                return -1;
        } 
        int i = *(uint8_t*)reader->cursor >> reader->pos;
        reader->cursor += (reader->pos + 1) >> 3;
        reader->pos = (reader->pos + 1) & 0x7;
        reader->avail --;
        return i & 1;
}

int read_bits(bit_reader* reader, size_t len, uint64_t * result) {
        if (len > reader->avail || len > 64) {
                return -1;
        }
        size_t rest = reader->bufend - reader->cursor;
        int shift;
        uint_u tmp;
        tmp.u64 = 0;
        if (rest > 8) {
                *result = ((uint_u*) reader->cursor)->u64 >> reader->pos;
                int read = 64 - reader->pos;
                if (len > read) {
                        tmp.u8[7] = ((uint8_t *) reader->cursor)[8];
                        tmp.u64 <<= 8-reader->pos;
                        *result |= tmp.u64;
                } 
        } else {
                switch (rest)
                {
                case 8:
                        ((uint_u*) result)->u64 = ((uint_u*) reader->cursor)->u64 >> reader->pos;
                        break;
                case 7:
                        ((uint_u*) result)->u32[0] = ((uint_u*) reader->cursor)->u32[0] >> reader->pos;
                        ((uint_u*) result)->u16[2] = ((uint_u*) reader->cursor)->u16[2] >> reader->pos;
                        ((uint_u*) result)->u8[6] = ((uint_u*) reader->cursor)->u8[6] >> reader->pos;
                        break;
                case 6: 
                        ((uint_u*) result)->u32[0] = ((uint_u*) reader->cursor)->u32[0] >> reader->pos;
                        ((uint_u*) result)->u16[2] = ((uint_u*) reader->cursor)->u16[2] >> reader->pos;
                        break;
                case 5: 
                        ((uint_u*) result)->u32[0] = ((uint_u*) reader->cursor)->u32[0] >> reader->pos;
                        ((uint_u*) result)->u8[4] = ((uint_u*) reader->cursor)->u8[4] >> reader->pos;
                        break;
                case 4: 
                        ((uint_u*) result)->u32[0] = ((uint_u*) reader->cursor)->u32[0] >> reader->pos;
                        break;
                case 3:
                        ((uint_u*) result)->u16[0] = ((uint_u*) reader->cursor)->u16[0] >> reader->pos;
                        ((uint_u*) result)->u8[2] = ((uint_u*) reader->cursor)->u8[2] >> reader->pos;
                        break;
                case 2:
                        ((uint_u*) result)->u16[0] = ((uint_u*) reader->cursor)->u16[0] >> reader->pos;
                        break;
                case 1:
                        ((uint_u*) result)->u8[0] = ((uint_u*) reader->cursor)->u8[0] >> reader->pos;
                        break;
                default:
                        break;
                }
        }
        shift = (64-len);
        *result = *result << shift >> shift;
        reader->cursor += (len + reader->pos) >> 3; 
        reader->pos = (len + reader->pos) & 0x7;
        reader->avail -= len;
        return len;
}