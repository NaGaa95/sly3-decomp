// Sly 2 reference: src/hand/CdPath__FPcT0i.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
extern "C" {
char *strcpy(char *, const char *);
char *strcat(char *, const char *) __asm__("func_00271670");
unsigned int strlen(const char *) __asm__("func_002715F8");
int sprintf(char *, const char *, ...) __asm__("func_00271448");
}
int CpchzTokenizePath(char *pchz) __asm__("func_00162C48");
void CdPath(char *pchzOut, char *pchzIn, int fCdrom) __asm__("func_00162FF0");
void CdPath(char *pchzOut, char *pchzIn, int fCdrom)
{
    char achPath[256];
    int c;
    int i;
    strcpy(achPath, "\\");
    strcat(achPath, pchzIn);
    c = CpchzTokenizePath(achPath);
    char *pch = achPath;
    for (i = 1; i < c; i++) {
        pch[strlen(pch)] = '\\';
    }
    sprintf(pchzOut, "%s\\%s", fCdrom ? "cdrom0:" : "", achPath);
}
