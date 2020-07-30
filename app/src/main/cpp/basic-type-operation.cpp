//
// Created by 杨殿生 on 2020/7/30.
//

#include <jni.h>
#include <string>
#include <logutil.h>

// 八种基本数据类型 从 Java 到 JNI 的类型转换操作

// JNI 的基础数据类型在 Java 的基础类型上加了一个 j
// 查看源码，JNI 的基础数据类型就是在 C/C++ 基础之上，通过 typedef 声明的别名

///* Primitive types that match up with Java equivalents. */
//typedef uint8_t  jboolean; /* unsigned 8 bits */
//typedef int8_t   jbyte;    /* signed 8 bits */
//typedef uint16_t jchar;    /* unsigned 16 bits */
//typedef int16_t  jshort;   /* signed 16 bits */
//typedef int32_t  jint;     /* signed 32 bits */
//typedef int64_t  jlong;    /* signed 64 bits */
//typedef float    jfloat;   /* 32-bit IEEE 754 */
//typedef double   jdouble;  /* 64-bit IEEE 754 */

extern "C"
JNIEXPORT jint JNICALL Java_com_yangdainsheng_operations_JNIBasicType_callNativeInt(JNIEnv *env, jobject thiz,jint num) {
    LOGD("java int value is %d", num);
    int c_num = num * 2;
    return c_num;
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_com_yangdainsheng_operations_JNIBasicType_callNativeByte(JNIEnv *env, jobject thiz, jbyte b) {
    LOGD("java byte value is %d", b);
    jbyte c_byte = b + (jbyte) 10;
    return c_byte;
}

extern "C"
JNIEXPORT jchar JNICALL
Java_com_yangdainsheng_operations_JNIBasicType_callNativeChar(JNIEnv *env, jobject thiz, jchar a) {
    LOGD("java char value is %c", a);
    jchar c_char = a + (jchar) 3;
    return c_char;
}

extern "C"
JNIEXPORT jshort JNICALL
Java_com_yangdainsheng_operations_JNIBasicType_callNativeShort(JNIEnv *env, jobject thiz, jshort s) {
    LOGD("java char value is %d", s);
    jshort c_short = s + (jshort) 10;
    return c_short;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_yangdainsheng_operations_JNIBasicType_callNativeLong(JNIEnv *env, jobject thiz, jlong l) {
    LOGD("java long value is %lld", l);
    jlong c_long = l + 100;
    return c_long;
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_com_yangdainsheng_operations_JNIBasicType_callNativeFloat(JNIEnv *env, jobject thiz, jfloat f) {
    LOGD("java float value is %f", f);
    jfloat c_float = f + (jfloat) 10.0;
    return c_float;
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_yangdainsheng_operations_JNIBasicType_callNativeDouble(JNIEnv *env, jobject thiz, jdouble d) {
    LOGD("java double value is %f", d);
    jdouble c_double = d + 20.0;
    return c_double;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_yangdainsheng_operations_JNIBasicType_callNativeBoolean(JNIEnv *env, jobject thiz,
                                                              jboolean b) {
    LOGD("java boolean value is %d", b);
    jboolean c_bool = (jboolean) !b;
    return c_bool;
}