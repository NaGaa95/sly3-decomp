// SLY3_CFLAGS: -Os -G0
struct EngineWalkNode { unsigned char prefix[0x54]; int value; unsigned char gap[0x1C]; struct EngineWalkNode *next; };
struct EngineWalkOwner { unsigned char prefix[0x7C]; int value; struct EngineWalkNode *first; };
void func_00188DE0(struct EngineWalkNode *node);
void func_00187D30(struct EngineWalkOwner *owner);
void func_001862D0(struct EngineWalkOwner *owner,int value)
{
    struct EngineWalkNode *node;
    for(node=owner->first;node;node=node->next) {
        node->value=value;
        func_00188DE0(node);
    }
    owner->value=value;
    func_00187D30(owner);
}
