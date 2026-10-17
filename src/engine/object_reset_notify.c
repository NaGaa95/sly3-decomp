// SLY3_CFLAGS: -Os -G0
extern const int D_003210E4;
void func_00239FE0(void *token,int value);
void func_00170F60(void *object,int mode);
struct ResetObject { unsigned char prefix[0x13C]; void *token; unsigned char gap[0x144-0x140]; int word144; };
void func_00171050(struct ResetObject *object)
{
    object->word144=0;
    func_00239FE0(object->token,D_003210E4);
    func_00170F60(object,3);
}
