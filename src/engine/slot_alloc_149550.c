// SLY3_CFLAGS: -Os -G0
struct SlotNode { unsigned char prefix[0x1088]; void *extra; void *list; };
void *func_0011E118(void *pool);
void func_0011E1F0(void *pool, void *node);
void func_0011AF60(void *list, void *node);
struct SlotNode *func_00149550(char *self, int mode, void *list)
{
    struct SlotNode *node;
    if(!*(int *)(self + 0x4888)) goto fail;
    node = func_0011E118(self + 0x487C);
    if(!node) goto fail;
    if(mode == 2) {
        node->extra = func_0011E118(self + 0x4894);
        if(!node->extra) {
            func_0011E1F0(self + 0x487C, node);
fail:
            return 0;
        }
    }
    node->list = list;
    func_0011AF60(list, node);
    return node;
}
