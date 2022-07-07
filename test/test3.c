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
        uint8_t buffer[32];
        bit_writer* writer = new_writer(buffer, 32);
        TWBs(0x47048364, 32, 32);
        TWBs(0xc753, 16, 16);
        TWBs(0x64, 8, 8);
        TWBs(0xc353a302, 64, 64);
        // writer_flush(writer);
        
        bit_reader* reader = new_reader(buffer, 32<<3);
        TRBs(32, 32, 0x47048364);
        TRBs(16, 16, 0xc753);
        TRBs(8, 8, 0x64);
        TRBs(64, 64, 0xc353a302);
        free(writer);
        free(reader);
        return 0;
}