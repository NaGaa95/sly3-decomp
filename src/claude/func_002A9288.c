// Sly 2 counterpart: sceScfGetLanguage (decomp src/lib/sceScfGetLanguage.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct {
  unsigned int spdifMode:1;
  unsigned int screenType:2;
  unsigned int videoOutput:1;
  unsigned int japLanguage:1;
  unsigned int ps1drvConfig:8;
  unsigned int version:3;
  unsigned int language:5;
  unsigned int timezoneOffset:11;
} sceOsdConfigParam;
void func_00293750(sceOsdConfigParam *p);
int func_002A9248(void);
extern unsigned char D_0034DFB4[];
int func_002A9288(void)
{
  sceOsdConfigParam cp;
  int r;
  func_00293750(&cp);
  if (func_002A9248()) {
    r = D_0034DFB4[0];
  } else {
    func_00293750(&cp);
    if (cp.version == 0)
      r = cp.japLanguage;
    else
      r = cp.language;
  }
  return r;
}
