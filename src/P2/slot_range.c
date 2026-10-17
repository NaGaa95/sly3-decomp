// SLY3_CFLAGS: -Os -G0
void *func_002643C8(void *object,int id);
void *func_0026A150(char *object,int id)
{
    switch(id) {
    case 0x360: case 0x361:
        return object+(id-0x360)*12+0x12C;
    }
    return func_002643C8(object,id);
}
