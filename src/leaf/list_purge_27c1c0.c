// SLY3_CFLAGS: -Os -G0
void func_0023EDC8(void *owner,void *object);
void func_0023DEF8(void *owner,void *object,void *list);
void func_0027C1C0(void *owner,void *object)
{
    unsigned i;
    func_0023EDC8(owner,object);
    func_0023DEF8(owner,object,(char *)owner+0x358);
    for(i=0;i<4;i++)
        func_0023DEF8(owner,object,(char *)owner+i*0x60+0x194);
}
