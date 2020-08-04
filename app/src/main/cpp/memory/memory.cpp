
//
// Created by 杨 殿生 on 2020/8/5.
//
#include <stdlib.h>


void dynamicC(){
    //分配内存
    int *dynamicIntArray = (int*) malloc(sizeof(int) * 16);
    if(NULL == dynamicIntArray){
        //不能分配足够内存
    }else{
        *dynamicIntArray = 0;
        dynamicIntArray[9] = 1;
        //释放内存
        free(dynamicIntArray);
        dynamicIntArray = NULL;
    }

    //重新分配内存
    int *newdynamicIntArray = (int *)realloc(dynamicIntArray, sizeof(int) * 32);
    if(NULL == newdynamicIntArray){
        //不能重新分配
    }else {
        //更新内存指针
        dynamicIntArray = newdynamicIntArray;
    }
}


void dynamicCPlusPlus(){
    int *dynamic = new int;
    if(NULL == dynamic){

    }else {
        *dynamic = 0;
    }
    //分配数组
    int *dynamicIntArray = new int[16];

    delete dynamic;
    dynamic = 0;
    delete[] dynamicIntArray;
    dynamicIntArray = 0;
}

