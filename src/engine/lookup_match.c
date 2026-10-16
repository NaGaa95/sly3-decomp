// SLY3_CFLAGS: -Os -G0
struct EngineLookupOwner { unsigned char prefix[0x1108]; void *lookup; };
int func_00173428(void *lookup);
int func_0025E188(void);
int func_00172CF8(void *lookup);
int func_00156D48(struct EngineLookupOwner *owner)
{
    int valid=0;
    int a,b;
    if(owner->lookup) valid=func_00173428(owner->lookup)!=0;
    if(!valid) return 0;
    a=func_0025E188();
    b=func_00172CF8(owner->lookup);
    if(a==b || a==-1 || b==-1) return 1;
    return 0;
}
