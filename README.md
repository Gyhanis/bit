# C Library of bit stream read write

## Feature

Optimized for speed.

## API 

### Writer API

`bit_writer* new_writer(void* buffer, size_t bufsize);`  
`int init_writer(bit_writer * writer, void* buffer, size_t bufsize);`  
Create/Initilize a writer on _buffer_ of size _bufsize_ in bytes.

`int write_bit(bit_writer * writer, int bit);`  
Write the least significant bit of _bit_ to buffer.  
Returns 0 on success. -1 otherwise.

`int write_bits(bit_writer* writer, uint64_t bits, size_t len);`  
Write _len_ least significant bits of _bits_ to buffer.  
Returns _len_ on success, -1 otherwise. No bits are written 
on failure.

`size_t written_len(bit_writer * writer);`  
Return the number of bits written.

`size_t left_bits(bit_writer * writer);`  
Returns the length of available space to write in __bits__.  
If a reader is passed instead of a writer, returns the 
number of bits to be read. 

### Reader API 

`bit_reader* new_reader(void* buffer, size_t bufsize);`  
`int init_reader(bit_reader * reader, void* buffer, size_t bit_len);`  
Create/Initilize a reader on _buffer_ of size _bufsize_ in __bits__.

`int read_bit(bit_reader * reader);`  
Read a bit from buffer.  
Returns the bit on success. -1 otherwise.

`int read_bits(bit_reader* reader, size_t len, uint64_t *result);`  
Read _len_ bits of _bits_ from buffer 
and put the result in _result_.  
Returns _len_ on success, -1 otherwise. No bits are read 
on failure.

`size_t read_len(bit_reader * reader);`  
Return the number of bits read.

### Other
`int bit_greet();`  
Print greeting;  
Always return 0;