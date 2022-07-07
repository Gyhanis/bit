#include "bit.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TWB(x,y) assert(write_bit(writer, x) == y)

#define TWBs(x, l, y) assert(write_bits(writer, x, l) == y)

#define TRB(x) assert(read_bit(reader) == x)

#define TRBs(l,x,y) \
do {\
        assert(read_bits(reader, l, &tmp) == x);\
        assert(tmp == y);\
}while(0)

int main() {
        uint64_t tmp;
        uint8_t *buffer = malloc(9);
        bit_writer* writer = new_writer(buffer, 9); 
        TWBs(0x47048364,64,64);
        TWBs(0x4f, 8, 8);
        
        bit_reader* reader = new_reader(buffer, 9<<3);
        TRB(0);TRB(0);TRB(1);TRB(0);
        TRBs(64, 64, 0xf000000004704836);
        TRBs(4, 4, 0x4);
        free(writer);
        free(reader);
        free(buffer);
        return 0;
}