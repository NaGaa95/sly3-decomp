// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
void func_001C81B8(void *receiver);
void func_0015CE68(void *member);
void func_0011AF60(void *head, void *receiver);
void func_0011B028(void *head, void *receiver);
extern char D_00479B44[];
}

extern "C" void func_001A34D8(void *receiver)
{
    func_001C81B8(receiver);
    func_0015CE68((char *)receiver + 0xD0);
}

extern "C" void func_001A3508(void *receiver)
{
    func_0011B028(D_00479B44, receiver);
}

extern "C" void func_001A3530(void *receiver)
{
    func_0011AF60(D_00479B44, receiver);
}
