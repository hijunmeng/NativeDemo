#include <jni.h>
#include <string>
#include <ALog.h>


extern "C" //extern "C"表示使用c编译，这样才能在c++中引用c
JNIEXPORT jstring JNICALL
Java_com_junmeng_libnative_JniNative_stringFromJNI(
        JNIEnv *env,
        jobject thiz/* this */) {

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_junmeng_libnative_JniStaticNative_stringFromJNI(
        JNIEnv *env,
        jclass clazz,//注意静态方法与普通方法的区别就是jobject变成了jclass
        jstring _s
) {

    const char *s = env->GetStringUTFChars(_s, NULL);

    LOGI("Java_com_junmeng_libnative_JniStaticNative_stringFromJNI:s=%s", s);

    std::string hello = "Hello from C++";

    env->ReleaseStringUTFChars(_s, s);
    return env->NewStringUTF(hello.c_str());
}
