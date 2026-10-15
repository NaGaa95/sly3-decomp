// Reference: Sly 2 src/lib/_search_svdata.c; target Sly 3 0x00295BC8.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
typedef struct SD { int rpc_number; int pad[13]; struct SD *link; } SD;
typedef struct QD { int pad[2]; SD *link; int p2[2]; struct QD *next; } QD;
typedef struct { int pad[10]; QD *active; } CTX;
SD *_search_svdata(int rpc, CTX *c)
{
    QD *q;
    SD *s;
    for (q = c->active; q; q = q->next) {
        for (s = q->link; s; s = s->link)
            if (s->rpc_number == rpc) return s;
    }
    return 0;
}
