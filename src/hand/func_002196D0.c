// Initialize the actual inherited receiver and store both original looked-up resources using all four explicit context/kind/identifier/option inputs. Lookup wrapper17E1B8 generates its own remaining arguments.
// Reference compiler shape: src/hand/func_0022FBE0.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct S {
    char unknown_0[0xA0];
    void * first;
    void * second;
};
extern char D_00475480[];
void func_001C7DC8(void *receiver);
void *func_0017E1B8(void *context,int kind,int identifier,void *owner);
void func_002196D0(struct S *p) {
    func_001C7DC8(p);
    p->first=func_0017E1B8(D_00475480,0x405,0x798,0);
    p->second=func_0017E1B8(D_00475480,0x405,0x799,0);
}
