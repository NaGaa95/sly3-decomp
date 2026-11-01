// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Rotation (quaternion) and position of `stop` relative to the owner's two end nodes of p->link (same routine as Sly 2
// func_001B72B0).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } U;
typedef struct { U row[3]; } M3;
typedef struct { M3 basis; U position; } M4;
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } operator qword() const { return q; } };
typedef struct NODE { M4 local, world; char pad80[0x20]; struct NODE *parent; } NODE;
typedef struct { char pad[0x48]; NODE *left, *right; } OWNER;
typedef struct { char pad[0x40]; NODE *first; char pad44[0xC]; M4 transform; } POSE;
typedef struct { char pad[0x190]; OWNER *owner; int pad194; POSE *pose; } LINK;
typedef struct { char pad[0x1540]; LINK *link; } P;
extern "C" M4 D_003174C0;   // identity matrix
extern "C" M3 func_0028EA00(NODE *, NODE *, const M3 &);
extern "C" M4 func_0028EC08(NODE *, NODE *, const M4 &);
extern "C" VU_VECTOR func_0028E910(NODE *, NODE *, VU_VECTOR);
extern "C" VU_VECTOR func_0011D3C0(const M3 *);
extern "C" void func_0011C9E8(M3 *, VU_VECTOR);
extern "C" qword *func_002BA818(qword *, VU_VECTOR);
extern "C" void func_0011D768(M4 *, const M4 *);
extern "C" M4 func_0011D558(const M4 &, const M4 &);

extern "C" void func_001DFAD8(P *const p, NODE *stop, const M4 *input, VU_VECTOR *outRotation, VU_VECTOR *outPosition)
{
    if (!p->link->pose) {
        M3 basis;
        basis = func_0028EA00(stop, p->link->owner->right->parent, input->basis);
        *outRotation = func_0011D3C0(&basis);
        *outPosition = func_0028E910(stop, p->link->owner->left->parent, input->position.q);
        return;
    }
    {
        NODE *chain[16];
        U rotation, finalPosition;

        OWNER *owner = p->link->owner;
        NODE *node;
        int count = 0, left = -1, right = -1, j;
        M4 inverse;
        func_0011D768(&inverse, input);
        for (node = p->link->pose->first; node != stop; node = node->parent) {
            chain[count] = node;
            if (node == owner->left) left = count;
            if (node == owner->right) right = count;
            count++;
        }
        M4 from = func_0028EC08(p->link->pose->first, owner->right, D_003174C0);
        M4 to = func_0028EC08(owner->right->parent, stop, D_003174C0);
        from = func_0011D558(from, p->link->pose->transform);
        M4 replace;
        M4 result = func_0011D558(func_0011D558(from, inverse), to);
        func_0011D768(&replace, &result);
        rotation.q = func_0011D3C0(&replace.basis);
        func_0011C9E8(&result.basis, rotation.q);
        func_002BA818(&replace.position.q, chain[right]->local.position.q);
        M4 *pmat = &replace;
        pmat->basis = result.basis;
        replace.basis.row[0].i[3] = replace.basis.row[1].i[3] = replace.basis.row[2].i[3] = 0;
        pmat->position.f[3] = 1.0f;
        result = D_003174C0;
        M4 upper = D_003174C0;
        for (int i = count - 1; i > left; i--) {
            if (i == right) result = func_0011D558(result, replace);
            else result = func_0011D558(result, chain[i]->local);
        }
        for (j = left - 1; j >= 0; j--) {
            if (j == right) upper = func_0011D558(upper, replace);
            else upper = func_0011D558(upper, chain[j]->local);
        }
        upper = func_0011D558(upper, p->link->pose->transform);
        M4 product;
        M4 intermediate = func_0011D558(func_0011D558(upper, inverse), result);
        func_0011D768(&product, &intermediate);
        finalPosition = product.position;
        if (outRotation) *outRotation = rotation.q;
        if (outPosition) *outPosition = finalPosition.q;
    }
}
