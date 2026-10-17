// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct ContactPart {
    void *shape;
    unsigned char gap4[8];
    void *object;
    unsigned char rest[0x30];
};
typedef struct ContactNode {
    union {
        qword q[12];
        struct {
            struct ContactPart part[2];
            unsigned char gap80[0xAC - 0x80];
            struct ContactNode *next;
        } s;
    } u;
} ContactNode;
struct ContactWorld { char pad[0x44DC]; char pool[1]; };
struct ContactOwner { unsigned char prefix[0x6C]; ContactNode *head; };
struct ContactShape { unsigned char prefix[0x1C]; int key; };
struct QueryMethod {
    short adjustment, word2;
    void (*function)(void *self, struct ContactShape *shape, int a, int b, int c, ContactNode **out);
};
struct QueryTable { unsigned char prefix[0x1F8]; struct QueryMethod query; };
struct QueryObject { unsigned char prefix[0xC]; struct QueryTable *methods; };
struct QueryHolder { unsigned char prefix[0x60]; struct QueryObject *object; };
ContactNode *func_0011E118(void *pool);
int func_00240E10(void *object, int key);
void func_001CDD30(struct ContactWorld *world, ContactNode *chain, ContactNode **head);

void func_001CDE08(struct ContactWorld *world, struct QueryHolder *holder,
                   struct ContactOwner *owner, struct ContactShape *shape,
                   int a, int b, int c, ContactNode **out)
{
    ContactNode *chain = 0;
    struct QueryObject *object = holder->object;
    struct QueryMethod *method = &object->methods->query;
    method->function((char *)object + method->adjustment, shape, a, b, c,
                     shape->key ? &chain : out);
    if (chain) {
        ContactNode *node = chain;
        do {
            int side = node->u.s.part[0].shape == shape;
            struct ContactPart *other = &node->u.s.part[side];
            if (func_00240E10(other->object, shape->key)) {
                ContactNode *copy = func_0011E118(world->pool);
                *copy = *node;
                copy->u.s.next = owner->head;
                owner->head = copy;
            }
            node = node->u.s.next;
        } while (node);
        func_001CDD30(world, chain, out);
    }
}
