#ifndef TYPE_H_ENVE
#define TYPE_H_ENVE

typedef unsigned char                         Unsig8; 
typedef unsigned short                        Unsig16;
typedef unsigned int                          Unsig32;
typedef unsigned long long                    Unsig64;

typedef char                                  JustAChar;
typedef void                                  UPointer; 
typedef const char*                           String;   
typedef __attribute__((vector_size(16))) int  Unsig128; // BEST GCC FEATURE

#endif /* TYPE_H_ENVE */
