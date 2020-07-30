//
// Created by 杨殿生 on 2020/7/30.
//
#include <jni.h>
#include <string>
#include <logutil.h>

/**
 * Java 传递 字符串到 Native，然后再从 Native 返回 字符串
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_yangdainsheng_operations_StringType_getAndReleaseString(JNIEnv *env, jobject thiz,
                                                                 jstring s) {
    // Java 的字符串并不能直接转成 C/C++ 风格的字符串
    // 需要用到 GetStringChars 或者 GetStringUTFChars 相应的函数来申请内存
    // 转成一个指向 JVM 地址的指针
    // 最后还要释放该指针的内存
    const char *str = env->GetStringUTFChars(s,0);
    // GetStringUTFChars 涉及到申请内存，最好做个检查，防止 OOM
    // Get 和 Release 要配套使用，避免内存泄漏
    env->ReleaseStringUTFChars(s, str);
    // 从 Native 返回字符串，将 C/C++ 风格的字符串返回到 Java 层
    // 也需要用到特定的函数来转换 NewStringUTF 或者 NewString 等
    const char *c_str = "this is c String";
    return env->NewStringUTF(c_str);
}

/**
 * 反转字符串
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_yangdainsheng_operations_StringType_reverseString(JNIEnv *env, jobject thiz, jstring s) {
    const char *str = env->GetStringUTFChars(s,0);
    int len = env->GetStringLength(s);
    jchar res[len];
    for(int i = 0; i < len; i++){
        res[i] = str[len - 1 - i];
    }
    env->ReleaseStringUTFChars(s,str);
    return env->NewString(res,len);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_yangdainsheng_operations_StringType_getHalfString(JNIEnv *env, jobject thiz, jstring s) {
    const char *str = env->GetStringUTFChars(s,0);
    int len = env->GetStringLength(s);
    jchar res[len / 2];
    for(int i =0; i < len/2; i++){
        res[i] = str[i];
    }
    env->ReleaseStringUTFChars(s,str);
    return env->NewString(res,len/2);
}