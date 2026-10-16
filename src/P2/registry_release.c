// SLY3_CFLAGS: -Os -G0
struct RegistryNode { unsigned char prefix[0x18]; int id; };
extern char D_0046F540[];
int func_0021DD30(struct RegistryNode *node);
struct RegistryNode *func_0021DC30(void *registry,int id);
void func_0021DC60(void *registry,int id,struct RegistryNode *replacement);
void func_0011B028(void *list,void *node);
void func_0021DE60(struct RegistryNode *node)
{
    struct RegistryNode *previous;
    if(func_0021DD30(node)) {
        if(node->id!=-1)
            previous=func_0021DC30(D_0046F540,node->id);
        func_0011B028(D_0046F540,node);
        if(node->id!=-1) {
            func_0021DC60(D_0046F540,node->id,previous);
            node->id=-1;
        }
    }
}
