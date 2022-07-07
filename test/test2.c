#include "bit.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TWB(x,y) assert(write_bit(writer, x) == y)

#define TWBs(x, l, y) assert(write_bits(writer, x, l) == y)

#define TRB(x) assert(read_bit(reader) == x)

#define TRBs(l,x,y) \
do {\
        assert(read_bit(reader, l, &tmp) == x);\
        assert(tmp == y);\
}while(0)

uint32_t data = 0xc753a302;

int main() {
        uint64_t tmp;
        uint8_t buffer[10];
        bit_writer* writer = new_writer(buffer, 10);
        uint32_t data0 = data;
        for (int i = 0; i < 32; i++) {
                TWB(data0, 0);
                data0 >>= 1;
        }

        bit_reader* reader = new_reader(buffer, 80);
        data0 = data;
        for (int i = 0; i < 32; i++) {
                printf("%d\n", i);
                int r = data0 & 1;
                TRB(r);
                data0 >>= 1;
        }
        
        free(writer);
        free(reader);
        return 0;
}