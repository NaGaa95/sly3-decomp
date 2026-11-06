// SLY3_CFLAGS: -Os -G0
// Clone fixup: remap a node pointer from the source pool into the destination pool and rebase its self-links
// (the second test stores to +0x88 again, as in the original).
struct Node { char p[0x80]; void *a; void *b; struct Node *n88; void *n8C; char q[0x100 - 0x90]; };
struct Pool { char p[0x40]; int count; struct Node *nodes; };
struct Owner { char p[0x10]; struct Pool *pool; };
void func_0028FE90(struct Owner *dst, struct Owner *src, struct Node **pp)
{
    struct Node *p = *pp;
    if (p) {
        struct Node *q = 0;
        int i = p - src->pool->nodes;
        if (i >= 0 && i < src->pool->count)
            q = dst->pool->nodes + i;
        if (q->n88 == (struct Node *)&p->a)
            q->n88 = (struct Node *)&q->a;
        if (q->n8C == &p->b)
            q->n88 = (struct Node *)&q->b;
        *pp = q;
    }
}
