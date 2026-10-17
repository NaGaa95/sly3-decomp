// SLY3_CFLAGS: -Os -G0
struct Eight { unsigned char bytes[8]; };
struct TableRequest { int size,kind; };
struct CloneReceiver {
    unsigned char prefix[0x10];
    int key;
    unsigned char gap14[0xBC];
    struct Eight preserved;
    unsigned char gapD8[0x30];
    void *object;
    unsigned char gap10C[0x24];
    void *table;
};
extern char D_0034A040[];
void func_0028FE20(void *destination,void *source);
void *func_001D24D0(struct TableRequest *request,void *source);
void *func_001507E0(void *object,int key);
void func_00274030(struct CloneReceiver *destination,void *source)
{
    struct Eight preserved=destination->preserved;
    func_0028FE20(destination,source);
    destination->preserved=preserved;
    if(destination->table!=D_0034A040) {
        struct TableRequest local;
        struct TableRequest *request=&local;
        local.size=0x30;
        request->kind=0x10;
        destination->table=func_001D24D0(request,destination->table);
    }
    destination->object=func_001507E0(destination->object,destination->key);
}
