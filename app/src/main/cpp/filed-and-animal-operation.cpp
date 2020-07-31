//
// Created by 杨殿生 on 2020/7/31.
//
#include <jni.h>
#include <string>
#include <logutil.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_FiledAndMethodOp_callFiled(JNIEnv *env, jobject thiz,
                                                             jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    jfieldID fid = env->GetFieldID(cls,"name","Ljava/lang/String;");
    if(fid == NULL)
        return;
    jstring jstr = (jstring) env->GetObjectField(animal,fid);
    const char *str = env->GetStringUTFChars(jstr,0);
    if(str == NULL)
        return;
    LOGD("name is %s", str);
    env->ReleaseStringUTFChars(jstr,str);
    jstr = env->NewStringUTF("replace name");
    if(jstr == NULL)
        return;
    env->SetObjectField(animal,fid,jstr);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_FiledAndMethodOp_callStaticFiled(JNIEnv *env, jobject thiz,
                                                                   jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    jfieldID fid = env->GetStaticFieldID(cls,"num","I");
    if(fid == NULL)
        return;
    jint num = env->GetStaticIntField(cls,fid);
    LOGD("get static field num is %d", num);
    env->SetStaticIntField(cls,fid,100);
}