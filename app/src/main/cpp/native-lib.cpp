#include <jni.h>
#include <string>
//#include <people>
#include "people/People.h"


extern "C" JNIEXPORT jstring JNICALL
Java_com_yangdainsheng_anative_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    People people;
    return env->NewStringUTF(people.getString().c_str());
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_yangdainsheng_anative_MainActivity_getString(JNIEnv *env, jobject thiz) {
}