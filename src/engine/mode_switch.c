// SLY3_CFLAGS: -Os -G0
void func_001B7268(void *context,int a,int b,int c,float value);
void func_00172E60(void *owner,int value);
struct SwitchOwner { unsigned char prefix[0x48]; int mode; void *context; int word50; int value; };
void func_00173280(struct SwitchOwner *owner,int mode)
{
    if(mode==owner->mode) return;
    owner->mode=mode;
    switch(mode) {
    case 0:
        func_001B7268((char *)owner->context+0x320,0x10,0,0,1.0f);
        break;
    case 1:
        func_00172E60(owner,owner->value);
        break;
    case -1:
        owner->value=0;
        break;
    }
}
