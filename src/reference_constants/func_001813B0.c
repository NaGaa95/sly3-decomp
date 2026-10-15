// Original USA entry 0x1813b0; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct Packed  {
    int value;
} __attribute__((packed));
void func_001813B0(char *p)  {
    *(int *)(p+8)=*(int *)(p+4);
    *(int *)(p+0x10)=*(int *)(p+0x14);
    *(struct Packed *)(p+0x168)=*(struct Packed *)(p+0x16C);
    *(struct Packed *)(p+0x164)=*(struct Packed *)(p+0x168);
    *(int *)(p+0x160)=0;
}
