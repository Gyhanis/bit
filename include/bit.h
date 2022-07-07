#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

typedef union {
        uint64_t u64;
        uint32_t u32[2];
        uint16_t u16[4];
        uint8_t  u8[8];
} uint_u;

typedef struct {
        void * buffer;
        size_t bufsize;
        size_t avail;
        void * cursor;
        void * bufend;
        int pos;
} bit_writer, bit_reader;

int bit_greet();
int init_writer(bit_writer * writer, void* buffer, size_t bufsize);
int write_bit(bit_writer * writer, int bit);
int write_bits(bit_writer* writer, uint64_t bits, size_t len);

int init_reader(bit_reader * reader, void* buffer, size_t bit_len);
int read_bit(bit_reader* reader);
int read_bits(bit_reader* reader, size_t len, uint64_t * result);

static inline bit_writer* new_writer(void* buffer, size_t bufsize) {
        bit_writer * writer = (bit_writer*) malloc(sizeof(bit_writer));
        if (writer) {
                init_writer(writer, buffer, bufsize);
        }
        return writer;
}

static inline bit_reader* new_reader(void* buffer, size_t bufsize) {
        bit_reader * reader = (bit_reader*) malloc(sizeof(bit_reader));
        if (reader) {
                init_reader(reader, buffer, bufsize);
        }
        return reader;
}

static inline size_t left_bits(bit_writer * writer) {
        return writer->avail;
}