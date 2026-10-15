// Original USA entry 0x1fc1f0; ordinary C reconstruction.
// Receiver A0 and optional context A1 are explicit. Absent receiver.object38 or its word24 returns1. Otherwise a nonnull context is compared with the actual pointer returned by1FC118(receiver); that full callee only consumes receiver and produces its own child/global lookup arguments.
// SLY3_CFLAGS: -Os -G0
void *func_001FC118(void *);
int func_001FC1F0(char *p,void *context)  {
    char *object=*(char **)(p+0x38);
    if(!object || !*(int *)(object+0x24))return 1;
    if(!context)return 0;
    return context==func_001FC118(p);
}
