// SLY3_CFLAGS: -Os -G0 -fno-strength-reduce -fno-exceptions
union Word { int i; float f; void *p; };
struct Blob { Word w[28]; };
struct Request { int size; int alignment; };
struct Voices { int pad[7]; int list[1]; };
struct Stream;
struct Record {
    unsigned type : 8;
    unsigned flag : 1;
    unsigned first : 11;
    unsigned second : 11;
    int x4;
    union { int i; float f; void *p; unsigned low : 11; } v8;
    union { int i; float f; void *p; short s[2]; } vC;
};
struct Table {
    unsigned char pad00[0x40];
    int count;
    Record *records;
};
extern "C" {
int func_00119178(Stream *s);
int func_00119128(Stream *s);
int func_001191E0(Stream *s);
float func_00119260(Stream *s);
int func_00119048(Stream *s);
int func_001190A8(Stream *s);
void func_001192D8(Stream *s, void *destination);
void func_001193B8(Stream *s, void *destination);
void func_001193D8(Stream *s, void *destination);
void *func_001D2470(Request *request);
void *func_001D2538(Request *request);
}
#define BLOB(r) ((Blob *)(r)->v8.p)
#define ALLOC(fn, n) (req.size = (n), req.alignment = 16, fn(&req))
extern "C" void func_00225220(Table *self, Stream *s)
{
    Request req;
    int index;
    int count = func_00119178(s);
    req.size = count * 16;
    req.alignment = 16;
    self->count = count;
    self->records = (Record *)func_001D2538(&req);
    for (index = 0; index < self->count; index++) {
        Record *rec = &self->records[index];
        rec->type = func_00119128(s);
        rec->x4 = func_001191E0(s);
        rec->flag = func_00119128(s) & 1;
        rec->first = func_00119048(s);
        rec->second = func_00119048(s);
        switch (rec->type) {
        case 0:
            rec->v8.low = func_00119048(s);
            break;
        case 12: {
            int n = func_00119128(s);
            rec->v8.i = n;
            rec->vC.p = ALLOC(func_001D2470, n * 4);
            for (int j = 0; j < rec->v8.i; j++)
                ((int *)rec->vC.p)[j] = func_001191E0(s);
            break;
        }
        case 13: {
            rec->v8.p = ALLOC(func_001D2470, 0xC);
            BLOB(rec)->w[0].i = func_00119128(s);
            void *list = ALLOC(func_001D2470, BLOB(rec)->w[0].i * 4);
            BLOB(rec)->w[1].p = list;
            for (int j = 0; j < BLOB(rec)->w[0].i; j++)
                ((int *)BLOB(rec)->w[1].p)[j] = func_001191E0(s);
            BLOB(rec)->w[2].i = func_001191E0(s);
            break;
        }
        case 25:
            rec->v8.p = ALLOC(func_001D2470, 0x10);
            BLOB(rec)->w[0].i = func_001191E0(s);
            BLOB(rec)->w[1].i = func_001191E0(s);
            BLOB(rec)->w[2].i = func_001191E0(s);
            BLOB(rec)->w[3].i = func_00119128(s);
            break;
        case 29:
            rec->v8.p = ALLOC(func_001D2470, 0x20);
            func_001193B8(s, rec->v8.p);
            func_001193D8(s, &BLOB(rec)->w[4]);
            BLOB(rec)->w[6].f = func_00119260(s);
            break;
        case 31:
            rec->v8.i = func_00119128(s);
            rec->vC.i = func_00119128(s);
            break;
        case 34:
            rec->v8.i = func_001191E0(s);
            rec->vC.s[0] = func_00119128(s);
            rec->vC.s[1] = func_00119128(s);
            break;
        case 46:
            rec->v8.p = ALLOC(func_001D2470, 0xC);
            BLOB(rec)->w[0].i = func_001191E0(s);
            BLOB(rec)->w[1].i = func_001191E0(s);
            BLOB(rec)->w[2].i = func_001191E0(s);
            break;
        case 47:
            rec->v8.p = ALLOC(func_001D2470, 0xC);
            func_001193D8(s, rec->v8.p);
            BLOB(rec)->w[2].i = func_001191E0(s);
            break;
        case 48:
            rec->v8.p = ALLOC(func_001D2470, 0x14);
            BLOB(rec)->w[0].i = func_001191E0(s);
            BLOB(rec)->w[1].f = func_00119260(s);
            BLOB(rec)->w[2].f = func_00119260(s);
            BLOB(rec)->w[3].i = func_001191E0(s);
            BLOB(rec)->w[4].i = func_00119128(s);
            break;
        case 51:
            rec->v8.p = ALLOC(func_001D2470, 0x14);
            BLOB(rec)->w[0].i = func_001191E0(s);
            BLOB(rec)->w[1].i = func_00119128(s);
            BLOB(rec)->w[2].i = func_00119128(s);
            BLOB(rec)->w[3].f = func_00119260(s);
            BLOB(rec)->w[4].i = func_001191E0(s);
            break;
        case 52:
            rec->v8.p = ALLOC(func_001D2470, 0x14);
            BLOB(rec)->w[0].i = func_001191E0(s);
            BLOB(rec)->w[1].f = func_00119260(s);
            BLOB(rec)->w[2].i = func_00119128(s);
            BLOB(rec)->w[3].f = func_00119260(s);
            BLOB(rec)->w[4].i = func_001191E0(s);
            break;
        case 53:
            rec->v8.p = ALLOC(func_001D2470, 0xC);
            BLOB(rec)->w[0].i = func_001191E0(s);
            BLOB(rec)->w[1].f = func_00119260(s);
            BLOB(rec)->w[2].f = func_00119260(s);
            break;
        case 54:
            rec->v8.p = ALLOC(func_001D2470, 0x10);
            BLOB(rec)->w[0].i = func_001191E0(s);
            BLOB(rec)->w[1].i = func_00119128(s);
            BLOB(rec)->w[2].i = func_00119128(s);
            BLOB(rec)->w[3].i = func_00119128(s);
            break;
        case 55:
            rec->v8.p = ALLOC(func_001D2470, 0xC);
            BLOB(rec)->w[0].i = func_001191E0(s);
            BLOB(rec)->w[1].f = func_00119260(s);
            BLOB(rec)->w[2].f = func_00119260(s);
            break;
        case 62:
            rec->v8.i = func_00119178(s);
            break;
        case 63:
            rec->v8.i = func_00119128(s);
            break;
        case 64:
            rec->v8.f = func_00119260(s);
            rec->vC.i = func_00119128(s);
            break;
        case 65:
        case 66:
            rec->v8.p = ALLOC(func_001D2470, 0xC);
            BLOB(rec)->w[0].i = func_001191E0(s);
            BLOB(rec)->w[1].i = func_001191E0(s);
            BLOB(rec)->w[2].f = func_00119260(s);
            break;
        case 67:
            rec->v8.p = ALLOC(func_001D2470, 0x1C);
            BLOB(rec)->w[0].i = func_00119178(s);
            BLOB(rec)->w[1].i = func_001191E0(s);
            BLOB(rec)->w[2].i = func_001191E0(s);
            BLOB(rec)->w[3].i = func_001191E0(s);
            BLOB(rec)->w[4].f = func_00119260(s);
            BLOB(rec)->w[5].f = func_00119260(s);
            BLOB(rec)->w[6].f = func_00119260(s);
            break;
        case 68:
            rec->v8.i = func_00119178(s);
            break;
        case 69:
            rec->v8.p = ALLOC(func_001D2538, 0x60);
            func_001192D8(s, rec->v8.p);
            func_001192D8(s, &BLOB(rec)->w[4]);
            BLOB(rec)->w[8].f = func_00119260(s);
            BLOB(rec)->w[9].f = func_00119260(s);
            BLOB(rec)->w[20].f = func_00119260(s);
            BLOB(rec)->w[11].i = func_00119048(s);
            BLOB(rec)->w[21].i = func_001191E0(s);
            BLOB(rec)->w[22].i = func_001191E0(s);
            func_001192D8(s, &BLOB(rec)->w[16]);
            func_001191E0(s);
            break;
        case 70:
            rec->v8.p = ALLOC(func_001D2470, 0x70);
            BLOB(rec)->w[0].i = func_001191E0(s);
            BLOB(rec)->w[1].i = func_001191E0(s);
            func_001192D8(s, &BLOB(rec)->w[4]);
            func_001192D8(s, &BLOB(rec)->w[8]);
            BLOB(rec)->w[12].f = func_00119260(s);
            BLOB(rec)->w[24].i = func_001191E0(s);
            BLOB(rec)->w[25].i = func_001191E0(s);
            BLOB(rec)->w[26].i = func_001191E0(s);
            break;
        case 74:
            rec->v8.p = ALLOC(func_001D2470, 0x50);
            func_001192D8(s, rec->v8.p);
            func_001192D8(s, &BLOB(rec)->w[4]);
            BLOB(rec)->w[8].f = func_00119260(s);
            break;
        case 78:
            rec->v8.i = func_001191E0(s);
            rec->vC.i = func_001191E0(s);
            if (rec->v8.i == -1)
                rec->v8.i = 0x40;
            break;
        case 79:
            rec->v8.i = func_00119128(s);
            break;
        case 82:
        case 83: {
            int n = func_00119128(s);
            req.size = n < 2 ? 0x20 : n * 4 + 0x1C;
            req.alignment = 16;
            rec->v8.p = func_001D2538(&req);
            BLOB(rec)->w[6].i = n;
            BLOB(rec)->w[5].i = n;
            BLOB(rec)->w[7].i = -1;
            for (int j = 0; j < n; j++)
                ((Voices *)rec->v8.p)->list[j] = func_001191E0(s);
            if (rec->type == 0x52) {
                BLOB(rec)->w[0].i = func_00119128(s);
                BLOB(rec)->w[1].i = func_001191E0(s);
                BLOB(rec)->w[2].i = func_001191E0(s);
                BLOB(rec)->w[3].i = func_001191E0(s);
                BLOB(rec)->w[4].f = func_00119260(s);
            }
            break;
        }
        case 85:
        case 86:
            rec->v8.i = func_00119178(s);
            rec->vC.i = func_00119128(s);
            break;
        case 87:
            rec->v8.i = func_00119128(s);
            break;
        case 88:
            rec->v8.f = func_00119260(s);
            rec->vC.i = func_001191E0(s);
            break;
        case 89:
        case 90:
            rec->v8.i = func_00119178(s);
            break;
        case 75:
        case 91:
            rec->v8.f = func_00119260(s);
            break;
        case 92:
            rec->v8.p = ALLOC(func_001D2470, 0x10);
            BLOB(rec)->w[0].i = func_001191E0(s);
            BLOB(rec)->w[1].i = func_00119128(s);
            BLOB(rec)->w[2].i = func_001191E0(s);
            BLOB(rec)->w[3].i = func_00119128(s);
            break;
        case 38:
        case 56:
        case 57:
        case 96:
            rec->v8.i = func_001191E0(s);
            rec->vC.f = func_00119260(s);
            break;
        case 4: case 7: case 8: case 15: case 16: case 26: case 40: case 42:
        case 58: case 59: case 60: case 61: case 98: case 99: case 104:
            rec->v8.i = func_001191E0(s);
            rec->vC.i = func_001191E0(s);
            break;
        case 107:
            rec->v8.p = ALLOC(func_001D2470, 0x14);
            BLOB(rec)->w[0].i = func_001191E0(s);
            BLOB(rec)->w[1].i = func_001190A8(s);
            BLOB(rec)->w[2].i = func_00119048(s);
            BLOB(rec)->w[3].i = func_00119128(s);
            BLOB(rec)->w[4].i = func_001191E0(s);
            break;
        case 108: {
            rec->v8.p = ALLOC(func_001D2470, 0x10);
            BLOB(rec)->w[0].i = func_001191E0(s);
            int n = func_00119128(s);
            BLOB(rec)->w[1].i = n;
            void *first = ALLOC(func_001D2470, n * 4);
            BLOB(rec)->w[2].p = first;
            void *second = ALLOC(func_001D2470, n * 4);
            BLOB(rec)->w[3].p = second;
            for (int j = 0; j < n; j++) {
                ((int *)BLOB(rec)->w[2].p)[j] = func_001191E0(s);
                ((int *)BLOB(rec)->w[3].p)[j] = func_001191E0(s);
            }
            break;
        }
        case 115:
            rec->v8.i = func_00119128(s);
            break;
        case 14: case 19: case 28: case 30: case 111: case 112: case 116:
            rec->v8.i = func_001191E0(s);
            rec->vC.i = func_00119128(s);
            break;
        case 22:
        case 117:
            rec->v8.p = ALLOC(func_001D2470, 0xC);
            BLOB(rec)->w[0].i = func_001191E0(s);
            BLOB(rec)->w[1].i = func_001191E0(s);
            BLOB(rec)->w[2].i = func_00119128(s);
            break;
        case 118:
            rec->v8.p = ALLOC(func_001D2470, 0x14);
            BLOB(rec)->w[0].i = func_001191E0(s);
            BLOB(rec)->w[1].i = func_00119128(s);
            BLOB(rec)->w[2].i = func_00119128(s);
            BLOB(rec)->w[3].i = func_00119128(s);
            BLOB(rec)->w[4].i = func_00119128(s);
            break;
        case 11: case 17: case 18: case 21: case 23: case 24: case 27: case 32:
        case 33: case 36: case 37: case 41: case 43: case 44: case 45: case 72:
        case 73: case 77: case 81: case 97: case 101: case 102: case 103:
        case 106: case 113: case 114: case 119:
            rec->v8.i = func_001191E0(s);
            break;
        }
    }
}
