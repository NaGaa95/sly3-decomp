// Sly 3 USA icon.sys metadata writer; complete original code/data independently verified.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct {
    char Head[4];
    unsigned short Reserv1;
    unsigned short OffsLF;
    unsigned int Reserv2;
    unsigned int TransRate;
    int BgColor[4][4];
    float LightDir[3][4];
    float LightColor[3][4];
    float Ambient[4];
    unsigned short TitleName[34];
    unsigned char FnameView[64];
    unsigned char FnameCopy[64];
    unsigned char FnameDel[64];
    unsigned char Reserve3[512];
} ICONSYS;
typedef char icon_sys_size3C4[(sizeof(ICONSYS) == 0x3C4) ? 1 : -1];
char *strcpy(char *, const char *);
void *func_00292034(void *, int, unsigned int);
void func_00238308(char *, unsigned short *);
int func_00271448(void *, char *, ...);
int func_001D09C8(void *s, void *name, void *b, int n);

int func_001D00A0(void *p, char *dir, char *title)
{
    ICONSYS icon;
    char name[0x50];
    func_00292034(&icon, 0, sizeof(icon));
    /* Copy through the complete object representation: five bytes including NUL. */
    strcpy((char *)&icon, "PS2D");
    func_00238308(title, icon.TitleName);
    icon.OffsLF = 0x20;
    icon.TransRate = 0x60;
    icon.BgColor[0][0] = 0;
    icon.BgColor[0][1] = 0x87;
    icon.BgColor[0][2] = 0xFF;
    icon.BgColor[1][0] = 0;
    icon.BgColor[1][1] = 0x29;
    icon.BgColor[1][2] = 0x6F;
    icon.BgColor[2][0] = 0;
    icon.BgColor[2][1] = 0x29;
    icon.BgColor[2][2] = 0x6F;
    icon.BgColor[3][0] = 0;
    icon.BgColor[3][1] = 0x87;
    icon.BgColor[3][2] = 0xFF;
    icon.LightDir[0][0] = 0.0f;
    icon.LightDir[0][1] = 0.5f;
    icon.LightDir[0][2] = -0.5f;
    icon.LightDir[1][0] = 0.5f;
    icon.LightDir[1][1] = -0.4f;
    icon.LightDir[1][2] = 0.1f;
    icon.LightDir[2][0] = -0.5f;
    icon.LightDir[2][1] = 0.5f;
    icon.LightDir[2][2] = 0.5f;
    icon.LightColor[0][0] = 0.14f;
    icon.LightColor[0][1] = 0.03f;
    icon.LightColor[0][2] = 0.48f;
    icon.LightColor[1][0] = 0.33f;
    icon.LightColor[1][1] = 0.0f;
    icon.LightColor[1][2] = 0.33f;
    icon.LightColor[2][0] = 0.14f;
    icon.LightColor[2][1] = 0.14f;
    icon.LightColor[2][2] = 0.38f;
    icon.Ambient[0] = 0.5f;
    icon.Ambient[1] = 0.5f;
    icon.Ambient[2] = 0.5f;
    strcpy((char *)icon.FnameView, "memcard_icon.ico");
    strcpy((char *)icon.FnameCopy, "memcard_icon.ico");
    strcpy((char *)icon.FnameDel, "memcard_icon.ico");
    func_00271448(name, "%s/%s", dir, "icon.sys");
    return func_001D09C8(p, name, &icon, sizeof(icon));
}
