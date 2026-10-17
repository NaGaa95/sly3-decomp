// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Stats { unsigned char prefix[0x190]; int done[2]; int total[2]; };
struct Meter { unsigned char prefix[0x128]; float ratio[2]; unsigned char gap130[0xC]; struct Stats *stats; };
void func_0021B6C0(struct Meter *meter)
{
    int i;
    for(i=0;i<2;i++) {
        int total=meter->stats->total[i];
        if(total>0)
            meter->ratio[i]=(float)meter->stats->done[i]/(float)total;
        else
            meter->ratio[i]=0.0f;
    }
}
