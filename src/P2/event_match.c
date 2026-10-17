// SLY3_CFLAGS: -Os -G0
struct Node { unsigned char gap0[8]; struct Node *next; };
struct Handler { unsigned char prefix[0x34]; struct Node *node; unsigned char gap38[0x28]; int key; int matched; };
struct Event { int key; int unused4; struct Node *target; };
void func_0013BEC0(struct Handler *self,int event,struct Event *data);
void func_00226500(struct Handler *self,int event,struct Event *data)
{
    func_0013BEC0(self,event,data);
    if(event==0xB&&data->key==self->key&&data->target==self->node->next->next)
        self->matched=1;
}
