// Reference algorithm: src/hand/func_001AA020.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct E { union { qword q[12]; struct { char pad[0xAC]; struct E *next; } s; } u; } E;
struct S { char pad[0x44DC]; char pool[1]; };
E *func_0011E118(void *pool);
E *func_001CDD78(struct S *s, E *src)
{
    E *head;
    E **pp;
    if (!src)
        return 0;
    head = 0;
    pp = &head;
    do {
        E *n = func_0011E118(s->pool);
        *n = *src;
        *pp = n;
        src = src->u.s.next;
        pp = &n->u.s.next;
    } while (src);
    return head;
}
