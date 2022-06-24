#ifndef WIND_PVECTOR
#define WIND_PVECTOR
    #include <stdlib.h>
    #define uint unsigned int
    typedef struct{
        uint **ptr;
        int crt;
        uint capacity;
        uint ndim;
    }*p_vector;

    void p_init(p_vector *obj,uint capacity,uint ndim);
    void p_del(p_vector *obj);
    void p_push(p_vector obj,const uint *p);
    void p_pop(p_vector obj,uint *p);
    uint p_has(p_vector obj,const uint *p);
    void showArray(uint *p,int num);
    void p_getPoint(p_vector obj,uint index,uint *p);
    void p_flatten(p_vector obj,uint *buf,uint buf_size);

#endif