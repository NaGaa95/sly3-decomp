// SLY3_CFLAGS: -Os -G0
int func_00172F48(void *object);
int func_00173068(void *object);
int func_00173428(void *object);
int func_001731B0(void *object)
{
    int first=func_00172F48(object);
    int second=func_00173068(object);
    int third=func_00173428(object);
    return (first && !third) || (second && third);
}
