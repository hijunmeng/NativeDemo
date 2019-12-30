#include <jni.h>
#include <ALog.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libnative_JniException_invokeJavaException(
        JNIEnv *env,
        jclass clazz//注意静态方法与普通方法的区别就是jobject变成了jclass
) {

    //jclass jcls = env->FindClass("com/junmeng/libnative/JniException");//由于是静态方法，已经有了jclass，因此就不需要再FindClass了
    jmethodID op = env->GetMethodID(clazz, "exception", "()I");
    jmethodID mid2 = env->GetMethodID(clazz, "<init>", "()V");
    jobject job = env->NewObject(clazz, mid2);
    env->CallIntMethod(job, op);

    //一般是用在回调java层时，即使java层产生了异常，也不会直接奔溃掉
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