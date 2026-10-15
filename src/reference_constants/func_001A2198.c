// Original USA entry 0x1a2198; ordinary C reconstruction.
// Receiver A0 and other object A1 supply unsigned32-bit masks at F0/164. Original AND plus SLTU returns the integer Boolean; no other input is read.
// SLY3_CFLAGS: -Os -G0
int func_001A2198(char *p,char *other)  {
    return (*(unsigned int *)(p+0xF0)&*(unsigned int *)(other+0x164))!=0;
}
