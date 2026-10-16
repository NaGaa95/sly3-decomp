// SLY3_CFLAGS: -Os -G0
struct EngineInitOwner { unsigned char prefix[0x1190]; void *handle; };
void func_00152488(void *owner);
void *func_0023DDA0(void *owner,int identity,int kind);
void func_001C1B68(void *owner,void *a,void *b);
void func_001C1410(void *owner,void *record,void *output);
void func_00258958(void *record);
void func_0017E760(void *target,void *owner,int value,void *record);
void func_00155190(void *owner,int id);
void func_0013D480(struct EngineInitOwner *owner)
{
    char *base=(char *)owner;
    func_00152488(owner);
    owner->handle=func_0023DDA0(owner,0x22,1);
    func_001C1B68(owner,base+0x1530,base+0x1630);
    func_001C1410(owner,base+0x1660,base+0x1760);
    func_00258958(base+0x1470);
    func_00258958(base+0x1770);
    func_0017E760(base+0x1830,owner,*(int *)(base+0x1760),base+0x1660);
    func_00155190(owner,0x2E);
}
