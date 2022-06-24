#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "p_vector.h"

void p_init(p_vector *obj,uint capacity,uint ndim){
    *obj = (p_vector)malloc(sizeof(p_vector));
    (*obj)->ptr = (uint **)malloc(capacity*sizeof(uint *));
    (*obj)->crt = 0;
    (*obj)->capacity = capacity;
    (*obj)->ndim = ndim;
    for(int i=0;i<capacity;i++){
        (*obj)->ptr[i] = (uint *)malloc(ndim*sizeof(uint));
        for(int j=0;j<ndim;j++)
            (*obj)->ptr[i][j] = 0;
    }
}

void p_del(p_vector *obj){
    uint capacity = (*obj)->capacity;
    uint ndim = (*obj)->ndim;
    for(int i=0;i<capacity;i++)
        free((*obj)->ptr[i]);
    free((*obj)->ptr);
    free(*obj);
}

void p_push(p_vector obj,const uint *p){
    uint ndim = obj->ndim;
    uint capacity = obj->capacity;
    if((obj->crt) < capacity)
        memcpy(obj->ptr[(obj->crt)++],p,ndim*sizeof(uint));
    else
        puts("p_vector is full!");
}
void p_pop(p_vector obj,uint *p){
    uint ndim = obj->ndim;
    uint capacity = obj->capacity;
    if((obj->crt) > 0)
        memcpy(p,obj->ptr[--(obj->crt)],ndim*sizeof(uint));
    else
        puts("p_vector is empty!");
}

uint p_has(p_vector obj,const uint *p){
    // 查看p_vector中是否存在相同的向量，存在则返回非0
    uint ndim = obj->ndim;
    uint flag;
    for(int i=0;i<(obj->crt);i++){
        flag = 1;
        for(int j=0;j<ndim;j++)
            if(obj->ptr[i][j] != p[j])    // 只要存在一个不同，就不相同
                flag = 0;
        if(flag == 1)
            return 1;
    }
    return 0;
}

void showArray(uint *p,int num){
    for(int i=0;i<num;i++){
        if(i)
            putchar(',');
        printf("%d",p[i]);
    }
    putchar('\n');
}

void p_getPoint(p_vector obj,uint index,uint *p){
    uint crt = obj->crt;
    uint ndim = obj->ndim;
    if(index >= crt){
        puts("索引超出范围！");
        return;
    }
    memcpy(p,obj->ptr[index],ndim*sizeof(uint));
}

void p_flatten(p_vector obj,uint *buf,uint buf_size){
    uint crt = obj->crt;
    uint ndim = obj->ndim;
    uint capacity = obj->capacity;
    uint subbuf[4] = {0};
    // printf("%d,%d,%d\n",buf_size,crt,ndim);
    if(buf_size < crt*ndim){
        puts("数组长度太短！");
        return;
    }
    for(int i=0;i<crt;i++){
        p_getPoint(obj,i,subbuf);
        memcpy(buf + i*ndim,subbuf,ndim*sizeof(uint));
    }
}


// int main(void){
//     p_vector a;
//     p_init(&a,5,4);

//     uint a1[4] = {1,4,2,4};
//     uint a2[4] = {6,2,3,1};
//     uint a3[4] = {9,3,2,5};

//     uint b1[4] = {0};
//     uint b2[4] = {0};
//     uint b3[4] = {0};
//     uint b4[4] = {0};
//     uint b5[4] = {0};

//     p_push(a,a1);
//     p_push(a,a2);
//     p_push(a,a2);
//     uint ret = p_has(a,a3);
//     printf("ret = %d\n",ret);

//     p_pop(a,b1);
//     p_pop(a,b2);
//     p_pop(a,b3);


//     p_del(&a);

//     showArray(b1,4);
//     showArray(b2,4);
//     showArray(b3,4);


//     return 0;
// }

