// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "bis.h"
#include "heap.h"

struct MESH_TRIANGLE {
    int indices[3];
    float weight;
};
struct MESH_DATA {
    int vertex_count;
    qword *positions;
    int triangle_count;
    MESH_TRIANGLE *triangles;
    qword *normals;
    float total_weight;
    unsigned char reserved18[8];
    qword axis;
    unsigned char reserved30[0x18];
    int format;
};
struct MESH_RECORD {
    unsigned char reserved00[0x10];
    MESH_DATA *mesh;
};
typedef unsigned int UQ __attribute__((mode(TI)));
extern "C" {
void *func_001D2470(ALLOCREQ *);
void *func_001D2538(ALLOCREQ *);
extern const UQ D_00317550;
}

static inline ALLOCREQ *MeshRequest(ALLOCREQ *request, int bytes)
{
    request->cb = bytes;
    request->cbAlign = 16;
    return request;
}

// These hardware primitives leave vector/GPR allocation to the compiler.
static inline qword Subtract(qword a, qword b)
{
    qword result;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(result) : "j"(a), "j"(b));
    return result;
}
static inline qword Add(qword a, qword b)
{
    qword result;
    __asm__("vadd.xyzw %0,%1,%2" : "=j"(result) : "j"(a), "j"(b));
    return result;
}
static inline qword Cross(qword a, qword b)
{
    // XYZ changes; the original packed accumulation also uses input a's W.
    __asm__("vopmula.xyz $ACC,%0,%1\n\tvopmsub.xyz %0,%1,%0"
            : "+j"(a) : "j"(b));
    return a;
}
static inline qword Dot3(qword value)
{
    qword product, one;
    __asm__("vmul.xyz %0,%2,%2\n\t"
            "vaddw.x %1,$vf0,$vf0w\n\t"
            "vadday.x $ACC,%0,%0y\n\t"
            "vmaddz.x %0,%1,%0z"
            : "=j"(product), "=&j"(one) : "j"(value));
    return product;
}
static inline qword SqrtX(qword value)
{
    qword result;
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q"
            : "=j"(result) : "j"(value));
    return result;
}
static inline float XFloat(qword value)
{
    float result;
    __asm__("qmfc2.ni %0,%1" : "=r"(result) : "j"(value));
    return result;
}
static inline qword DivideByX(qword value, qword divisor)
{
    qword result;
    __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q"
            : "=j"(result) : "j"(divisor), "j"(value));
    return result;
}
static inline void Normalize(qword *destination, qword fallback)
{
    qword value = *destination;
    qword result = SqrtX(Dot3(value));
    if (XFloat(result) < 0.0001f)
        result = fallback;
    else
        result = DivideByX(value, result);
    *destination = result;
}

extern "C" void func_001FCF10(void *receiver, void *input)
{
    MESH_DATA *mesh = ((MESH_RECORD *)receiver)->mesh;
    CBinaryInputStream *stream = (CBinaryInputStream *)input;
    if (mesh->format != 3)
        return;

    ALLOCREQ request;
    mesh->vertex_count = stream->U16Read();
    mesh->positions = (qword *)func_001D2470(
        MeshRequest(&request, mesh->vertex_count * (int)sizeof(qword)));
    mesh->normals = (qword *)func_001D2538(
        MeshRequest(&request, mesh->vertex_count * (int)sizeof(qword)));
    for (int vertex = 0; vertex < mesh->vertex_count; ++vertex)
        stream->ReadVector((VECTOR *)&mesh->positions[vertex]);

    mesh->triangle_count = stream->U16Read();
    mesh->triangles = (MESH_TRIANGLE *)func_001D2470(
        MeshRequest(&request, mesh->triangle_count * (int)sizeof(MESH_TRIANGLE)));
    mesh->total_weight = 0;
    for (int face = 0; face < mesh->triangle_count; ++face) {
        MESH_TRIANGLE *triangle = &mesh->triangles[face];
        for (int input_corner = 0; input_corner < 3; ++input_corner)
            triangle->indices[input_corner] = stream->U16Read();
        triangle->weight = stream->F32Read();
        mesh->total_weight += triangle->weight;
        qword origin = mesh->positions[triangle->indices[0]];
        qword edge1 = Subtract(mesh->positions[triangle->indices[1]], origin);
        qword edge2 = Subtract(mesh->positions[triangle->indices[2]], origin);
        qword normal = Cross(edge1, edge2);
        for (int output_corner = 0; output_corner < 3; ++output_corner) {
            qword *destination = &mesh->normals[triangle->indices[output_corner]];
            *destination = Add(*destination, normal);
        }
    }
    stream->ReadVector((VECTOR *)&mesh->axis);
    for (int normal = 0; normal < mesh->vertex_count; ++normal)
        Normalize(&mesh->normals[normal], (qword)D_00317550);
}
