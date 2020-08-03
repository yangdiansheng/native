//
// Created by 杨殿生 on 2020/7/31.
//
#include <stdio.h>
#include "thread_operation.h"
#include "base/jvm.h"
#include <logutil.h>
#include <time.h>
#include <unistd.h>

void *printThreadHello(void *);
void *printThreadHelloArgs(void *);
void *printThreadJoin(void *);

static jmethodID printThreadName;
static jmethodID printNativeMsg;

struct ThreadRunArgs{
    int id;
    int result;
};

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

/**
 * 创建线程
 */
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

extern "C"
JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ThreadOp_createNativeThreadWithArgs(JNIEnv *env, jobject thiz) {
    pthread_t pthread;
    ThreadRunArgs *args = new ThreadRunArgs;
    args->id = 1001;
    args->result = 2002;
    int result = pthread_create(&pthread, NULL, printThreadHelloArgs, args);
    if(result != 0){
        LOGD("thread create failed");
    }else {
        LOGD("thread create success");
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ThreadOp_joinNativeThread(JNIEnv *env, jobject thiz) {
    pthread_t pthread;
    int result = pthread_create(&pthread, NULL, printThreadJoin, NULL);
    pthread_join(pthread,NULL);
    if(result != 0){
        LOGD("thread create failed");
    }else {
        LOGD("thread create success");
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

/**
 * 带参数的任务执行
 * @param arg
 * @return
 */
void *printThreadHelloArgs(void *arg){
    LOGD("printThreadHelloArgs");
    ThreadRunArgs *args = (ThreadRunArgs*)arg;
    LOGD("thread args id=%d",args->id);
//    pthread_exit(0);//线程退出
    LOGD("thread args result=%d",args->result);
    return NULL;
}

void *printThreadJoin(void *arg){
    ThreadRunArgs *args = (ThreadRunArgs*)arg;
    struct timeval begin;
    gettimeofday(&begin, NULL);
    sleep(3);
    struct timeval end;
    gettimeofday(&end,NULL);
    LOGD("time used is=%d",end.tv_sec - begin.tv_sec);
    pthread_exit(0);
}