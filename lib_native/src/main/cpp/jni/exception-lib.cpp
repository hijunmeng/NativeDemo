#include <jni.h>
#include <ALog.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libnative_JniException_invokeJavaException(
        JNIEnv *env,
        jclass clazz//注意静态方法与普通方法的区别就是jobject变成了jclass
) {

    jclass jcls = env->FindClass("com/junmeng/libnative/JniException");
    jmethodID op = env->GetMethodID(jcls, "exception", "()I");
    jmethodID mid2 = env->GetMethodID(jcls, "<init>", "()V");
    jobject job = env->NewObject(jcls, mid2);
    env->CallIntMethod(job, op);

    jthrowable exc = env->ExceptionOccurred();//检测ｊａｖａ层是否有异常产生
    if (exc) {
        env->ExceptionDescribe();//输出异常信息
        env->ExceptionClear();//清除异常

    }

}

extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libnative_JniException_throwException(
        JNIEnv *env,
        jclass clazz//注意静态方法与普通方法的区别就是jobject变成了jclass
) {

    jclass cls = env->FindClass("java/lang/IllegalArgumentException");
    env->ThrowNew(cls, "产生异常了");
}