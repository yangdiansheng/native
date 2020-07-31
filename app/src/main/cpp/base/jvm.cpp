//
// Created by 杨殿生 on 2020/7/31.
//
#include "jvm.h"


static JavaVM *gVm = nullptr;

#ifdef __cplusplus
extern "C" {
#endif
void setJvm(JavaVM *jvm) {
    gVm = jvm;
}
JavaVM *getJvm() {
    return gVm;
}

#ifdef __cplusplus
}
#endif