// SLY3_CFLAGS: -Os -G0 -malign-loops=3
struct Info { char pad[0x28]; float f28; int n2C; int n30; int n34; char pad38[0x50 - 0x38]; float f50; int n54; int n58; };
struct Node { unsigned type : 8; unsigned flag : 1; unsigned first : 11; unsigned next : 11; int n4; struct Info *info; int nC; };
struct Env { char pad[0x44]; struct Node *nodes; };
struct Ctx { char pad[0x14]; struct Env *env; };
int func_002267E8(struct Ctx *, int);
void func_00226AE8(struct Ctx *, struct Info *);
float func_0022A670(struct Ctx *, struct Node *);
static inline struct Node *Get(struct Ctx *c, struct Node *n)
{
    struct Env *e = c->env;
    int i = n->next;
    return i ? &e->nodes[i] : 0;
}
struct Node *func_0022A500(struct Ctx *ctx, struct Node *node)
{
    struct Node *s;
    struct Node *found;
    int fl;
    node->info->n30 = func_002267E8(ctx, node->info->n54);
    node->info->n34 = func_002267E8(ctx, node->info->n58);
    if (node->info->f50 == 0.0f) {
        fl = 1;
        node->info->f28 = 0.0f;
    } else {
        node->info->f28 = node->info->f50;
        fl = 0;
    }
    found = 0;
    for (s = Get(ctx, node); s; s = Get(ctx, s)) {
        if (s->type == 0x45) {
            s->info->n30 = func_002267E8(ctx, s->info->n54);
            s->info->n34 = func_002267E8(ctx, s->info->n58);
            found = s;
            break;
        }
        if (s->type == 0x18) func_00226AE8(ctx, s->info);
        if (fl) node->info->f28 += func_0022A670(ctx, s);
    }
    return found;
}
