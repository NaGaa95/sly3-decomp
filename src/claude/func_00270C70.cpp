// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// WriteTft (Sly 2 WriteTft__FP3TFTP5OSTRMPPcPci), plain C++.
struct TFT { int fLeft, fPlus, fSpace, fPrefix, fZero, fPrec0, width, precision, cbits, rowItems, rowCount; unsigned char conversion; int fUpper; };
class OSTRM { public: char *buffer; int capacity, used; char unknownC[4]; int count, buffered; int CbWrite(void *, int) __asm__("func_0025A2D0"); };
void WriteTftPchz(TFT *, OSTRM *, char *) __asm__("func_0026FF90");
void WriteTftUl(TFT *, OSTRM *, unsigned long) __asm__("func_002702E8");
extern "C" void func_00270A18(TFT *, OSTRM *, double);
extern "C" unsigned int strlen(const char *);
static inline char *Next(char **args) { char *p = *args; *args = p + 8; return p; }
static inline void WritePchz(OSTRM *out, char *s) { out->CbWrite(s, strlen(s)); }
extern "C" void func_00270C70(TFT *f, OSTRM *out, char **args, char *text, int count)
{
    switch (f->conversion) {
    case '%': out->CbWrite(&f->conversion, 1); break;
    case 'c': { unsigned char c = *(unsigned char *)Next(args); out->CbWrite(&c, 1); break; }
    case 's': WriteTftPchz(f, out, *(char **)Next(args)); break;
    case 'p': f->precision = 8; f->conversion = 'x'; f->cbits = 0;
    case 'b': case 'd': case 'i': case 'o': case 'u': case 'x': {
        unsigned long n;
        switch (f->cbits) {
        case 0: case 1: n = *(unsigned int *)Next(args); break;
        case 2: n = *(unsigned long *)Next(args); break;
        }
        WriteTftUl(f, out, n); break;
    }
    case 'e': case 'f': case 'g':
        if (f->rowItems) {
            float *p = *(float **)Next(args);
            char *newline = "\n";
            char *rowSep = ",\n", *rowOpen = "{ ", *itemSep = ", ", *rowClose = " }";
            if (f->rowCount > 1) WritePchz(out, newline);
            int row, i;
            for (row = 0; row < f->rowCount; row++) {
                if (row) WritePchz(out, rowSep);
                WritePchz(out, rowOpen);
                for (i = 0; i < f->rowItems; i++) {
                    if (i) WritePchz(out, itemSep);
                    func_00270A18(f, out, (double)*p++);
                }
                WritePchz(out, rowClose);
            }
            if (f->rowCount > 1) WritePchz(out, newline);
        } else func_00270A18(f, out, *(double *)Next(args));
        break;
    case 'n':
        switch (f->cbits) {
        case 0: { int *d = *(int **)Next(args); *d = out->count; } break;
        case 1: { short *d = *(short **)Next(args); int c = out->count; *d = c; } break;
        case 2: { long *d = *(long **)Next(args); *d = out->count; } break;
        }
        break;
    default: out->CbWrite(text, count); break;
    }
}
