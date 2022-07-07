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
        uint8_t *buffer = malloc(64);
        bit_writer* writer = new_writer(buffer, 64); 
        TWBs(0x47048364,64,64);
        TWBs(0x47048364,16,16);
        TWB(1,0);TWB(1,0);TWB(0,0);TWB(1,0);
        TWB(0,0);TWB(0,0);TWB(1,0);TWB(1,0);
        TWBs(0x47048364,32,32);
        // writer_flush(writer);
        
        bit_reader* reader = new_reader(buffer, 64<<3);
        TRB(0);TRB(0);TRB(1);TRB(0);
        TRB(0);TRB(1);TRB(1);TRB(0);
        TRBs(32, 32, 0x00470483);
        TRBs(64, 64, 0x8364cb8364000000);
        TRBs(8, 8, 0x04);
        TRBs(8, 8, 0x47);
        free(writer);
        free(reader);
        free(buffer);
        return 0;
}