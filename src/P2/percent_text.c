// SLY3_CFLAGS: -Os -G0
extern char D_00375290[],D_004BC268[],D_00468D30[],D_003261C8[];
int func_001CFDF8(void *save);
int func_0025E6D0(void *record);
int func_00271448(char *output,const char *format,...);
unsigned short *func_002717E0(unsigned short *destination,const char *source);
void func_00222750(unsigned short *output)
{
    char buffer[16];
    void *record=func_001CFDF8(D_00375290) ? D_004BC268 : D_00468D30;
    func_00271448(buffer,D_003261C8,func_0025E6D0(record));
    func_002717E0(output,buffer);
}
