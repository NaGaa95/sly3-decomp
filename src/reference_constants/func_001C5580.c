// Original USA entry 0x1c5580; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
void func_001C5A40(void *);
void func_001C5580(char *p,int state)  {
    if(state!=*(int *)(p+332))  {
        func_001C5A40(p);
        *(int *)(p+332)=state;
        if(state)*(int *)(p+336)=0;
        func_001C5A40(p);
    }
}
