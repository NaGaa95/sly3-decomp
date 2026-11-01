// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
// Query the contacts of a shape against an owner's body position (up to 0x40) and report each one, last to first,
// together with its signed distance to the contact plane. Same routine as Sly 2 func_001A9B28.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } ReportScalar;
struct ReportBody { unsigned char prefix[0x70]; qword position; };
struct ReportOwner { struct ReportBody *body; int word4; float radius; };
struct ReportContact { qword point; qword plane; int kind; int id; int pad[2]; };
int func_001CD098(qword position, void *shape, int mask, int count, void *triangles,
                  int capacity, struct ReportContact *contacts, float radius);
void func_002BA000(void *scalar);
void func_001CB8B0(void *world, void *owner, void *shape, qword point, qword plane,
                   int kind, int unused, int id, float distance, int extra);

// dot(point.xyz, plane.xyz) - plane.w; the VU result and its helper lane are kept in the two scalar slots.
static inline float PlaneDistance(qword plane, qword point, ReportScalar *distance, ReportScalar *one)
{
    qword td, tone;
    float result;
    func_002BA000(distance);
    func_002BA000(one);
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %2w"
            : "=&j"(td), "=&j"(tone) : "j"(plane), "j"(point));
    // allocation-only alternatives: the float readback keeps td in its VU register (same trick as func_00167588)
    __asm__("mtc1 %1, %0" : "=f,f"(result) : "r,j"(td), "i,r"(0));
    one->q = tone;
    distance->q = td;
    return result;
}

void func_001CD858(void *world, struct ReportOwner *owner, void *shape, int count,
                   void *triangles, int extra)
{
    struct ReportContact contacts[0x40];
    int found = func_001CD098(owner->body->position, shape, 0x7FFFFFFF, count, triangles,
                              0x40, contacts, owner->radius);
    int i;
    for (i = found - 1; i >= 0; --i) {
        struct ReportContact *contact = &contacts[i];
        ReportScalar distance, one;
        qword point = contact->point;
        qword plane = contact->plane;
        float d = PlaneDistance(plane, point, &distance, &one);
        func_001CB8B0(world, owner, shape, point, plane, contact->kind, 0, contact->id, d, extra);
    }
}
