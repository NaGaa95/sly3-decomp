// Recovered parent row input and deferred session resource acquisition.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "session.h"
#include "bis.h"
#include "heap.h"
extern "C" void func_001C7D98(SESSION_CONTROL_PARENT *,CBinaryInputStream *);
extern "C" void *func_001D2538(ALLOCREQ *);
extern "C" void func_00119948(CBinaryInputStream *,void *);
extern "C" void func_0017AA08(SESSION_CONTROL_PARENT *parent,CBinaryInputStream *stream) {
    func_001C7D98(parent,stream);
    int count=stream->U16Read();
    {
        ALLOCREQ request;
        request.cb=count*sizeof(SESSION_CONTROL_ROW);
        request.cbAlign=16;
        parent->count=count;
        parent->rows=(SESSION_CONTROL_ROW *)func_001D2538(&request);
    }
    for(int i=0;i<parent->count;i++) {
        SESSION_CONTROL_ROW *row=&parent->rows[i];
        row->kind=stream->S32Read();
        switch(parent->mode) {
            case 0:case 1:
                row->node=(SESSION_CONTROL_NODE *)stream->S32Read();
                break;
            case 2: {
                ALLOCREQ matrixRequest;
                matrixRequest.cb=64;
                matrixRequest.cbAlign=16;
                row->node=(SESSION_CONTROL_NODE *)func_001D2538(&matrixRequest);
                func_00119948(stream,row->node);
                break;
            }
        }
    }
}
struct SESSION_LAZY_RESOURCE { char prefix[0xE0]; void *resource; };
extern "C" void *func_00244B68(SESSION_LAZY_RESOURCE *);
extern "C" void *func_0017A308(SESSION_LAZY_RESOURCE *session) {
    if(!session->resource)session->resource=func_00244B68(session);
    return session->resource;
}
