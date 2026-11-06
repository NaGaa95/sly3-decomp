// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Resolve an entry's target object (cf. Sly 2 src/hand/func_00209130.c).
struct E { int kind; void *value; int n8, nC; };
extern char D_00475480[];
void func_00259330(void *, void *);
void *func_0017E1B8(void *, int, int, void *);
int func_0013B868(void *);
void *func_00136880(void *, int);
void *func_002576C8(void *, void *);
void func_00253AA8(void *);
void func_00254C00(struct E *e, void *context)
{
    int kind = e->kind;
    if (kind != -1) {
        if (kind == 3)
            func_00259330(e->value, context);
    } else {
        void *resource = func_0017E1B8(D_00475480, 4, (int)e->value, context);
        if (!resource) {
            e->kind = -1;
            return;
        }
        switch (func_0013B868(resource)) {
        case 0x82:
            if (func_00136880(resource, 0x3D)) {
                e->kind = 2;
                e->value = func_002576C8(context, resource);
                if (e->nC == -1)
                    e->nC = 0;
            } else {
                e->value = resource;
                e->kind = 0;
            }
            break;
        case 0x95:
            e->kind = 2;
            e->value = resource;
            if (e->nC == -1)
                e->nC = 0;
            break;
        case 0x84:
            e->kind = 1;
            e->value = resource;
            if (e->nC == -1)
                e->nC = 0;
            break;
        default:
            e->kind = -1;
            break;
        }
    }
    func_00253AA8(context);
}
