// SLY3_CFLAGS: -Os -G0
extern const float D_00322058[3];
void func_0019DDC8(char *self,float scale)
{
    *(float *)(self+0x3E8)=D_00322058[0]*scale;
    *(float *)(self+0x3EC)=D_00322058[1]*scale;
    *(float *)(self+0x3F0)=D_00322058[2];
}
