//
// Created by 杨殿生 on 2020/8/3.
//
#include <jni.h>
#include <string>
#include <logutil.h>

/**
 * 使用局部引用来缓存static的变量，会导致出现野指针的情况
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_yangdainsheng_operations_LocalAndGlobalReferenceOp_errorCacheUseLocalReference(JNIEnv *env,jobject thiz) {
    static jmethodID mid = NULL;
    static jclass cls = NULL;
    //局部引用只能有512个，超过就会崩溃，如果需要局部引用多的，需要手动提前释放引用
    // 局部引用不能使用 static 来缓存，否则函数退出后，自动释放，成为野指针，程序 Crash
    if(cls == NULL) {
        cls = env->FindClass("java/lang/String");
        if(cls == NULL) return NULL;
    }else {
        LOGD("cls is not null but program will crash");
    }
    if(mid == NULL){
        mid = env->GetMethodID(cls,"<init>","([C)V");
        if(mid == NULL) return NULL;
    }
    jcharArray arr = env->NewCharArray(10);
    const jchar *c = env->GetStringChars(env->NewStringUTF("localrefrence"),0);
    env->SetCharArrayRegion(arr,0,9,c);
    jstring res = (jstring) env->NewObject(cls,mid,arr);
    env->DeleteLocalRef(arr);
    return res;
}


/**
 * 使用全局引用来缓存 static 的变量
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_yangdainsheng_operations_LocalAndGlobalReferenceOp_cacheWithGlobalReference(JNIEnv *env,jobject thiz) {
    static jclass globalCls = NULL;
    if(globalCls == NULL) {
        jclass localCls = env->FindClass("java/lang/String");
        if (localCls == NULL) return NULL;
        globalCls = (jclass)env->NewGlobalRef(localCls);
        env->DeleteLocalRef(localCls);
        if(globalCls == NULL) return NULL;
    } else {
        LOGD("use globalClass cached");
    }
    static jmethodID mid = NULL;
    if(mid == NULL) {
        mid = env->GetMethodID(globalCls,"<init>","(Ljava/lang/String;)V");
        if(mid == NULL) return NULL;
    } else {
        LOGD("use method cached");
    }
    return (jstring) env->NewObject(globalCls,mid,env->NewStringUTF("new string"));

}

/**
 * 弱全局引用的使用，要防止弱全局引用在使用时被 GC 回收了
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_LocalAndGlobalReferenceOp_useWeakGlobalReference(JNIEnv *env,
                                                                                      jobject thiz) {
    static jclass globalCls = NULL;
    if(globalCls == NULL){
        jclass localCls = env->FindClass("java/lang/String");
        if(localCls == NULL) return;
        globalCls = (jclass)(env->NewWeakGlobalRef(localCls));
        if(globalCls == NULL) return;
    }
    static jmethodID mid = NULL;
    if(mid == NULL) {
        mid = env->GetMethodID(globalCls,"<init>", "(Ljava/lang/String;)V");
        if(mid == NULL) return;
    }
    jboolean isGC = env->IsSameObject(globalCls,NULL);
    if (isGC) {
        LOGD("weak reference has been gc");
    } else {
        jstring str = (jstring) env->NewObject(globalCls, mid,
                                               env->NewStringUTF("jstring"));
        LOGD("str is %s", env->GetStringUTFChars(str, NULL));
    }
}

/**
 * 使用 局部引用管理的一系列函数
 * 注释掉是因为暂时不能运行，未完善代码细节
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_LocalAndGlobalReferenceOp_useLocalReferenceManageFuntions(
        JNIEnv *env, jobject thiz) {
    int len = 20;
    // Use EnsureLocalCapacity
//    if (env->EnsureLocalCapacity(len) < 0) {
//        // 创建失败，out of memory
//    }
//
//    for (int i = 0; i < len; ++i) {
//        jstring jstr = env->GetObjectArrayElement(arr, i);
//        // 处理 字符串
//        // 创建了足够多的局部引用，这里就不用删除了，显然占用更多的内存
//    }

    // Use PushLocalFrame & PopLocalFrame
//    for (int i = 0; i < len; ++i) {
//        if (env->PushLocalFrame(len)) { // 创建指定数据的局部引用空间
//            //out ot memory
//        }
//        jstring jstr = env->GetObjectArrayElement(arr, i);
//        // 处理字符串
//        env->PopLocalFrame(NULL); // 直接释放这个空间内的所有局部引用
//    }
}