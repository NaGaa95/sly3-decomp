// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the Sly 2 match func_00120548.cpp. One commented register pin (pb in a1).
struct CRef {
    short m_tagk; short m_pad; int m_tag;
    CRef(int n, int tagk) { m_tag = n; m_tagk = tagk; }
};
extern "C" CRef func_001221B8(void *pbasic, CRef *aref);
CRef func_001221B8(void *pbasic, CRef *aref)
{
    CRef *pa = &aref[0];
    register CRef *pb __asm__("$5") = &aref[1];  /* register pin: &aref[1] reuses the dead pbasic register (a1) as in the target */
    int f;
    if (pa->m_tagk != pb->m_tagk) {
        f = 0;
    } else {
        switch (pa->m_tagk) {
        case 0x13: case 0x15: case 0x16: case 0x17:
        case 0x1D: case 0x1E: case 0x1F: case 0x20:
            f = pa->m_tag == pb->m_tag;
            break;
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18:
        case 0x22:
            f = 1;
            break;
        default:
            break;
        }
    }
    return CRef(f, 0x15);
}
