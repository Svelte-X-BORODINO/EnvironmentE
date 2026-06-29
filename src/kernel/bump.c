#include <type.h>
#include <bump.h>

extern JustAChar heap_start[];

UPointer* Alloc(Unsig32 size) {
    static JustAChar *heap_ptr = (JustAChar *)heap_start;
    UPointer *ptr = (UPointer *)heap_ptr;
    heap_ptr += size;
    return ptr;
}