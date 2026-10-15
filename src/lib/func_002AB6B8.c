// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
typedef struct {
    unsigned int remaining_qwc;
    unsigned int dma_address;
} RuntimeMpegDma4Chunk;

#define MPEG_DMA_REG(a) (*(volatile unsigned int *)(a))

static __inline__ void EnableMpegDmaInterrupts(void)
{
    __asm__ volatile("sync\n\tei");
}

int func_002AB6B8(void *unused_channel, RuntimeMpegDma4Chunk *chunk)
{
    unsigned int limit = 0xffff;
    MPEG_DMA_REG(0x1000E010) = 0x10;
    if (chunk->remaining_qwc == 0) {
        EnableMpegDmaInterrupts();
        return 1;
    }
    if (chunk->remaining_qwc > limit) {
        MPEG_DMA_REG(0x1000B410) = chunk->dma_address;
        MPEG_DMA_REG(0x1000B420) = limit;
        MPEG_DMA_REG(0x1000B400) = 0x101;
        chunk->dma_address = (chunk->dma_address + limit * 16) & 0x0fffffff;
        chunk->remaining_qwc -= limit;
    } else {
        MPEG_DMA_REG(0x1000B410) = chunk->dma_address;
        MPEG_DMA_REG(0x1000B420) = chunk->remaining_qwc;
        MPEG_DMA_REG(0x1000B400) = 0x101;
        chunk->remaining_qwc = 0;
    }
    EnableMpegDmaInterrupts();
    return 0;
}

typedef char RuntimeMpegDma4ChunkSize8[(sizeof(RuntimeMpegDma4Chunk) == 8) ? 1 : -1];
typedef char RuntimeMpegDma4ChunkAlign4[(__alignof__(RuntimeMpegDma4Chunk) == 4) ? 1 : -1];
