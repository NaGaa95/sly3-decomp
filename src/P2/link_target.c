// SLY3_CFLAGS: -Os -G0
struct LinkRecord { char unknown_0[0x40]; void *linked; };
struct LinkHolder { int unknown_0; struct LinkRecord *record; };
void *func_00258CE0(struct LinkHolder *holder)
{
    return holder->record->linked;
}
