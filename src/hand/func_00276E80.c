// Update the inherited receiver from the explicit stream and initialize both float controls of a present stored record to two.
// Reference algorithm: src/hand/func_001C2D70.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { char prefix[0xD4]; float first;float second; };
struct S { char unknown_0[0xD8]; struct R * record; };
void func_0023C0B8(struct S *object,void *stream);
void func_00276E80(struct S *object,void *stream)
{
    func_0023C0B8(object,stream);
    if(object->record){object->record->first=2.0f;object->record->second=2.0f;}
}
