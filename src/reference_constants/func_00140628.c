// Original USA entry 0x140628; ordinary C reconstruction.
// Only receiver A0 is consumed. Flag214 returns zero; signed state1520 selects constants5/15 or the explicit receiver-only 156388 query. Full query reads only receiver fields, including its actual switch table.
// SLY3_CFLAGS: -Os -G0
int func_00156388(void *);
int func_00140628(char *p)  {
    if(*(int *)(p+0x214))return 0;
    switch(*(int *)(p+0x1520)) {
        case 10:return 5;
        case 15:return 15;
        default:return func_00156388(p);
    }
}
