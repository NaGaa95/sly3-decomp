// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Per-frame update of the topmost menu group: run its item updaters, then advance the menu state machine (open/close
// transitions, input handling, navigation); same routine as Sly 2 func_001AEEE0.
struct POOL;
struct VTE { short delta, pad; void (*fn)(POOL *); };
struct POOL { char pad[0xC]; VTE *vt; };
struct ITEM { int kind; void (*select)(ITEM *); char pad8[8]; void (*update)(ITEM *); char pad14[8]; unsigned flags; };
struct META { char pad[0xC]; int ready, pad10, back, forward, reverse; };
struct GROUP { int count; ITEM *items; POOL *pool; int back; int pad10, index; META *meta; };
struct INPUT;
struct P { char pad[0x1C]; INPUT *input; char pad20[0x18]; int depth; char pad3C[0x1C0]; int state, pending; char nav[1]; };
struct CONTEXT { char bytes[0x6864]; };
struct BANK { char pad[0x24]; CONTEXT contexts[3]; char pad2[8]; CONTEXT *current; };
struct OPT;
struct MENU;
extern "C" void *func_001291A8(void *, const void *);
extern "C" void func_0012BC20(void *);
struct CRef {
    int tag;
    union { int n; float f; };
    CRef(const CRef &r) { func_001291A8(this, &r); }
    ~CRef() { func_0012BC20(this); }
};
extern "C" {
void func_0021DD20();
int func_00260758(POOL *, int);
void func_00262280(POOL *, int);
void func_001D2ED0(P *, int);
int func_001A9C38(void *);
int func_001A7A80(INPUT *, unsigned, float);
int func_001A7AE0(INPUT *, int, int);
int func_0025E150();
void func_001D3918(P *);
void func_001D3A90(P *);
void func_001D3AE8(P *);
void func_001D4498(P *, ITEM *);
void func_001D3FC0(P *, ITEM *);
void func_001D3B58(P *, GROUP *, ITEM *);
int func_001D45B0(P *);
CRef func_002BC010(OPT *, CONTEXT *);
void func_001D0C08(MENU *, int);
extern OPT *D_004794EC;
extern CONTEXT D_003752B4[];
extern MENU D_003751D0;
extern ITEM D_00388D28[];
}
static inline float Value(OPT *key, CONTEXT *context) { CRef result = func_002BC010(key, context); return result.f; }
static inline void Select(CONTEXT *contexts, CONTEXT *context) { BANK *bank = (BANK *)((char *)contexts - 0x24); bank->current = context; }
extern "C" void func_001D3288(P *p)
{
    int direction;
    int flags;
    func_0021DD20();
    if (p->depth <= 0)
        return;
    GROUP *group = (GROUP *)((char *)p + 0x20 + p->depth * sizeof(GROUP));
    int i;
    for (i = 0; i < group->count; i++) {
        ITEM *item = &group->items[i];
        if (item->update)
            item->update(item);
    }
    switch (p->state) {
    case 0:
        break;
    case 1:
        if (func_00260758(group->pool, 0x37B))
            break;
        if (p->pending != -1) {
            p->depth = p->pending;
            p->pending = -1;
        }
        goto resumed;
    case 2:
        if (func_00260758(group->pool, 0x37B))
            break;
        if (p->pending != -1)
            p->pending = -1;
        else
            p->depth--;
        if (p->depth == 0)
            goto close;
        goto resumed;
    case 3:
        if (func_00260758(group->pool, group->meta->back))
            break;
        p->depth = p->pending;
        p->pending = -1;
        func_001D2ED0(p, 4);
        break;
    case 4:
        if (func_00260758(group->pool, group->meta->ready))
            break;
        goto resumed;
    case 8: {
        if (func_00260758(group->pool, 0x37B))
            break;
    close:
        POOL *pool = group->pool;
        VTE *method = &pool->vt[54];
        method->fn((POOL *)((char *)pool + method->delta));
        func_001D2ED0(p, 0);
        break;
    }
    case 5:
        if (func_00260758(group->pool, group->meta->forward))
            break;
    activate:
        func_001D2ED0(p, 7);
        direction = func_001A9C38(p->nav);
        if (direction < 0)
            goto up;
        goto positive;
    case 6:
        if (func_00260758(group->pool, group->meta->reverse))
            break;
        goto activate;
    case 7: {
        if (!p->input)
            break;
        flags = func_001A7A80(p->input, 0x870, 0.0f);
        if (!flags)
            flags = func_001A7AE0(p->input, 0x100, 8) ? 0x800 : 0;
        if (func_0025E150() == 1 && p->depth == 1 && group->items == D_00388D28)
            flags &= ~0x810;
        if (flags & 0x800) {
            func_001D3AE8(p);
            break;
        }
        if ((flags & 0x10) || (group->count == 0 && flags)) {
            if (group->back)
                func_001D3918(p);
            else
                func_001D3A90(p);
            break;
        }
        if (p->depth > 0 && (flags & 0x40)) {
            ITEM *item = &group->items[group->index];
            if (item->select)
                item->select(item);
            if (item->flags & 2)
                break;
            if (item->flags & 1)
                goto back;
            func_001D3AE8(p);
            break;
        back:
            if (group->back)
                func_001D3918(p);
            else
                func_001D3A90(p);
            break;
        }
        if (flags & 0x20) {
            int kind = func_001D45B0(p);
            if (kind != 0x25 && kind != 0x2A)
                break;
            CONTEXT *contexts = D_003752B4;
            CONTEXT *context = contexts + group->index;
            if (Value(D_004794EC, context) == 0.0f)
                break;
            Select(contexts, context);
            func_001D0C08(&D_003751D0, 0x2D);
            break;
        }
        if (!group)
            break;
        {
            direction = func_001A9C38(p->nav);
            if (direction >= 0)
                goto positive;
        up:
            func_001D2ED0(p, 6);
            break;
        positive:
            if (direction <= 0)
                break;
            func_001D2ED0(p, 5);
            break;
        }
    }
    case 11:
        if (func_00260758(group->pool, 0x3B7))
            break;
        func_001D2ED0(p, 10);
        break;
    case 9:
        if (func_00260758(group->pool, 0x3B8))
            break;
        func_00262280(group->pool, 0x3B8);
    resumed:
        func_001D2ED0(p, 7);
        break;
    case 10: {
        if (!p->input)
            break;
        ITEM *item = &group->items[group->index];
        flags = func_001A7A80(p->input, 0x850, 0.0f);
        if (!flags)
            flags = func_001A7AE0(p->input, 0x100, 8) ? 0x800 : 0;
        if (func_0025E150() == 1 && p->depth == 1 && group->items == D_00388D28)
            flags &= ~0x810;
        if (flags & 0x800) {
            func_001D4498(p, item);
            func_001D3AE8(p);
            break;
        }
        if (flags & 0x10)
            func_001D4498(p, item);
        else if (flags & 0x40)
            func_001D3FC0(p, item);
        else
            func_001D3B58(p, group, item);
        break;
    }
    default:
        break;
    }
}
