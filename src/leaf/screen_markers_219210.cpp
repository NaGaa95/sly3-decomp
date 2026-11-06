// Place the screen overlay sprites of a panel: first a rotated 2x3 transform (heading of the panel's own
// object, translated to its projected position) for the main marker, then one translated identity transform per
// found marker object (at most three), publishing each object's linked id in the control's slot table.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
// 3x3 rotation returned in three qwords; the float view reads the entries of the 2x3 part.
struct M3 { union { qword r[3]; float f[12]; }; };
struct Vec4 { float x, y, z, w; } __attribute__((aligned(16)));
// 2x3 affine transform (a b c d tx ty), padded to 32 bytes.
struct Transform { float a[8]; } __attribute__((aligned(16)));
struct Method { short delta, pad; void *(*call)(void *); };
struct Info { char pad[0x60]; int id; };
struct Link { char pad[0x6C]; Info *info; };
struct Obj { char pad0[0xC]; Method *vt; char pad10[0x140 - 0x10]; Link *link; };
struct Control { char pad[0xBC]; int slot[1]; };
struct Panel { char pad0[0xC]; Method *vt; char pad10[0x448 - 0x10]; Control *control; };
struct Game;
extern "C" {
extern Game D_00475480;
extern qword D_00317550;
extern int D_00325CD8[];
float func_002A3EE8(float y, float x);                              // atan2f
M3 func_0011C8C0(float angle, qword axis);                          // rotation about an axis
Vec4 func_00219120(Panel *self, qword position);                    // world position to screen
void func_00262990(Control *control, int key, Transform *data);     // send a transform record
void func_00262450(Control *control, int key);
int func_0017E208(Game *game, int a, int b, int c, int n, Obj **out);   // collect objects by kind
void *func_00292034(void *dest, int value, int bytes);              // memset
}
// Virtual slot 36 returns the object's matrix (rows of four floats; row 3 is the position).
#define MATRIX(o) ((qword *)(o)->vt[36].call((char *)(o) + (o)->vt[36].delta))
static inline float Heading(Panel *self)
{
    float *m = (float *)MATRIX(self);
    return func_002A3EE8(m[1], m[0]);
}
extern "C" void func_00219210(Panel *self)
{
    Transform t;
    Vec4 screen;
    {
        M3 rot = func_0011C8C0(-Heading(self), D_00317550);
        t.a[0] = rot.f[0];
        t.a[1] = rot.f[1];
        t.a[2] = rot.f[4];
        t.a[3] = rot.f[5];
        t.a[4] = rot.f[8];
        t.a[5] = rot.f[9];
    }
    screen = func_00219120(self, MATRIX(self)[3]);
    t.a[4] = screen.x;
    t.a[5] = screen.y;
    func_00262990(self->control, 0x3EB, &t);
    {
        Obj *list[3];
        int n = func_0017E208(&D_00475480, 0x105, 0x78, 0, 3, list);
        func_00292034(&t, 0, 0x20);
        t.a[3] = 1.0f;
        t.a[0] = 1.0f;
        for (int i = 0; i < n; i++) {
            Obj *o = list[i];
            screen = func_00219120(self, MATRIX(o)[3]);
            int key = D_00325CD8[i];
            t.a[4] = screen.x;
            t.a[5] = screen.y;
            func_00262450(self->control, key);
            func_00262990(self->control, key, &t);
            int id = -1;
            if (o->link && o->link->info) {
                int v = o->link->info->id;
                if (v != -1) id = v;
            }
            self->control->slot[i] = id;
        }
    }
}
