// SLY3_CFLAGS: -Os -G0
extern int D_0036B138;
struct Item { short kind; short pad2; struct Rec *rec; int mark8; struct Item *next; };
struct Node;
struct Msg { short type; short pad; struct Rec *rec; };
struct Edge { int pad0; int mark4; int pad8; struct Msg msg; struct Edge *next; };
struct Node { int pad0; int mark4; struct Node *next8; struct Edge *edges; };
struct Rec { int pad0; int mark4; struct Node *node; int padC; int pad10; struct Item *list; struct Item *single; };
struct Walker { int pad0; int n1; struct Node **s1; int n2; struct Item **s2; int n3; struct Rec **s3; };
static inline struct Node *PopNode(struct Walker *w)
{
    if(w->n1 > 0) return w->s1[--w->n1];
    return 0;
}
static inline struct Rec *PopRec(struct Walker *w)
{
    if(w->n3 > 0) return w->s3[--w->n3];
    return 0;
}
static inline struct Item *PopItem(struct Walker *w)
{
    if(w->n2 > 0) return w->s2[--w->n2];
    return 0;
}
void func_00129E88(struct Walker *w)
{
    struct Node *node;
    struct Edge *edge;
    struct Rec *rec;
    struct Item *item;
    struct Item *link;
    int zero = 0;
    for(;;) {
        if((node = PopNode(w)) != 0) {
            for(edge = node->edges; edge; edge = edge->next) {
                struct Msg *msg = &edge->msg;
                edge->mark4 = (edge->mark4 & 0x7FFFFFFF) | ((unsigned short)D_0036B138 << 31);
                switch(msg->type) {
                case 0x1D:
                    item = (struct Item *)msg->rec;
                    if((item->mark8 < zero) != D_0036B138) {
                        item->mark8 = (item->mark8 & 0x7FFFFFFF) | (D_0036B138 << 31);
                        w->s2[w->n2++] = item;
                    }
                    break;
                case 0x1E:
                    rec = msg->rec;
                    if((rec->mark4 < zero) != D_0036B138) {
                        rec->mark4 = (rec->mark4 & 0x7FFFFFFF) | (D_0036B138 << 31);
                        w->s3[w->n3++] = rec;
                    }
                    break;
                case 0x20:
                    rec->mark4 = (rec->mark4 & 0x7FFFFFFF) | ((unsigned short)D_0036B138 << 31);
                    break;
                }
            }
            link = (struct Item *)node->next8;
            if(link && (((struct Node *)link)->mark4 < zero) != D_0036B138) {
                ((struct Node *)link)->mark4 = (((struct Node *)link)->mark4 & 0x7FFFFFFF) | (D_0036B138 << 31);
                w->s1[w->n1++] = (struct Node *)link;
            }
        } else if((rec = PopRec(w)) != 0) {
            for(item = rec->list; item; item = item->next) {
                if((item->mark8 < zero) != D_0036B138)
                    item->mark8 = (item->mark8 & 0x7FFFFFFF) | (D_0036B138 << 31);
            }
            item = rec->single;
            if((item->mark8 < zero) != D_0036B138) {
                item->mark8 = (item->mark8 & 0x7FFFFFFF) | (D_0036B138 << 31);
                w->s2[w->n2++] = item;
            }
            node = rec->node;
            if((node->mark4 < zero) != D_0036B138) {
                node->mark4 = (node->mark4 & 0x7FFFFFFF) | (D_0036B138 << 31);
                w->s1[w->n1++] = node;
            }
        } else if((item = PopItem(w)) != 0) {
            switch(item->kind) {
            case 0x1D:
                link = (struct Item *)item->rec;
                if((link->mark8 < zero) != D_0036B138) {
                    link->mark8 = (link->mark8 & 0x7FFFFFFF) | (D_0036B138 << 31);
                    w->s2[w->n2++] = link;
                }
                break;
            case 0x1E:
                rec = item->rec;
                if((rec->mark4 < zero) != D_0036B138) {
                    rec->mark4 = (rec->mark4 & 0x7FFFFFFF) | (D_0036B138 << 31);
                    w->s3[w->n3++] = rec;
                }
                break;
            case 0x20:
                link = (struct Item *)item->rec;
                ((struct Rec *)link)->mark4 = (((struct Rec *)link)->mark4 & 0x7FFFFFFF) | ((unsigned short)D_0036B138 << 31);
                break;
            }
            link = item->next;
            if(link && (link->mark8 < zero) != D_0036B138) {
                link->mark8 = (link->mark8 & 0x7FFFFFFF) | (D_0036B138 << 31);
                w->s2[w->n2++] = link;
            }
        } else return;
    }
}
