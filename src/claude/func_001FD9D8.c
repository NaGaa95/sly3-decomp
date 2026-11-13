// SLY3_CFLAGS: -Os -G0 -malign-loops=3
struct Arena { int storage[4]; };
struct Request { int bytes; int alignment; };
struct Color { unsigned char c[4]; };
struct Data { int n0; char pad[0x218 - 4]; int count; struct Color colors[1]; };
struct Owner { char pad[0x20]; struct Data *data; };
struct Desc { char pad[0x1C]; struct Owner *owner; };
struct Obj { char pad[0x20]; struct Desc *desc; };
void func_001D2770(struct Arena *);
void func_001D2798(struct Arena *, int);
struct Data *func_001D2670(struct Request *);
struct Data *func_001D24D0(struct Request *, struct Data *);
void func_001FD198(struct Obj *, void *);
void func_00236908(struct Color *);
static inline struct Request *allocation_request(struct Request *request, int bytes, int alignment)
{
    request->bytes = bytes;
    request->alignment = alignment;
    return request;
}
static inline struct Data *Alloc(int cb)
{
    struct Request request;
    request.bytes = cb;
    request.alignment = 0x10;
    return func_001D2670(&request);
}
static inline struct Data *Realloc(int cb, struct Data *p)
{
    struct Request request;
    request.bytes = cb;
    request.alignment = 0x10;
    return func_001D24D0(&request, p);
}
static inline void Swap(struct Color *a, struct Color *b)
{
    struct Color t = *a;
    *a = *b;
    *b = t;
}
void func_001FD9D8(struct Obj *obj, void *arg)
{
    struct Arena arena;
    struct Owner *owner;
    int n;
    int size;
    owner = obj->desc->owner;
    func_001D2770(&arena);
    owner->data = Alloc(0x29C);
    owner->data->n0 = -1;
    func_001FD198(obj, arg);
    size = 0x220;
    n = owner->data->count;
    if (n) {
        struct Color *colors = owner->data->colors;
        struct Color *lo, *hi;
        int i;
        size = sizeof(struct Data) + (n - 1) * sizeof(struct Color);
        for (i = 0; i < n; i++) {
            struct Color *c = &colors[i];
            int j;
            func_00236908(c);
            for (j = 0; j < 4; j++) c->c[j] = (c->c[j] + 1) >> 1;
        }
        lo = colors; hi = colors + n - 1;
        while (lo < hi) Swap(lo++, hi--);
    }
    owner->data = Realloc(size, owner->data);
    func_001D2798(&arena, 2);
}
