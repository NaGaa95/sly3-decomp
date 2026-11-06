// SLY3_CFLAGS: -Os -G0
// Read a scalar from the cached record at (+0xD8)->+0xDC without creating it (cf. func_00241B60), 0 if absent.
struct Record { float f0, f4, f8, fC; };
struct Owner { char prefix[0xDC]; struct Record *record; };
struct Actor { char prefix[0xD8]; struct Owner *owner; };
static inline struct Record *PeekRecord(struct Actor *a) { return a->owner ? a->owner->record : 0; }
float func_00241C40(struct Actor *a) { struct Record *r = PeekRecord(a); if (r) return r->f8; return 0.0f; }
