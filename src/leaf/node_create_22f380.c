// SLY3_CFLAGS: -Os -G0
// Create a path-sample node: curve position/direction at the parameter, plus arc length, parameter and owner.
struct Node { unsigned char prefix[0x20]; unsigned char position[0x10]; unsigned char direction[0x10]; float length; float parameter; void *owner; unsigned char gap4C[4]; };
void *func_001C9A50(unsigned int bytes);
void *func_002BF168(void *object);
void func_0022E148(void *owner, float parameter, void *position, void *direction);
float func_0022DD48(void *owner, float parameter);
struct Node *func_0022F380(void *owner, float parameter)
{
    struct Node *node = func_002BF168(func_001C9A50(0x50));
    func_0022E148(owner, parameter, node->position, node->direction);
    node->parameter = parameter;
    node->length = func_0022DD48(owner, parameter);
    node->owner = owner;
    return node;
}
