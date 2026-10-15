// Reference: Sly 2 src/lib/_sceRpcGetFPacket2.c; target Sly 3 0x002959A0.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
struct rpcd { int pad[5]; char *buf; int n; char *buf2; int n2; int idx; };
void *_sceRpcGetFPacket(struct rpcd *d);
void *_sceRpcGetFPacket2(struct rpcd *d, int rid)
{
    if (rid < 0 || rid >= d->n2) return _sceRpcGetFPacket(d);
    return d->buf2 + (rid << 6);
}
