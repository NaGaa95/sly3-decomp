// SLY3_CFLAGS: -Os -G0
struct Record { unsigned char prefix[0x24]; int value24; unsigned char gap28[8]; int value30; };
struct Holder { int kind; unsigned char gap4[4]; struct Record *record; };
int func_00254F80(struct Holder *holder)
{
    switch(holder->kind) {
    case 0:
    case 2:
        return (int)holder->record;
    case 1:
        return holder->record->value30;
    case 3:
        return holder->record->value24;
    default:
        return 0;
    }
}
