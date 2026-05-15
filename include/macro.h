#ifndef MACRO_H_ENVE
#define MACRO_H_ENVE

#define TODO(s) "todo : " str(s)
#define UNIMPL(s) "unimpl : " str(s)

#define VASM(...) __asm__ volatile (__VA_ARGS__)

#define str(s) xstr(s)
#define xstr(s) #s

#endif /* MACRO_H_ENVE */
