// Complete original CID52 state-index mapper and classifier.
// True code 172/148; complete compiler-generated table verified as one section.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions

void func_001ADDD0(void *, int, int);

void func_001AF150(void *receiver, int index)
{
    switch (index) {
    case -1:
        func_001ADDD0(receiver, -1, -1);
        break;
    case 0:
        func_001ADDD0(receiver, 0, -1);
        break;
    case 1:
        func_001ADDD0(receiver, 3, -1);
        break;
    case 2:
        func_001ADDD0(receiver, 8, -1);
        break;
    case 3:
        func_001ADDD0(receiver, 5, -1);
        break;
    case 4:
        func_001ADDD0(receiver, 14, -1);
        break;
    case 5:
        func_001ADDD0(receiver, 15, -1);
        break;
    case 6:
        func_001ADDD0(receiver, 16, -1);
        break;
    case 7:
        func_001ADDD0(receiver, 18, -1);
        break;
    case 8:
        func_001ADDD0(receiver, 9, -1);
        break;
    case 9:
        func_001ADDD0(receiver, 23, -1);
        break;
    case 10:
        func_001ADDD0(receiver, 6, -1);
        break;
    }
}

struct ActorStateIndex {
    char prefix[0x19E0];
    int state;
};

int func_001AF200(const struct ActorStateIndex *receiver)
{
    switch (receiver->state) {
    case -1: return -1;
    case 0: return 0;
    case 3: return 1;
    case 8: return 2;
    case 5: return 3;
    case 14: return 4;
    case 15: return 5;
    case 16: return 6;
    case 18: return 7;
    case 9: return 8;
    case 23: return 9;
    case 6: return 10;
    default: return 11;
    }
}


