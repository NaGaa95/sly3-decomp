// Original USA entry 0x135e88; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
void func_001C7340(void *);
void func_0011AF38(void *,int);
void func_00135E88(char *p)  {
    float *value;
    func_001C7340(p);
    func_0011AF38(p+0x40,0x2C);
    value=(float *)(p+0x70);
    *(float *)(p+0x68)=1.0f;
    value[0]=1.0f;
    ((int *)value)[1]=0;
    ((int *)value)[2]=0;
    *(float *)(p+0x84)=1.0f;
    *(int *)(p+0x80)=0;
    *(unsigned int *)(p+0x3C)|=0x80;
}
