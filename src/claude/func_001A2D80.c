// SLY3_CFLAGS: -Os -G0
// Streaming ring-buffer update, adapted from Sly 2 func_001849A0.
struct Stream {
    char pad[0x10];
    char *cursor;
    int available;
    char pad18[0x1C];
    int capacity;
    char *storage;
    int pad3C;
    int transferred, queued, remaining, retryOffset, sector;
    int slots, occupied, readIndex, writeIndex;
};

int func_002A0E08(void);
int func_002A0480(int);
int func_002A10D8(void);
void func_001630B0(unsigned int, unsigned int, void *, int);

static inline int Min(int a, int b) { return a < b ? a : b; }

void func_001A2D80(struct Stream *p)
{
    int chunk;
    p->cursor += p->available;
    p->available = 0;
    chunk = p->capacity / p->slots;
    if (chunk > 0x8000)
        chunk &= -0x8000;
    else
        chunk &= -0x800;
    if (p->occupied > 0) {
        int index = p->readIndex + 1;
        if (p->cursor == p->storage + index * chunk) {
            p->readIndex = index % p->slots;
            p->occupied--;
            p->cursor = p->storage + p->readIndex * chunk;
        }
    }
    do {
        if (p->queued > 0) {
            int pending = func_002A0E08() + p->retryOffset;
            int current = Min(pending, p->queued);
            if (p->transferred < current) {
                p->transferred = current;
            } else if (func_002A0480(1) == 0) {
                if (func_002A10D8() == 0) {
                    int bytes = p->queued;
                    p->transferred = bytes;
                    p->sector += bytes / 0x800;
                    p->remaining -= bytes;
                    p->queued = 0;
                    p->retryOffset = 0;
                } else {
                    int index = p->writeIndex;
                    int bytes = p->transferred;
                    char *buffer = p->storage + index * chunk + bytes;
                    int blocks = (p->queued - bytes + 0x7FF) >> 11;
                    int sector = p->sector + bytes / 0x800;
                    // The retry reuses a3 for the buffer offset before clearing it in the delay slot.
                    register int mode __asm__("$7") = 0;
                    p->retryOffset = bytes;
                    func_001630B0(sector, blocks, buffer, mode);
                }
            }
        }
        if (p->occupied < p->slots && p->queued == 0 && p->remaining > 0) {
            int bytes = Min(p->remaining, chunk);
            p->transferred = 0;
            p->queued = bytes;
            p->writeIndex = (p->writeIndex + 1) % p->slots;
            p->occupied++;
            func_001630B0(p->sector, ((bytes + 0x7FF) & -0x800) / 0x800, p->storage + p->writeIndex * chunk, 0);
        }
        if (!p->occupied) {
            p->available = 0;
        } else {
            int bytes = p->occupied == 1 ? p->transferred : chunk;
            int consumed = p->cursor - (p->storage + p->readIndex * chunk);
            p->available = Min(bytes - consumed, 0x1000);
        }
    } while (p->available == 0 && p->remaining > 0);
}
