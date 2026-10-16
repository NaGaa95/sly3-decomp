// SLY3_CFLAGS: -Os -G0
struct ThreeArrayDefaults {
    char unaccessed[0x70];
    float scalar70;
    int word74,word78,word7C;
    char unaccessed80[0x90-0x80];
    float scalar90,scalar94,scalar98;
    char unaccessed9C[0xA4-0x9C];
    int wordA4;
    float scalarA8;
};
extern float D_00321D60;
void func_001C7340(void *receiver);
void func_00198798(struct ThreeArrayDefaults *owner)
{
    func_001C7340(owner);
    owner->scalar70=5500.0f;
    owner->word74=owner->word7C=owner->word78=1;
    owner->scalar90=30.0f;
    owner->scalar94=50.0f;
    owner->scalar98=2.5f;
    owner->wordA4=1;
    owner->scalarA8=D_00321D60;
}
