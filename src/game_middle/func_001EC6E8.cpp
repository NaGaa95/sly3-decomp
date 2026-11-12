// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001EC6E8: build a walking path from `from` to `to`: route over the navigation graph (func_001EC300, up to 16
// points), then append the points to path->apos one by one; when a segment hits an obstacle object (func_001E7500),
// project the entry/exit points onto the object's outline (func_0022EA88) and walk its outline points (transformed
// by the object's matrix) in the direction chosen by func_001E6ED0 (1 = backwards, 2 = forwards, 4 = give up).
// Finally store the point count and rebuild the segment data (func_001EF608).
// Matching notes: the frame comes from block-scoped temps (hitExit's freed BLKmode slot is reused by aposPath and the
// matrix copy); FFull returns the comparison as a value (sltu/xori/bnez); the push after the obstacle path and the
// plain push each test FFull themselves (cross-jumping merges the tails); apos[i++] gives the separate pointer copy;
// case 1 copies jFirst into the loop counter (orders the counter copy after the second call's arguments).
typedef int qword __attribute__((mode(TI)));
struct LSG {
    qword apos[2];
    qword anormal[2];
    float au[2];
    char pad[0x60 - 0x48];
};
struct M4 { qword r[4]; };
struct VTE { short delta, pad; void *fn; };
struct OBJ { char pad0[0xC]; VTE *vt; char pad10[0xE4 - 0x10]; qword *apos; };
struct PATH { char pad0[0x30]; int cpos; int pad34[3]; qword apos[16]; };
extern "C" {
extern char D_00474FD0[];
int func_001EC300(void *, qword, qword, int, qword *);
OBJ *func_001E7500(void *, void *, qword, qword);
int func_001E6830(OBJ *, qword, qword, int, LSG *);
void func_0022EA88(OBJ *, qword, void *, qword *, int, int, float *);
qword *func_001EC6D8(qword *, qword);
int func_001E6ED0(OBJ *, void *, float *, int, float);
int func_0022F198(OBJ *, float, float *, float *);
int func_001E66D8(OBJ *, int);
void func_001EF608(PATH *);
}
static inline M4 *Matrix(OBJ *o) { VTE *e = &o->vt[36]; return ((M4 *(*)(void *))e->fn)((char *)o + e->delta); }
static inline int FFull(qword *c, qword *e) { return c >= e; }
static inline qword MulPoint(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}

extern "C" int func_001EC6E8(void *world, qword from, qword to, PATH *path)
{
    qword apos[16];
    int cpos = func_001EC300((char *)world + 0xD0, from, to, 16, apos);
    if (cpos < 2)
        return 0;
    int i = 1;
    qword *start = path->apos;
    qword *end = &path->apos[15];
    path->apos[0] = apos[0];
    qword *cursor = start;
    while (i < cpos) {
        qword posCur = *cursor;
        OBJ *obj = func_001E7500(world, 0, posCur, apos[i]);
        if (!obj) {
            cursor = func_001EC6D8(cursor, apos[i++]);
            if (FFull(cursor, end))
                goto done;
        } else {
            LSG hitEnter;
            qword posEnter;
            if (func_001E6830(obj, posCur, apos[i], 1, &hitEnter) != 1 || hitEnter.au[0] != 0.0f)
                posEnter = posCur;
            else
                posEnter = hitEnter.apos[1];
            qword posPrev = posEnter;
            qword posExit;
            while (i < cpos) {
                LSG hitExit;
                if (!func_001E6830(obj, posPrev, apos[i], 1, &hitExit)) {
                    posPrev = apos[i];
                    i++;
                } else {
                    if (hitExit.au[0] > 0.0f || (hitExit.au[0] == 0.0f && hitExit.au[1] == 1.0f))
                        posExit = hitExit.apos[0];
                    else
                        posExit = hitExit.apos[1];
                    break;
                }
            }
            if (i >= cpos)
                posExit = posPrev;
            qword aposPath[2];
            float tEnter, tExit;
            func_0022EA88(obj, posEnter, D_00474FD0, &aposPath[0], 0, 0, &tEnter);
            func_0022EA88(obj, posExit, D_00474FD0, &aposPath[1], 0, 0, &tExit);
            cursor = func_001EC6D8(cursor, aposPath[0]);
            if (FFull(cursor, end))
                goto done;
            switch (func_001E6ED0(obj, world, &tExit, -1, tEnter)) {
            case 1: {
                M4 mat = *Matrix(obj);
                int jFirst = func_0022F198(obj, tEnter, 0, 0);
                int jEnd = func_0022F198(obj, tExit, 0, 0);
                for (int j = jFirst; j != jEnd; j = func_001E66D8(obj, j - 1)) {
                    cursor = func_001EC6D8(cursor, MulPoint(mat, obj->apos[j]));
                    if (FFull(cursor, end))
                        goto done;
                }
                break;
            }
            case 2: {
                M4 mat = *Matrix(obj);
                int j = func_001E66D8(obj, func_0022F198(obj, tEnter, 0, 0) + 1);
                int jEnd = func_001E66D8(obj, func_0022F198(obj, tExit, 0, 0) + 1);
                for (; j != jEnd; j = func_001E66D8(obj, j + 1)) {
                    cursor = func_001EC6D8(cursor, MulPoint(mat, obj->apos[j]));
                    if (FFull(cursor, end))
                        goto done;
                }
                break;
            }
            case 4:
                return 1;
            }
            cursor = func_001EC6D8(cursor, aposPath[1]);
            if (FFull(cursor, end))
                goto done;
        }
    }
done:
    path->cpos = cursor - start + 1;
    func_001EF608(path);
    return 1;
}
