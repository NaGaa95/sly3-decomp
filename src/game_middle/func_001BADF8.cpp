// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Support test for an actor standing on its contacts: after the clock/stamp throttle, builds the Gram matrix of the
// (owner-flipped) contact normals, solves for weights against "down" (func_0011BA98) and reports whether the
// weighted normals cancel down well enough (z of the residual above -0.1).
#include "../P2/packed_matrix_intrinsics.h"
#include "../P2/vector_intrinsics.h"

struct ContactActor;
struct Contact {
    char prefix[8]; ContactActor *owner;
    char gap0C[0x80 - 0xC]; qword normal;
    char gap90[0xAC - 0x90]; Contact *next;
};
struct ContactGroup { Contact *first; ContactGroup *next; };
struct ContactContainer { char prefix[0x64]; ContactGroup *groups; };
struct ContactActor { char prefix[0xDC]; ContactContainer *collision; };
struct ContactClock { float time, delta; };
struct ContactRequest { int bytes, alignment; };
union ContactWorkspace { ContactRequest request; qword scalar; };
union ContactVector { qword packed; float components[4]; };
union ContactFloatWord { unsigned int bits; float value; };
extern "C" {
extern ContactClock D_0036BB98;
extern qword D_00317550;
extern float D_00323238;
int func_001BADC0(void *actor);
void *func_001D2770(void *scope);
void func_001D2798(void *scope, int flags);
void *func_001D25B0(ContactRequest *request);
void func_0011BA98(int count, float limit, float *matrix, float *rhs, float *weights);
}
struct ContactAllocationScope {
    ContactAllocationScope() { func_001D2770(this); }
    ~ContactAllocationScope() { func_001D2798(this, 2); }
};

static inline qword ContactScalar(float value)
{
    qword scalar;
    asm("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(value));
    return scalar;
}
static inline float ContactZ(qword vector)
{
    qword bits;
    float result;
    asm("qmfc2.ni %1,%2\n\tpextuw %1,$zero,%1\n\tmtc1 %1,%0"
        : "=f"(result), "=&r"(bits) : "j"(vector));
    return result;
}
static inline void ContactNormalInto(qword &normal, ContactActor *actor, Contact *contact,
                                     ContactWorkspace *workspace)
{
    normal = contact->normal;
    if (contact->owner != actor) {
        workspace->scalar = ContactScalar(-1.0f);
        asm("vmulx.xyzw %0,%0,%1x" : "+j"(normal) : "j"(workspace->scalar));
    }
}
static inline void ContactStoreDot(float *out, qword a, qword b)
{
    qword one, d;
    asm("vmul.xyz %2,%3,%4
	vaddw.x %1,$vf0,$vf0w
	vadday.x $ACC,%2,%2y
	vmaddz.x %2,%1,%2z
	qmfc2.ni %0,%2" : "=&rV"(*out), "=j"(one), "=j"(d) : "j"(a), "j"(b));
}
static inline qword ContactAddScaled(qword sum, qword normal, float weight,
                                     ContactWorkspace *workspace)
{
    workspace->scalar = ContactScalar(weight);
    qword result;
    asm("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x"
        : "=j"(result) : "j"(sum), "j"(normal), "j"(workspace->scalar));
    return result;
}

extern "C" int func_001BADF8(ContactActor *actor, float previous, float *stamp)
{
    float now = D_0036BB98.time;
    if (now - previous < 1.0f)
        return 0;
    if (stamp) {
        if (now - *stamp < 1.0f)
            return 0;
        *stamp = now;
    }
    if (func_001BADC0(actor))
        return 0;
    int count = 0;
    ContactGroup *group;
    Contact *contact;
    for (group = actor->collision->groups; group; group = group->next)
        for (contact = group->first; contact; contact = contact->next)
            ++count;
    if (!count)
        return 0;

    ContactAllocationScope scope;
    ContactWorkspace workspace;
    qword down;
    int rowBytes = count * 4;
    workspace.scalar = ContactScalar(-1.0f);
    down = ScalePackedMatrixRow(D_00317550, workspace.scalar);
    ContactRequest *request = &workspace.request;
    request->bytes = count * count * 4;
    request->alignment = 16;
    float *matrix = (float *)func_001D25B0(request);
    request->bytes = rowBytes;
    request->alignment = 16;
    float *rhs = (float *)func_001D25B0(request);
    request->bytes = rowBytes;
    request->alignment = 16;
    float *weights = (float *)func_001D25B0(request);

    ContactFloatWord *cursor = (ContactFloatWord *)matrix;
    for (group = actor->collision->groups; group; group = group->next) {
        for (contact = group->first; contact; contact = contact->next) {
            qword normal;
            ContactNormalInto(normal, actor, contact, &workspace);
            for (ContactGroup *other = actor->collision->groups; other; other = other->next) {
                Contact *second = other->first;
                if (!second)
                    continue;
                do {
                    { qword other; ContactNormalInto(other, actor, second, &workspace); ContactStoreDot((float *)cursor, normal, other); cursor++; }
                } while ((second = second->next) != 0);
            }
        }
    }
    cursor = (ContactFloatWord *)rhs;
    for (group = actor->collision->groups; group; group = group->next) {
        contact = group->first;
        if (!contact)
            continue;
        do {
            { qword n; ContactNormalInto(n, actor, contact, &workspace); ContactStoreDot((float *)cursor, n, down); cursor++; }
        } while ((contact = contact->next) != 0);
    }
    func_0011BA98(count, D_00323238, matrix, rhs, weights);
    qword sum = down;
    cursor = (ContactFloatWord *)weights;
    for (group = actor->collision->groups; group; group = group->next) {
        contact = group->first;
        if (!contact)
            continue;
        do {
            qword normal;
            ContactNormalInto(normal, actor, contact, &workspace);
            float weight = (cursor++)->value;
            contact = contact->next;
            sum = ContactAddScaled(sum, normal, weight, &workspace);
        } while (contact);
    }
    int supported = 1;
    if (-0.1f < PackedVectorZ(sum)) {
    } else {
        supported = 0;
    }
    return supported;
}
