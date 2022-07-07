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
        uint8_t *buffer = malloc(13);
        bit_writer* writer = new_writer(buffer, 13); 
        TWBs(0x47048364,64,64);
        TWBs(0x47048364,16,16);
        TWB(1,0);TWB(1,0);TWB(0,0);TWB(1,0);
        TWB(0,0);TWB(0,0);TWB(1,0);TWB(1,0);
        TWBs(0x47048364,32,-1);
        size_t lb = left_bits(writer);
        TWBs(0x47048364, lb, lb);
        TWB(0, -1);
        
        bit_reader* reader = new_reader(buffer, 13<<3);
        TRB(0);TRB(0);TRB(1);TRB(0);
        TRB(0);TRB(1);TRB(1);TRB(0);
        TRBs(32, 32, 0x00470483);
        TRBs(16, 16, 0);
        TRBs(64, -1, tmp);
        TRBs(48, 48, 0x8364cb836400);
        TRBs(8, -1, tmp);
        TRB(-1);
        free(writer);
        free(reader);
        free(buffer);
        return 0;
}