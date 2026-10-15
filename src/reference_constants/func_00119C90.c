// SLY3_CFLAGS: -Os -G0
// Return a real BSP node orNULL; the two traversal routines preserve pointer V0.
typedef int qword __attribute__((mode(TI)));
struct BSP_NODE;
struct BSP_NODE *func_002B9CC0(struct BSP_NODE *,unsigned int limit,qword);
struct BSP_NODE *func_002B9C08(struct BSP_NODE *,unsigned int unused_limit,qword);
struct BSP_NODE *func_00119C90(struct BSP_NODE *node,unsigned int limit,qword point)
{
    struct BSP_NODE *result;
    if(limit!=0x7FFFFFFF)result=func_002B9CC0(node,limit,point);
    else result=func_002B9C08(node,0,point);
    return result;
}
