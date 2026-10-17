// SLY3_CFLAGS: -Os -G0
struct Entry { void *object; int first; int second; };
struct Method { short delta,unused; void (*method)(void *,int,int); };
struct Listener { unsigned char prefix[0xC]; struct Method *methods; };
struct Owner { unsigned char prefix[0x98]; int count; struct Entry entries[8]; };
int func_0013B500(void *object,int kind);
void func_0022B4A8(struct Owner *owner,struct Listener *listener,int first,int second)
{
    if(func_0013B500(listener,0x32)) {
        int count=owner->count;
        int i;
        for(i=0;i<count;i++) {
            if(owner->entries[i].object==listener)
                return;
        }
        if(count>=0&&count<8) {
            struct Entry *entry;
            struct Method *method;
            owner->count=count+1;
            entry=&owner->entries[count];
            entry->object=listener;
            entry->first=first;
            entry->second=second;
            method=&listener->methods[94];
            method->method((char *)listener+method->delta,first,second);
        }
    }
}
