// SLY3_CFLAGS: -Os -G0
struct Setting {
    unsigned char prefix[0x184];
    int first;
    int second;
    float stamp;
};
extern float D_0036BB98;
void func_001F4DD8(struct Setting *setting, int first, int second, float stamp)
{
    setting->first = first;
    setting->second = second;
    if (stamp == -3.40282347e+38f)
        setting->stamp = D_0036BB98;
    else
        setting->stamp = stamp;
}
