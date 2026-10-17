// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Weight { unsigned char prefix[8]; float value; unsigned char gapC[8]; };
struct Slot { unsigned char prefix[8]; short weight; unsigned char gapA[0xE]; };
struct Table { unsigned char prefix[4]; struct Weight *weights; struct Slot *slots; };
void func_002673F8(struct Table *table,int slot,void *extra,float value);
static inline float Max(float a,float b)
{
    return a>b?a:b;
}
static inline float Min(float a,float b)
{
    return a<b?a:b;
}
void func_00267370(struct Table *table,int slot,void *extra,float amount)
{
    float scale=Max(amount,0.0f);
    int index;
    scale=Min(scale,1.0f);
    index=table->slots[slot].weight;
    if(index>=0)
        func_002673F8(table,slot,extra,table->weights[index].value*scale);
}
