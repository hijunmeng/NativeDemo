#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_junmeng_libnative_JniNative_stringFromJNI(
        JNIEnv* env,
        jobject thiz/* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_junmeng_libnative_JniStaticNative_stringFromJNI(
        JNIEnv* env,
        jclass clazz) {
    std::string hello = "Hello from C++ with static";
    return env->NewStringUTF(hello.c_str());
}
