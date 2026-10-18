// SLY3_CFLAGS: -Os -G0
struct AttachOwner { char prefix[0x35C]; unsigned int count; int kinds[8]; };
extern unsigned char D_00475480[];
int func_0017E208(void *,int,int,void *,int,void **);
int func_00170C28(void *,void *);
void func_00170118(void *,void *,int);
void func_0016FE30(struct AttachOwner *owner,int kind,int context)
{
    if(owner->count < 8) {
        void *objects[256];
        int count=func_0017E208(D_00475480,0x405,kind,0,256,objects);
        int i;
        for(i = 0; i < count; i++) {
            void *object = objects[i];
            if(!func_00170C28(owner,object)) func_00170118(owner,object,context);
        }
        owner->kinds[owner->count++]=kind;
    }
}
