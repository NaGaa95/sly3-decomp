// SLY3_CFLAGS: -Os -G0
extern unsigned char D_00321AA0[];
extern unsigned char *D_00344FC8[];
int func_0025E188(void);
void *func_0018B658(int index)
{
    int selector=func_0025E188();
    unsigned char *base;
    if(selector!=-1) base=D_00344FC8[selector]; else base=D_00321AA0;
    if(!base) return 0;
    return base+index*0x14;
}
