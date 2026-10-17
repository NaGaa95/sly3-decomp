// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
typedef struct { Qword rows[4]; } Mat4;
Mat4 func_0028EC08(const void *first,const void *second,Mat4 *matrix);
void func_00290078(void *object);
struct MatrixOwner { unsigned char prefix[0x40]; void *parent; unsigned char pad44[0x50-0x44]; Mat4 matrix; };
void func_00166DE8(struct MatrixOwner *owner,Mat4 *matrix)
{
    owner->matrix=func_0028EC08(0,owner->parent,matrix);
    func_00290078(owner);
}
