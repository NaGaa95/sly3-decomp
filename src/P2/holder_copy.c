// SLY3_CFLAGS: -Os -G0
struct CopyRequest { int bytes, alignment; };
struct Holder { unsigned char prefix[0x130]; void *current; };
extern char D_0034A040[];
void *func_001D24D0(struct CopyRequest *request, void *source);
void *func_002746B0(struct Holder *holder,int mode)
{
    if(mode==1 && holder->current==D_0034A040) {
        struct CopyRequest request;
        request.bytes=0x30;
        request.alignment=0x10;
        holder->current=func_001D24D0(&request,holder->current);
    }
    return holder->current;
}
