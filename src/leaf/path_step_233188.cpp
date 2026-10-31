// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Path step: sample the start/finish vectors and the motion rows for this frame, push them through the object's virtual
// setters, then count the remaining path time down (never below zero).
typedef int qword __attribute__((mode(TI)));
struct Rows { qword row[3]; };
struct Entry { short delta, pad; union { void (*Quad)(void *, qword); void (*Matrix)(void *, Rows *); }; };
struct Path { unsigned char prefix[0xC]; Entry *vtable; unsigned char gap10[0x17C - 0x10]; float end; };
extern float D_0036BB9C;
extern "C" {
void func_00233280(Path *path, qword *start, qword *finish, float time);
void func_00233360(Path *path, Rows *rows, qword *output, float time, float first, float second);
}
extern "C" void func_00233188(Path *self, float first, float second)
{
    qword start[1], finish[1];
    Rows rows;
    qword output[1];
    float step = D_0036BB9C;
    func_00233280(self, start, finish, step);
    self->vtable[34].Quad((char *)self + self->vtable[34].delta, start[0]);
    self->vtable[40].Quad((char *)self + self->vtable[40].delta, finish[0]);
    func_00233360(self, &rows, output, step, first, second);
    self->vtable[35].Matrix((char *)self + self->vtable[35].delta, &rows);
    self->vtable[41].Quad((char *)self + self->vtable[41].delta, output[0]);
    self->end = (self->end - step) >? 0.0f;
}
