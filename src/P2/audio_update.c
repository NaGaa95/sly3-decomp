// SLY3_CFLAGS: -Os -G0 -ffast-math
struct AudioUpdateView {
    unsigned char prefix[0x14];
    int route;
    float pitch;
    unsigned char reserved1C[0x28];
    int handle;
    float gain;
    unsigned char reserved4C[0x10];
    unsigned short dirty;
    unsigned char reserved5E[0x12];
    float channelGain[6];
    int channelWord[6];
    unsigned char reservedA0[0x31C];
    int dirtyChannels;
};
void func_00291CE8(int signature, int command, int handle, int mask, int value, int route, int pitch);

void func_002465E0(struct AudioUpdateView *audio)
{
    int i;
    if (audio->dirty&0x70) {
        int flags=0;
        int volume, pitch;
        if (audio->dirty&0x10) {
            flags=1;
            volume=(int)(audio->gain*1024.0f);
        }
        if (audio->dirty&0x20)
            flags|=4;
        if (audio->dirty&0x40) {
            flags|=8;
            pitch=(int)(audio->pitch*1524.0f);
        }
        func_00291CE8(0x524B5553, 5, audio->handle, flags, volume, audio->route, pitch);
    }
    if (audio->dirty&0x180) {
        for (i=0; i<6; i++) {
            int mask=1<<i;
            if (audio->dirtyChannels&mask)
                func_00291CE8(0x524B5553, 6, audio->handle, i,
                    (int)(audio->channelGain[i]*1024.0f), audio->channelWord[i], 0);
        }
        audio->dirtyChannels=0;
    }
}
