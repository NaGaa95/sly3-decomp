// SLY3_CFLAGS: -Os -G0
void *func_002643C8(void *object,int id);
void *func_00260640(char *object,int id)
{
    switch(id) {
    case 0x360: return object+0x128;
    case 0x361: return object+0x12C;
    case 0x362: return object+0x130;
    }
    return func_002643C8(object,id);
}
