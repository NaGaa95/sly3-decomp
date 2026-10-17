// SLY3_CFLAGS: -Os -G0
struct Entry { int id; int value; char text[4]; };
struct EntryList { unsigned char prefix[0x120]; int count; struct Entry entries[2]; };
extern char D_00327ED0[];
int func_00271448(char *output,const char *format,...);
void func_0026A030(struct EntryList *list,int id)
{
    if(list->count<2) {
        struct Entry *entry=&list->entries[list->count++];
        entry->id=id;
        entry->value=0;
        func_00271448(entry->text,D_00327ED0,0);
    }
}
