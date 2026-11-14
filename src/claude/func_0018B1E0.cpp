// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Refresh the world-space copy of a shape's geometry: points are transformed by the owner's world matrix and the
// plane normals by the inverse transpose of its rotation (VU0 microprogram at 0x150). Sly 2 counterpart:
// func_001664A0 (TransformGeom-style routine with explicit matrix/source/destination arguments).
typedef int qword __attribute__((mode(TI)));
struct MATRIX3 { qword r[3]; };
struct MATRIX4 { qword r[4]; };
struct PLANE { qword normal; int unknown10, unknown14, unknown18; int vertex; };
struct GEOMETRY { int pointCount; qword *points; int planeCount; PLANE *planes; };
struct Frame {
    char pad0[0x40];
    MATRIX4 matWorld;
    char pad80[0x24];
    int generation;
};
struct Shape {
    Frame *frame;
    char pad4[0x84];
    GEOMETRY local;
    char pad98[0x8];
    GEOMETRY world;
    char padB0[0x10];
    int generation;
};
extern "C" void func_0018B168(const MATRIX4 *, unsigned int, const qword *, qword *);
extern "C" MATRIX3 func_0011C6F8(const MATRIX3 *);

// MMI 3x3 transpose (engine inline).
static inline MATRIX3 Transpose(const MATRIX3 &mat) return matT
{
    qword xy, zw, cx, cz;
    __asm__("pextlw %0,%5,%4\n\tpextuw %1,%5,%4\n\tpextlw %2,$zero,%6\n\tpextuw %3,$zero,%6"
            : "=&r"(xy), "=&r"(zw), "=&r"(cx), "=r"(cz) : "r"(mat.r[0]), "r"(mat.r[1]), "r"(mat.r[2]));
    __asm__("pcpyld %0,%4,%3\n\tpcpyud %1,%3,%4\n\tpcpyld %2,%6,%5"
            : "=&r"(matT.r[0]), "=&r"(matT.r[1]), "=r"(matT.r[2]) : "r"(xy), "r"(cx), "r"(zw), "r"(cz));
}

extern "C" void func_0018B1E0(Shape *shape)
{
    shape->generation = shape->frame->generation;
    if (shape->local.points == shape->world.points)
        return;

    func_0018B168(&shape->frame->matWorld, shape->local.pointCount, shape->local.points, shape->world.points);
    MATRIX3 matNormal;
    matNormal = Transpose(func_0011C6F8((const MATRIX3 *)&shape->frame->matWorld));
    int planeCount = shape->local.planeCount;
    if (planeCount > 0) {
        const PLANE *input = shape->local.planes;
        PLANE *output = shape->world.planes;
        const PLANE *last = output + planeCount - 1;
        // The VU microprogram takes the matrix rows in vf1-vf3, the plane's vertex in vf4 and the plane in vf5.
        register qword row0 __asm__("vf1") = matNormal.r[0];
        register qword row1 __asm__("vf2") = matNormal.r[1];
        register qword row2 __asm__("vf3") = matNormal.r[2];
        register qword anchor __asm__("vf4") = shape->world.points[input->vertex];
        register qword plane __asm__("vf5") = input->normal;
        qword nextAnchor, nextPlane;
        ++input;
        for (;;) {
            __asm__ __volatile__("vcallms 0x150" : : "j"(row0), "j"(row1), "j"(row2), "j"(anchor), "j"(plane));
            if (output < last) {
                nextPlane = input->normal;
                nextAnchor = shape->world.points[input->vertex];
                ++input;
            }
            {
                int sync;
                register qword result __asm__("vf5");
                __asm__ __volatile__("cfc2.i %0,$vi0" : "=r"(sync), "=j"(result));
                output->normal = result;
            }
            if (output == last)
                break;
            anchor = nextAnchor;
            ++output;
            plane = nextPlane;
        }
    }
}
