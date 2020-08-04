//
// Created by 杨殿生 on 2020/7/31.
//

#include <jni.h>
#include <logutil.h>
#include <pthread.h>

#ifndef NATIVE_THREAD_OPERATION_H
#define NATIVE_THREAD_OPERATION_H


#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ThreadOp_createNativeThread(JNIEnv *env, jobject thiz);


JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ThreadOp_nativeInit(JNIEnv *env, jobject thiz);

JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ThreadOp_nativeFree(JNIEnv *env, jobject thiz);

JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ThreadOp_createNativeThreadWithArgs(JNIEnv *env, jobject thiz);

JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ThreadOp_joinNativeThread(JNIEnv *env, jobject thiz);

JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ThreadOp_waitNativeThread(JNIEnv *env, jobject thiz);

JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ThreadOp_waitNotifyThread(JNIEnv *env, jobject thiz);
#ifdef __cplusplus
}
#endif
#endif //NATIVE_THREAD_OPERATION_H
