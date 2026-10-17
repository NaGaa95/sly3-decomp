// SLY3_CFLAGS: -Os -G0
struct SoundRow { int id0; int id; };
extern struct SoundRow D_003210E0[];
int func_00239E70(void *token);
void func_00170F60(void *object,int mode);
struct DispatchObject { unsigned char prefix[0x130]; int state; unsigned char gap134[0x13C-0x134]; void *token; unsigned char gap140[0x144-0x140]; int row; };
void func_00170EE0(struct DispatchObject *object)
{
    int seen;
    do {
        seen=object->state;
        if(seen<3) {
            if(seen>=0) {
                if(func_00239E70(object->token)==D_003210E0[object->row].id) func_00170F60(object,3);
            }
        }
    } while(seen!=object->state);
}
