// Original USA entry 0x1c3d78; ordinary C reconstruction.
// State record A0 and target object A1 are explicit; flags6C bit0 is set and signed state4 values5 or9..13 clear target54. The native switch tree, every branch and complete original return match.
// SLY3_CFLAGS: -Os -G0
void func_001C3D78(char *p,char *object)  {
    *(unsigned int *)(object+0x6C)|=1;
    switch(*(int *)(p+4)) {
        case 5:case 9:case 10:case 11:case 12:case 13:*(int *)(object+0x54)=0;
    }
}
