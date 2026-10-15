// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
unsigned int func_002715F8(char *s);
void func_001D2898(void *dst, void *src, int cb);
char *func_00271670(char *pchzDst, char *pchzSrc)
{
    unsigned int dstLength = func_002715F8(pchzDst);
    unsigned int srcLength = func_002715F8(pchzSrc);
    func_001D2898(pchzDst + dstLength, pchzSrc, srcLength + 1);
    return pchzDst;
}
