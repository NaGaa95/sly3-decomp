// SLY3_CFLAGS: -Os -G0
struct Inner24 { unsigned char prefix[0x24]; int value; };
struct Mid1C { unsigned char prefix[0x1C]; struct Inner24 *inner; };
struct Owner20 { unsigned char prefix[0x20]; struct Mid1C *mid; };
int func_001FDB70(struct Owner20 *owner) { return owner->mid->inner->value; }
