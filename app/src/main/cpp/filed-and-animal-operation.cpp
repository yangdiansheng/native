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

extern "C"
JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_FiledAndMethodOp_callIntanceMethod(JNIEnv *env, jobject thiz,
                                                                     jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    jmethodID mid = env->GetMethodID(cls,"instanceMethod", "(I)V");
    if(mid == NULL) return;
    env->CallVoidMethod(animal,mid,1111);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_FiledAndMethodOp_callStaticMethod(JNIEnv *env, jobject thiz,
                                                                    jobject animal) {
    jclass cls = env->GetObjectClass(animal);
    //调用一个参数
    jmethodID mid = env->GetStaticMethodID(cls,"staticMethod","(Ljava/lang/String;)Ljava/lang/String;");
    if(mid == NULL) return;
    jstring jstr = env->NewStringUTF("string from native");
    env->CallStaticObjectMethod(cls,mid, jstr);

    //调用两个参数，一个数组，一个int类型
    jmethodID mid2 = env->GetStaticMethodID(cls,"staticMethod","([Ljava/lang/String;I)Ljava/lang/String;");
    if(mid2 == NULL) return;
    jclass objcls = env->FindClass("java/lang/String");
    if(objcls == NULL) return;
    int size = 3;
    jobjectArray arr = env->NewObjectArray(size,objcls,NULL);
    if(arr == NULL) return;
    jstring element;
    for(int i = 0; i < size; i++){
        element = env->NewStringUTF("str in c");
        env->SetObjectArrayElement(arr,i,element);
    }
    env->CallStaticObjectMethod(cls,mid2,arr,3);
}