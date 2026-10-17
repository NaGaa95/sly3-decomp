// SLY3_CFLAGS: -Os -G0
struct TrackEvent { int key; void *target; };
struct TrackSelf {
    unsigned char prefix[0x414];
    int tracked;
};
void func_001F4278(void *receiver, int event, struct TrackEvent *record);
void func_00207FA0(struct TrackSelf *self, int event, struct TrackEvent *record)
{
    func_001F4278(self, event, record);
    switch (event) {
    case 6:
        if (record->target == self)
            self->tracked = record->key;
        break;
    case 7:
        if (record->target == self) {
            if (record->key == self->tracked)
                self->tracked = 0;
        }
        break;
    }
}
