// Reference: Sly 2 src/lib/sceDmaGetChan.c; target Sly 3 0x0029FA38.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
/* libdma */
extern void *_sceDmaChans[10];
void *sceDmaGetChan(int id)
{
    return (unsigned)id < 10 ? _sceDmaChans[id] : 0;
}
