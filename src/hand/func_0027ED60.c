// Copy the original16-bit global resource name into the explicit destination when the identifier is present.
// Reference algorithm: src/hand/func_001BBA18.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
struct R { int id; };
const unsigned short *func_00150630(void *global,int id);
unsigned short *func_00271730(unsigned short *destination,const unsigned short *source);
void func_0027ED60(struct R *record,unsigned short *destination)
{
    if(record->id!=-1)func_00271730(destination,func_00150630(D_00475480,record->id));
}
