//
// Created by 杨殿生 on 2020/7/31.
//
#include <jni.h>
#include <string>
#include <logutil.h>

/**
 * 通过 创建String类型对象
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_yangdainsheng_operations_InvokeConstructorOp_invokeStringConstructor(JNIEnv *env,
jobject thiz) {
    // 由 C++ 字符串创建一个 Java 字符串
    jstring temp = env->NewStringUTF("this is char array");
    // 再从 Java 字符串获得一个字符数组指针，作为 String 构造函数的参数
    const jchar *chars = env->GetStringChars(temp, NULL);
    int len = 10;
    jclass stringclass = env->FindClass("java/lang/String");
    if(stringclass == NULL) return NULL;
    // 找到具体的方法，([C)V 表示选择 String 的 String(char value[]) 构造方法
    jmethodID cid = env->GetMethodID(stringclass, "<init>", "([C)V");
    if(cid == NULL) return NULL;
    jcharArray arr = env->NewCharArray(len);
    if(arr == NULL) return NULL;
    env->SetCharArrayRegion(arr,0,len,chars);
    jstring res = (jstring) env-> NewObject(stringclass,cid,arr);

    env->DeleteLocalRef(arr);
    env->DeleteLocalRef(stringclass);
    return res;
}

/**
 * 通过 构造函数创建一个对象
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_yangdainsheng_operations_InvokeConstructorOp_invokeAnimalConstructor(JNIEnv *env,
        jobject thiz) {
    jclass cls = env->FindClass("com/yangdainsheng/bean/Animal");
    if(cls == NULL)
        return NULL;
    jmethodID mid = env->GetMethodID(cls,"<init>", "(Ljava/lang/String;)V");
    if(mid == NULL) return NULL;
    jstring args = env->NewStringUTF("dog");
    jobject jobj = env->NewObject(cls,mid,args);
    env->DeleteLocalRef(cls);
    return jobj;
}

/**
 * 通过 AllocObject 方法来创建一个对象
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_yangdainsheng_operations_InvokeConstructorOp_allocObjectConstructor(JNIEnv *env,
                                                                             jobject thiz) {
    jclass cls = env->FindClass("com/yangdainsheng/bean/Animal");
    if(cls == NULL) return NULL;
    jmethodID mid = env->GetMethodID(cls,"<init>","(Ljava/lang/String;)V");
    if(mid == NULL) return NULL;
    jstring args = env->NewStringUTF("cat");
    jobject res = env->AllocObject(cls);
    if(res == NULL) return NULL;
    env->CallNonvirtualVoidMethod(res,cls,mid,args);
    if(env->ExceptionCheck()){
        env->DeleteLocalRef(cls);
        return NULL;
    }
    return res;
}

/**
 * 调用父类方法
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_InvokeConstructorOp_callSuperMethod(JNIEnv *env, jobject thiz) {
    //构造子类对象
    jclass clsCat = env->FindClass("com/yangdainsheng/bean/Cat");
    if(clsCat == NULL) return;
    jmethodID midCat = env->GetMethodID(clsCat,"<init>","(Ljava/lang/String;)V");
    if(midCat == NULL) return;
    jstring argsCat = env->NewStringUTF("small cat");
    jobject jobCat = env->NewObject(clsCat,midCat,argsCat);
    if(jobCat == NULL) return;

    jclass clsAnimal = env->FindClass("com/yangdainsheng/bean/Animal");
    if(clsAnimal == NULL) return;
    jmethodID midAnimal = env->GetMethodID(clsAnimal,"getName", "()Ljava/lang/String;");
    if(midAnimal == NULL) return;
    jstring name = (jstring)env->CallNonvirtualObjectMethod(jobCat,clsAnimal,midAnimal);
    LOGD("getName method value is %s", env->GetStringUTFChars(name, NULL));
    jmethodID midAnimal2 = env->GetMethodID(clsAnimal,"instanceMethod", "(I)V");
    if(midAnimal2 == NULL) return;
    env->CallNonvirtualVoidMethod(jobCat,clsAnimal,midAnimal2,23);
}

