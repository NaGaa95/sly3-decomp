// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Triangle { int first,second,third; };
struct Mesh { unsigned char prefix[0xC]; struct Triangle *triangles; };
struct Surface { unsigned char data[0x20]; };
struct Body {
    unsigned char prefix[0x14];
    struct Mesh *mesh;
    unsigned char gap18[0x74];
    qword *positions;
    int count;
    struct Surface *surfaces;
};
void func_00119E20(void *surface,qword first,qword second,qword third);
void func_00240538(struct Body *body)
{
    int i;
    struct Triangle *triangles;
    qword *positions;
    struct Surface *surfaces;
    triangles=body->mesh->triangles;
    surfaces=body->surfaces;
    positions=body->positions;
    for(i=0;i<body->count;i++) {
        struct Triangle *triangle=&triangles[i];
        func_00119E20(&surfaces[i],positions[triangle->first],positions[triangle->second],positions[triangle->third]);
    }
}
