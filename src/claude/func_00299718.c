// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int x0[4]; int idx; int val; } CMDA;
typedef struct { int x0[2]; int x8; int xc[4]; int *tbl; } CMDB;
void func_00299718(CMDA *a, CMDB *b)
{
    b->tbl[a->idx] = a->val;
}

void func_00299738(CMDA *a, CMDB *b)
{
    b->x8 = a->idx;
}
