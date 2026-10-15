// Complete USA position initializer, with real receiver/stream inputs.
// Base initialization defines W; the full16-byte copy preserves it.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
extern char D_00345140[];
void func_00152448(void *,void *);
void func_001C8970(void *,int,void *,int);
void func_001AA250(char *p,void *stream)  {
    float *point;
    func_00152448(p,stream);
    point=(float *)(p+0x250);
    point[0]=0.0f;
    point[2]=-75.0f;
    point[1]=0.0f;
    *(qword *)(p+0x260)=*(qword *)(p+0x250);
    func_001C8970(p,0x6A,D_00345140,0);
}
