// Complete original Sly3 body; ordinary source/profile reconstruction.
// A0 is byte count, A1 is allocator receiver. The actual virtual allocator receives A2 type0x12 through117B40;117B40 zeroes the allocated byte count and returns its pointer.
// SLY3_CFLAGS: -Os -G0
void *func_00117B40(void *,unsigned int,int); void *func_00149028(unsigned int size,void *allocator) { return func_00117B40(allocator,size,0x12); }
