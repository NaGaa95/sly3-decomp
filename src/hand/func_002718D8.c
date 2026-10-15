// Return the original ASCII attribute mask8, or1 for wide whitespace codes.
// Complete72-byte body independently reviewed; unrelated trailing eight bytes stay unowned.
// SLY3_CFLAGS: -Os -G0
extern const unsigned char D_0032A691[128];
int func_002718D8(unsigned short value){if(value<0x80)return D_0032A691[value]&8;{switch(value){case 0xA0:case 0x3000:return 1;default:return 0;}}}
