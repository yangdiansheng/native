//
// Created by 杨殿生 on 2020/7/31.
//
#include <stdio.h>
#include "thread_operation.h"
#include "base/jvm.h"
#include <logutil.h>

void *printThreadHello(void *);

static jmethodID printThreadName;
static jmethodID printNativeMsg;


static jobject gObj = NULL;

JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    LOGD("JNI_OnLoad");
    setJvm(vm);
    return JNI_VERSION_1_6;
}


extern "C" JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ThreadOp_createNativeThread(JNIEnv *env, jobject thiz) {
    pthread_t thread;
    int result = pthread_create(&thread, NULL, printThreadHello, NULL);
    if(result != 0){
        LOGD("thread create failed");
    }else {
        LOGD("thread create success");
    }


}

extern "C"
JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ThreadOp_nativeInit(JNIEnv *env, jobject thiz) {
    jclass cls = env->GetObjectClass(thiz);
    printThreadName = env->GetMethodID(cls,"printThreadName","()V");
    printNativeMsg = env->GetMethodID(cls,"printNativeMsg", "(Ljava/lang/String;)V");
    if(gObj == NULL){
        gObj = env->NewGlobalRef(thiz);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ThreadOp_nativeFree(JNIEnv *env, jobject thiz) {
    if(gObj != NULL){
        env -> DeleteGlobalRef(gObj);
        gObj = NULL;
    }
}

void *printThreadHello(void *){
    LOGD("printThreadHello");
    JavaVM *gVm = getJvm();
    JNIEnv *env = nullptr;
    if(gVm->AttachCurrentThread(&env, nullptr) == 0){
        env->CallVoidMethod(gObj,printThreadName);
        gVm->DetachCurrentThread();
    }
    return NULL;
}