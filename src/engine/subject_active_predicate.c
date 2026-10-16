// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"
struct KEY;
struct SubjectPredicate { char prefix[0x44]; int mode; char unused48[0xE0-0x48]; unsigned int key_word; };
extern unsigned char D_00468D30[];
CRef *func_002BC010(CRef *output, struct KEY *key, unsigned char *buffer);
int func_00188A38(struct SubjectPredicate *subject)
{
    if (subject->mode == -1 && subject->key_word) {
        CRef value;
        int result;
        func_002BC010(&value, (struct KEY *)&subject->key_word, D_00468D30);
        result = value.payload.integer;
        func_0012BC20(&value);
        return result;
    }
    return subject->mode >= 2;
}
