// SLY3_CFLAGS: -Os -G0
struct RenderPacketSettings {
    char prefix[0x1A0];
    float first;
    char unused1A4[0x10];
    float second;
};
struct RenderPacketOwner {
    char prefix[0x100];
    char data100[16],unused110[16],data120[16],data130[16],data140[16];
    char unused150[0x190-0x150];
    int count190;
    char unused194[12];
    char data1A0[0x200];
    int count3A0;
    char data3A4[0x80];
    int enabled424;
    void *data428;
    unsigned int unused42C;
    float amount430;
};
struct RenderPacketClock { float time; char unused4[0x40]; float value44; };
union RenderPacketWord { int integer; float scalar; };
extern char D_0036C308[];
extern struct RenderPacketClock D_0036BB98;
void func_0027E420(void *packet,int format,int count,int address,int *bytes,void **output);
void func_0027E4C0(void *packet,int format,int count,const void *source,int address);
void func_0027E5A8(void *packet,int format,int count,const void *source,int address,void ***output);
void func_0014AC48(struct RenderPacketOwner *owner,struct RenderPacketSettings *settings)
{
    void *floatOutput;
    void *wordOutput;
    char *packet=D_0036C308;
    struct RenderPacketClock *clock;
    func_0027E420(packet,0xC,1,5,0,&floatOutput);
    clock=&D_0036BB98;
    ((float *)floatOutput)[0]=settings->first;
    ((float *)floatOutput)[1]=settings->second;
    ((float *)floatOutput)[2]=owner->amount430;
    ((float *)floatOutput)[3]=D_0036BB98.time;
    func_0027E420(packet,0xC,1,6,0,&wordOutput);
    ((union RenderPacketWord *)wordOutput)[0].integer=0;
    if(owner->enabled424)
        ((union RenderPacketWord *)wordOutput)[0].integer|=1;
    ((union RenderPacketWord *)wordOutput)[1].integer=owner->count3A0;
    ((union RenderPacketWord *)wordOutput)[2].integer=owner->count190;
    ((union RenderPacketWord *)wordOutput)[3].scalar=clock->value44;
    func_0027E4C0(packet,0xE,owner->count3A0,owner->data3A4,(int)(0x30u-(unsigned int)owner->count3A0));
    func_0027E4C0(packet,8,1,owner->data120,1);
    func_0027E4C0(packet,8,1,owner->data100,2);
    func_0027E4C0(packet,8,1,owner->data130,3);
    func_0027E4C0(packet,8,1,owner->data140,4);
    func_0027E4C0(packet,0xC,4,owner->data428,0x30);
    func_0027E5A8(packet,0xC,owner->count190,owner->data1A0,0xF,0);
}
