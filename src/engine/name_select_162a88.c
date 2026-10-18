// SLY3_CFLAGS: -Os -G0 -fno-schedule-insns
extern char D_00320BE0[], D_00320BF0[];
struct FidObject;
int func_0025E098(struct FidObject *object);
const char *func_001505D0(int index);
struct FidObject { unsigned char prefix[4]; int word4; unsigned char gap8[0x3C - 8]; int word3C; };
const char *func_00162A88(struct FidObject *object)
{
    int empty = 0;
    int id;
    if(!object || object->word4 == object->word3C) empty = 1;
    if(empty) return D_00320BE0;
    id = func_0025E098(object);
    return id == -1 ? D_00320BF0 : func_001505D0(id);
}
