// Original integer status protocol; receiver and stored payload remain opaque.
// SLY3_CFLAGS: -Os -G0
#include "save_bootstrap_api.h"
struct S { char pad[0x13950]; void *x; };
extern char D_003751D0[];
int func_001D0658(void *save);
int func_001D0410(void *save, void *payload);
void func_001D0D30(void *menu, int selection);

int func_001CFB90(void *save)
{
    struct S *s = save;
    int result = func_001D0658(s);
    if (!result) result = func_001CF7B8(s);
    if (!result) result = func_001D0410(s, s->x);
    if (result) func_001D0D30(D_003751D0, 3);
    return result;
}
