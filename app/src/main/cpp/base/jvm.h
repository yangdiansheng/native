//
// Created by 杨殿生 on 2020/7/31.
//
#include <jni.h>

#ifndef NATIVE_JVM_H
#define NATIVE_JVM_H

#ifdef __cplusplus
extern "C" {
#endif

void setJvm(JavaVM *jvm);
JavaVM *getJvm();

#ifdef __cplusplus
}
#endif

#endif //NATIVE_JVM_H
