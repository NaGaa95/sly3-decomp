// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
extern "C" {
char *func_00271978(char *);
char *func_00271670(char *, const char *);
unsigned int strlen(const char *);
}
extern "C" int func_00162C48(char *pchz)
{
    func_00271978(pchz);
    int cch = strlen(pchz);
    if (cch != 0 && ((unsigned char *)pchz)[cch - 1] != '\\' && ((unsigned char *)pchz)[cch - 1] != '/') {
        func_00271670(pchz, ";1");
        cch = strlen(pchz);
    }
    unsigned char *pchEnd = (unsigned char *)pchz + cch;
    unsigned char *pchOut = (unsigned char *)pchz;
    unsigned char *pch = (unsigned char *)pchz;
    int cpchz = 0;
    int cchCur = 0;
    int cchMax = 8;
    for (; pch < pchEnd; pch++) {
        switch (*pch) {
        case '/':
        case '\\':
            if (cchCur == 0)
                break;
            *pchOut++ = 0;
            cchCur = 0;
            cchMax = 8;
            cpchz++;
            break;
        case '.':
            if (cchCur == 0)
                break;
            if (cchMax != 8)
                break;
            *pchOut++ = *pch;
            cchCur = 0;
            cchMax = 3;
            break;
        case ';':
            if (cchCur != 0 && pch == pchEnd - 2 && pch[1] == '1') {
                *pchOut++ = *pch++;
                *pchOut++ = *pch;
                cchCur += 2;
                break;
            }
        default:
            if (cchCur < cchMax) {
                __asm__ __volatile__("" : : : "memory"); /* same barrier as Sly 2 CpchzTokenizePath */
                unsigned char ch = *pch;
                if ((unsigned char)(ch - 'A') < 26 || (unsigned char)(ch - '0') < 10)
                    *pchOut = ch;
                else
                    *pchOut = '_';
                pchOut++;
                cchCur++;
            }
            break;
        }
    }
    if (cchCur != 0) {
        *pchOut = 0;
        cpchz++;
    }
    return cpchz;
}
