// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions
#include "mat.h"

struct HierarchyPackedMatrix { qword rows[4]; };

struct HierarchyMatrixNode {
    char prefix[0x40];
    HierarchyPackedMatrix matrix;
    char pad80[0x98 - 0x80];
    short kind;
    char pad9A[0xA0 - 0x9A];
    HierarchyMatrixNode *parent;
};
typedef char CheckMatrix64[sizeof(HierarchyPackedMatrix) == 64 ? 1 : -1];
typedef char CheckNodeViewB0[sizeof(HierarchyMatrixNode) == 0xB0 ? 1 : -1];
extern "C" HierarchyPackedMatrix *func_0011D768(HierarchyPackedMatrix *,const HierarchyPackedMatrix *);
extern "C" HierarchyPackedMatrix *func_0011D558(HierarchyPackedMatrix *,const HierarchyPackedMatrix *,const HierarchyPackedMatrix *);
extern "C" void *func_00291E8C(void *,const void *,unsigned int);
extern "C" void *func_00292034(void *,int,unsigned int);
extern "C" HierarchyPackedMatrix *func_0028B730(HierarchyPackedMatrix *,HierarchyMatrixNode *);

static inline void AddHierarchyMatrices(HierarchyPackedMatrix *output,const HierarchyPackedMatrix *left,const HierarchyPackedMatrix *right)
{
    const qword *a = left->rows;
    const qword *b = right->rows;
    qword *result = output->rows;
    for (int i = 0; i < 4; ++i) {
        qword sum;
        asm("vadd.xyzw %0,%1,%2" : "=j"(sum) : "j"(a[i]),"j"(b[i]));
        result[i] = sum;
    }
}

extern "C" HierarchyPackedMatrix *func_0028BAD0(HierarchyPackedMatrix *output,void *start,void *stop)
{
    HierarchyPackedMatrix local,source,result,composed,inverse;
    HierarchyMatrixNode *last = static_cast<HierarchyMatrixNode *>(stop);
    func_00292034(output,0,64);
    for (HierarchyMatrixNode *node = static_cast<HierarchyMatrixNode *>(start);
         node != last; node = node->parent) {
        switch (node->kind) {
        case 0: case 3: case 11: case 13: case 16: case 20:
            break;
        default:
            func_0028B730(&source,node);
            {
                qword fourth=source.rows[3],first=source.rows[0],second=source.rows[1],third=source.rows[2];
                local.rows[0]=first; local.rows[1]=second; local.rows[2]=third; local.rows[3]=fourth;
            }
            if (node->parent) {
                HierarchyPackedMatrix *relative = &result;
                func_0011D558(&composed,&node->parent->matrix,&local);
                func_0011D768(&inverse,&node->matrix);
                func_0011D558(relative,&composed,&inverse);
                AddHierarchyMatrices(&source,output,relative);
                func_00291E8C(output,&source,64);
            } else {
                HierarchyPackedMatrix *relative = &result;
                func_0011D768(&composed,&node->matrix);
                func_0011D558(relative,&local,&composed);
                AddHierarchyMatrices(&source,output,relative);
                func_00291E8C(output,&source,64);
            }
            break;
        }
    }
    if (last) {
        HierarchyPackedMatrix *relative = &result;
        HierarchyPackedMatrix *transformed = &source;
        func_0011D768(relative,&last->matrix);
        func_0011D558(transformed,relative,output);
        func_00291E8C(output,transformed,64);
    }
    return output;
}
