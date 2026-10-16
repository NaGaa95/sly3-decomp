// SLY3_CFLAGS: -Os -G0
struct SubjectModeIdentifier { char prefix[0x44]; int mode; };
int func_00188AA0(struct SubjectModeIdentifier *subject)
{
    switch (subject->mode) {
    case 0: return 0x6E3;
    case 1: return 0x6E4;
    case 2: return 0x6E5;
    case 3: return 0x6E6;
    }
    return -1;
}
