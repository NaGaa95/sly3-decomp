// SLY3_CFLAGS: -Os -G0
extern int D_0036B138;
struct ParityRec { unsigned char prefix[4]; int word4; int word8; };
struct ParityMsg { short type; unsigned char pad[2]; struct ParityRec *rec; };
struct ParityOwner { unsigned char prefix[0xC]; int count1; struct ParityRec **list1; int count2; struct ParityRec **list2; };
void func_0012A2C8(struct ParityOwner *owner, struct ParityMsg *msg)
{
    struct ParityRec *rec;
    int zero = 0;
    switch(msg->type) {
    case 0x1D:
        rec = msg->rec;
        { int negative = (rec->word8 < zero); if(negative == D_0036B138) return; }
        rec->word8 = (rec->word8 & 0x7FFFFFFF) | (D_0036B138 << 31);
        owner->list1[owner->count1++] = rec;
        break;
    case 0x1E:
        rec = msg->rec;
        { int negative = (rec->word4 < zero); if(negative == D_0036B138) return; }
        rec->word4 = (rec->word4 & 0x7FFFFFFF) | (D_0036B138 << 31);
        owner->list2[owner->count2++] = rec;
        break;
    case 0x20:
        rec = msg->rec;
        rec->word4 = (rec->word4 & 0x7FFFFFFF) | ((unsigned short)D_0036B138 << 31);
        break;
    }
}
