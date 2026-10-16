// SLY3_CFLAGS: -Os -G0
struct EngineRequest { int words[5]; };
struct EngineRequestOwner { unsigned char prefix[0xD8]; int count; struct EngineRequest requests[1]; };
void func_00170410(void *owner,struct EngineRequest *request,int mode);
void func_00170360(struct EngineRequestOwner *owner)
{
    int i;
    for(i=0;i<owner->count;i++) func_00170410(owner,&owner->requests[owner->count],0);
}
