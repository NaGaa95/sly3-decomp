// SLY3_CFLAGS: -Os -G0
struct ActionEligibilityRecord { unsigned char prefix[0x48]; int blocked; };
int func_002533C0(void *,int);
void *func_002387A8(void *,int);
int func_00251368(void *);
int func_0013B500(void *,int);
int func_002513D0(void *receiver,int action)
{
    struct ActionEligibilityRecord *record;
    if(action==-1) return 1;
    if(func_002533C0(receiver,7)) return 0;
    record=(struct ActionEligibilityRecord *)func_002387A8((char *)receiver+0x29C,0xD3);
    if(record && record->blocked) return 0;
    switch(action) {
    case 14: case 16: case 22: return 1;
    case 20: return !func_0013B500(receiver,0x3D);
    case 12: case 15: return !func_00251368(receiver);
    case 10:
        return !(func_0013B500(receiver,0x3B) ||
                 func_0013B500(receiver,0x3C) ||
                 func_0013B500(receiver,0x3D));
    }
    return 0;
}
