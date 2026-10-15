// Original USA entry 0x1f57e0; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
int func_001F57E0(void *unused,int event)  {
    switch(event)  {
        case 12:return 0x204;
        case 0:return 0x260;
        case 2:return 0x261;
        case 4:return 0x262;
        case 7:return 0x263;
        default:return -1;
    }
}
