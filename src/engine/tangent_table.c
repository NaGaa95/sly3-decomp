// SLY3_CFLAGS: -Os -G0
extern float D_0036B168[3];
extern float D_0036B178[3][16];
struct TangentAmplitudes { float values[3]; };
extern const struct TangentAmplitudes D_0031F690;
float tanf(float angle);
void func_0012CF90(void)
{
    struct TangentAmplitudes amplitudes=D_0031F690;
    int row,index;
    D_0036B168[0]=0.0625f;
    D_0036B168[2]=0.0009765625f;
    D_0036B168[1]=0.0009765625f;
    for(row=0;row<3;++row) {
        float amplitude=amplitudes.values[row];
        for(index=0;index<16;++index)
            D_0036B178[row][index]=tanf((float)index*0.098174773f)*amplitude;
    }
}
