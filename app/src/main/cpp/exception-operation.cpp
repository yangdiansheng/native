//
// Created by 杨殿生 on 2020/8/3.
//
#include <jni.h>
#include <string>
#include <logutil.h>
#include <commonutil.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ExceptionOP_nativeInvokeJavaException(JNIEnv *env, jobject thiz) {
    jclass cls = env->FindClass("com/yangdainsheng/operations/ExceptionOP");
    if(cls == NULL) return;
    jmethodID opMid = env->GetMethodID(cls,"operation","()I");
    if(opMid == NULL) return;
    jmethodID obmid  = env->GetMethodID(cls,"<init>", "()V");
    if(obmid == NULL) return;
    jobject obj = env->NewObject(cls,obmid);
    env->CallIntMethod(obj,opMid);

    //检测异常
    jthrowable exc = env->ExceptionOccurred();
    if(exc){
        //打印日志
        env->ExceptionDescribe();
        // 这代码才是关键不让应用崩溃的代码
        env->ExceptionClear();
        // 发生异常了要记得释放资源
        env->DeleteLocalRef(cls);
        env->DeleteLocalRef(obj);
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ExceptionOP_nativeThrowException(JNIEnv *env, jobject thiz) {
    throwByName(env, "java/lang/IllegalArgumentException", "native throw exception");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ExceptionOP_doit(JNIEnv *env, jobject thiz) {
    jclass cls = env->FindClass("com/yangdainsheng/operations/ExceptionOP");
    if(cls == NULL) return;
    jmethodID opMid = env->GetMethodID(cls,"callback", "()V");
    if(opMid == NULL) return;
    jmethodID obmid  = env->GetMethodID(cls,"<init>", "()V");
    if(obmid == NULL) return;
    jobject obj = env->NewObject(cls,obmid);
    env->CallVoidMethod(obj,opMid);

    jthrowable exc = env->ExceptionOccurred();
    if(exc){
        env->ExceptionDescribe();
        env->ExceptionClear();
        jclass ecls = env->FindClass("java/lang/IllegalArgumentException");
        if(ecls == NULL) return;
        env->ThrowNew(ecls,"Thrown from C++ code");
    }
}