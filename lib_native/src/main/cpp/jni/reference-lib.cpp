#include <jni.h>
#include <string>
#include <ALog.h>
#include <GJvm.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_junmeng_libnative_JniReference_localReference(
        JNIEnv *env,
        jclass clazz//注意静态方法与普通方法的区别就是jobject变成了jclass
) {

    jclass jcls = env->FindClass("java/lang/String");//此处的jcls即是局部引用，在函数执行完毕后会被自动释放

    jmethodID jmid = env->GetMethodID(jcls, "<init>", "(Ljava/lang/String;)V");

    jobject jobj = env->NewObject(jcls, jmid, env->NewStringUTF("LocalRef"));

    return static_cast<jstring>(jobj);

}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_junmeng_libnative_JniReference_globalReference(
        JNIEnv *env,
        jclass clazz//注意静态方法与普通方法的区别就是jobject变成了jclass
) {
    static jclass cacheCls = nullptr;
    if (cacheCls == nullptr) {
        jclass jcls = env->FindClass("java/lang/String");
        cacheCls = static_cast<jclass>(env->NewGlobalRef(jcls));//全局引用在不需要的地方需要释放掉
        env->DeleteLocalRef(jcls);//虽然局部引用会在函数结束时被释放，但还是要养成及时释放无用的引用

    } else {
        LOGI("使用缓存的全局引用");
    }

    jmethodID jmid = env->GetMethodID(cacheCls, "<init>", "(Ljava/lang/String;)V");

    jobject jobj = env->NewObject(cacheCls, jmid, env->NewStringUTF("GlobalRef"));

    return static_cast<jstring>(jobj);

}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_junmeng_libnative_JniReference_weakReference(
        JNIEnv *env,
        jclass clazz//注意静态方法与普通方法的区别就是jobject变成了jclass
) {
    static jclass cacheCls = nullptr;
    if (cacheCls == nullptr) {
        jclass jcls = env->FindClass("java/lang/String");
        cacheCls = static_cast<jclass>(env->NewWeakGlobalRef(jcls));//使用弱引用
        env->DeleteLocalRef(jcls);//虽然局部引用会在函数结束时被释放，但还是要养成及时释放无用的引用

    } else {
        LOGI("使用缓存的全局弱引用");
    }

    //这一步可以判断引用是否已经被回收
    bool isNull = env->IsSameObject(cacheCls, nullptr);
    if (isNull) {
        LOGI("全局弱引用已经被回收");
        jclass jcls = env->FindClass("java/lang/String");
        cacheCls = static_cast<jclass>(env->NewWeakGlobalRef(jcls));//使用弱引用
        env->DeleteLocalRef(jcls);
    }


    jmethodID jmid = env->GetMethodID(cacheCls, "<init>", "(Ljava/lang/String;)V");

    jobject jobj = env->NewObject(cacheCls, jmid, env->NewStringUTF("WeakGlobalRef"));

    return static_cast<jstring>(jobj);

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_junmeng_libnative_JniReference_errorWithTooManyLocalRef(
        JNIEnv *env,
        jclass clazz//注意静态方法与普通方法的区别就是jobject变成了jclass
) {

    //以下存在过多本地引用，你会发现无法正常执行完１０００个
    for (int i = 0; i < 1000; i++) {
        LOGI("new string %d", i);
        jstring jstr = env->NewStringUTF("hello"); // 创建一个java string
        //env->DeleteLocalRef(jstr);//如果及时释放本地引用，则能正常执行完
    }
    LOGI("errorWithTooManyLocalRef end");
    return 0;

}





