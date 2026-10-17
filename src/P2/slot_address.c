// SLY3_CFLAGS: -Os -G0
void *func_002643C8(void *object,int id);
void *func_00260558(char *object,int id)
{
    switch(id) {
    case 0x360: return object+0x2A8;
    case 0x361: return object+0x2AC;
    case 0x362: return object+0x2B0;
    }
    return func_002643C8(object,id);
}
