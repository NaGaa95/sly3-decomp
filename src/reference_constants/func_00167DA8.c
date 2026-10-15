// Complete original Sly3 body; ordinary source/profile reconstruction.
// A1 indexes the original400-byte descriptor array; corresponding output records have80-byte stride. Native modular division constant and shift follow those two distinct real strides.
// SLY3_CFLAGS: -Os -G0
struct Entry { char data[0x190]; }; extern struct Entry D_0036C330[]; void *func_00167DA8(char *p,struct Entry *entry) { return p+0x370+(entry-D_0036C330)*0x50; }
