// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "card_commands.h"

/* Observed save prefix and embedded command storage. */
struct SaveCardView {
    int port, slot, word8, state;
    float elapsed, next_poll;
    int card_type, free_blocks, formatted;
    unsigned char unaccessed[0x13960 - 0x24];
    unsigned char command_context[0x14];
};

int func_002A22A8(void);
int func_002A2B68(int port, int slot, int *card_type,
                  int *free_blocks, int *formatted);

void func_001CEE08(void *command_context);

/* Initialize the real save context; the SDK init has no receiver input. */
void func_001CF058(void *storage, int port, int slot)
{
    struct SaveCardView *save = (struct SaveCardView *)storage;
    func_002A22A8();
    func_001CEE08(save->command_context);
    save->port = port;
    save->slot = slot;
    save->word8 = -1;
    save->state = 0;
    save->elapsed = save->next_poll = 0.0f;
    save->card_type = 0;
    save->free_blocks = 0;
    save->formatted = 0;
}

/* Preserve the original raw 32-bit SLL for every returned block word. */
int func_001D0760(void *storage, int *out_bytes)
{
    struct SaveCardView *save = (struct SaveCardView *)storage;
    void *command_context = save->command_context;
    int request, result;
    request = func_002A2B68(save->port, save->slot, &save->card_type,
                          &save->free_blocks, &save->formatted);
    result = func_001CEFC8(command_context, request, 1, 0);
    switch (result) {
    case 9:
        result = 0;
        break;
    case 10:
        result = 12;
        break;
    }
    if (result == 0)
        *out_bytes = (int)((unsigned int)save->free_blocks << 10);
    else
        *out_bytes = 0;
    return result;
}
