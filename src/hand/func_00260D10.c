// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct Status { unsigned char pad[0x48]; int mode; int unknown; int start, remaining; } Status;
typedef struct Node { unsigned char pad[0x40]; Status *status; unsigned char gap[8]; struct Node *next; } Node;
extern Node *D_004797A8;
extern int D_0036C650;
// Require every active status to have reached at least two elapsed units.
int func_00260D10(void)
{
    Node *node = D_004797A8;
    while (node) {
        Status *status = node->status;
        int mode = status->mode;
        if (mode) {
            int elapsed = mode == 1 ? D_0036C650 - status->start : status->remaining;
            if (elapsed < 2) return 0;
        }
        node = node->next;
    }
    return 1;
}
