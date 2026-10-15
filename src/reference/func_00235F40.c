// Canonical physical ID input and borrowed pointer return; default flags unchanged.
void *func_00235EC8(int id);
extern void *D_00479D98;

void *func_00235F40(int id)
{
    void *result = func_00235EC8(id);
    if (result == 0)
        result = D_00479D98;
    return result;
}
