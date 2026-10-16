// SLY3_CFLAGS: -Os -G0
struct ResourceLoadRequest { int bytes; int alignment; };
struct ResourceLoadRecord { unsigned char content[64]; void *owner; };
struct ResourceLoadOwner {
    unsigned char prefix[0x40];
    int count;
    void *records;
    int mode;
    unsigned char reserved4C[0x14];
    int key60, key64, key68, key6C;
    unsigned char reserved70[0x10];
    float gain;
    unsigned int word84, word88;
    unsigned char reserved8C[0x20];
    unsigned int wordAC;
    struct ResourceLoadRecord *record;
    void *heap;
};
extern unsigned char D_0047A4A0[], D_0047A4B0[], D_004797A8[];
void func_001C7D98(void *,void *);
int func_00119128(void *);
float func_00119260(void *);
unsigned int func_001190A8(void *);
void *func_001D2538(struct ResourceLoadRequest *);
void func_00119948(void *,void *);
void func_0011AD80(void *,void *);
void func_00263118(void *,void *);
void func_002631C8(void *,void *);

void func_00260810(struct ResourceLoadOwner *owner,void *stream)
{
    int dynamic;
    owner->key60=0x377;
    owner->key64=0x376;
    owner->key68=0x378;
    func_001C7D98(owner,stream);
    dynamic=func_00119128(stream);
    owner->gain=func_00119260(stream);
    owner->word84=func_001190A8(stream);
    owner->word88=func_001190A8(stream);
    owner->wordAC=func_001190A8(stream);
    if(dynamic) {
        struct ResourceLoadRequest request;
        owner->mode=0;
        request.bytes=80;
        request.alignment=16;
        owner->heap=D_0047A4A0;
        owner->record=(struct ResourceLoadRecord *)func_001D2538(&request);
        owner->record->owner=owner;
        func_00119948(stream,owner->record);
        func_0011AD80(D_004797A8,owner->record);
    } else {
        owner->mode=1;
        owner->heap=D_0047A4B0;
        func_00263118(owner,stream);
        func_002631C8(owner,stream);
    }
    owner->key6C=-1;
}
