// SLY3_CFLAGS: -Os -G0
struct StateView { unsigned char prefix[0x13C]; int state; };
int func_00277610(struct StateView *view)
{
    int state=view->state;
    if(state==10) goto yes;
    if(state<11) { if(state==6) goto yes; }
    else if(state==13) goto yes;
    return 0;
yes:
    return 1;
}
