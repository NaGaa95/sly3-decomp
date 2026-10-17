// SLY3_CFLAGS: -Os -G0
struct BindNode { unsigned char prefix[0xAC]; struct BindNode *next; void *sub; };
struct BindSelf { unsigned char prefix[0xF84]; struct BindNode *first; unsigned char gapF88[0xF90-0xF88]; struct BindNode *second; };
char *func_001F4A80(void *self);
void func_00262770(void *node,void *controller);
void func_002643D0(void *node,void *value);
void func_00156B00(struct BindSelf *self)
{
    struct BindNode *node=self->first;
    char *controller=func_001F4A80(self);
    if(node) {
        func_00262770(node,controller);
        func_002643D0(node,controller+0x150);
    }
    node=self->second;
    if(node) {
        if(node->sub) func_002643D0(node->sub,controller+0x150);
        node=node->next;
        if(node) {
            func_00262770(node,controller);
            func_002643D0(node,controller+0x150);
        }
    }
}
