// SLY3_CFLAGS: -Os -G0
extern int D_003440C0;
extern int D_00475094;
extern unsigned char D_0046FBE0[];
extern unsigned char D_0036B340[];
extern unsigned int D_003175F8[];
extern unsigned int D_003175F0;
extern unsigned char *D_003175EC;
extern unsigned char D_003175E0[];
int func_00162E08(void);
void func_00221970(void *object, int value);
int func_00221A20(void *object);
void func_002219C8(void *object);
int func_00163150(int value);
int func_002A0E38(void *object, int count, void *buffer, void *header);
void func_00162E80(void)
{
    switch(D_003440C0) {
    case 3:
        if(D_00475094) {
            if(!func_00162E08()) {
                func_00221970(D_0046FBE0, 0);
                D_003440C0 = 1;
            }
        }
        break;
    case 1:
        if(func_00221A20(D_0046FBE0)) {
            unsigned char *record = D_003175EC;
            record += 0xCA0;
            if(func_00162E08()) {
                if(func_002A0E38(record, 1, D_0036B340, D_003175E0) == 1) D_003440C0 = 2;
            }
        }
        break;
    case 2:
        if(func_00163150(0)) {
            const unsigned char *p = D_0036B340;
            const char *table = (const char *)D_003175F8;
            unsigned int crc = 0xFFFFFFFF;
            int n = 0x800;
            while(n--) crc = *(const unsigned int *)(table + (((crc ^ *p++) & 0xFF) << 2)) ^ (crc >> 8);
            if(crc == D_003175F0) {
                func_002219C8(D_0046FBE0);
                D_003440C0 = 3;
            } else D_003440C0 = 1;
        }
        break;
    }
}
