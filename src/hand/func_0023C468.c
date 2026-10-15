// Reset the original scalar vector to0,0,-1750 and set both state words to3. All stores use ordinary float/int members of the original nested record.
// Reference algorithm: src/hand/func_001C2078.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R {char prefix[0x80];float x,y,z;char unknown[0xA0-0x8C];int state;char unknown2[0xC0-0xA4];int mode;};
struct S { char unknown_0[0xD8]; struct R * record; };
void func_0023C468(struct S *p){float *vector=&p->record->x;vector[0]=0.0f;vector[2]=-1750.0f;vector[1]=0.0f;p->record->mode=3;p->record->state=3;}
