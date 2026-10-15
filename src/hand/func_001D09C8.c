// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
#include "card_transfer_api.h"
int func_001D0970(void *s, int h, void *b, int c, int *out);
void func_001D08C8(void *s, int h);
int func_001D09C8(void *s, void *a, void *b, int c)
{
    int h = -1;
    int v;
    int r = func_001D0860(s, a, 0x202, &h);
    if (r)
        return r;
    r = func_001D0970(s, h, b, c, &v);
    if (!r && v != c)
        r = 7;
    func_001D08C8(s, h);
    return r;
}
