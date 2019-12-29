#include <jni.h>
#include <string>
#include <ALog.h>
#include <GJvm.h>

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGI("JNI_OnLoad");
    //当Android的VM(Virtual Machine)执行到C组件(即so)里的System.loadLibrary()函数时便会执行JNI_OnLoad函数

    //因此可以在此执行一些初始化的工作，比如函数动态注册等


    //先保存jvm
    setJvm(vm);


    LOGI("JNI_OnLoad end");

    //返回值告诉vm使用的jni版本，如果没有JNI_OnLoad函数，那么默认是最旧的1.1版本
    //由于新版的JNI做了许多扩充，如果需要使用JNI的新版功能，
    //例如JNI 1.4的java.nio.ByteBuffer,就必须藉由JNI_OnLoad()函数来告知VM
    return JNI_VERSION_1_6;

}

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

extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libnative_JniStaticNative_byteReleaseWithCommit(
        JNIEnv *env,
        jclass clazz,//注意静态方法与普通方法的区别就是jobject变成了jclass
        jbyteArray array
) {

    jboolean isCopy;//是否有副本
    int len=env->GetArrayLength(array);
    jbyte* b=env->GetByteArrayElements(array,&isCopy);//一般当字节大于11KB时则不会产生副本
    LOGI("Java_com_junmeng_libnative_JniStaticNative_byteReleaseWithCommit:len=%d,isCopy=%d",len,isCopy);
    //改变值
    b[0]=0x02;
    env->ReleaseByteArrayElements(array,b,JNI_COMMIT);

    return ;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libnative_JniStaticNative_byteReleaseWithNull(
        JNIEnv *env,
        jclass clazz,//注意静态方法与普通方法的区别就是jobject变成了jclass
        jbyteArray array
) {

    jboolean isCopy;//是否有副本
    int len=env->GetArrayLength(array);
    jbyte* b=env->GetByteArrayElements(array,&isCopy);//一般当字节大于11KB时则不会产生副本
    LOGI("Java_com_junmeng_libnative_JniStaticNative_byteReleaseWithNull:len=%d,isCopy=%d",len,isCopy);
    //改变值
    b[0]=0x02;
    env->ReleaseByteArrayElements(array,b,NULL);

    return ;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libnative_JniStaticNative_byteReleaseWithAbort(
        JNIEnv *env,
        jclass clazz,//注意静态方法与普通方法的区别就是jobject变成了jclass
        jbyteArray array
) {

    jboolean isCopy;//是否有副本
    int len=env->GetArrayLength(array);
    jbyte* b=env->GetByteArrayElements(array,&isCopy);//一般当字节大于11KB时则不会产生副本
    LOGI("Java_com_junmeng_libnative_JniStaticNative_byteReleaseWithAbort:len=%d,isCopy=%d",len,isCopy);
    //改变值
    b[0]=0x02;
    env->ReleaseByteArrayElements(array,b,JNI_ABORT);

    return ;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libnative_JniStaticNative_byteCopy(
        JNIEnv *env,
        jclass clazz,//注意静态方法与普通方法的区别就是jobject变成了jclass
        jbyteArray array
) {
    int len=env->GetArrayLength(array);
    char cp[len];
    //将数据拷贝进cp数组里，比GetByteArrayElements相比好处就是减少jni调用，减少了一步release的调用
    env->GetByteArrayRegion(array, 0, len, reinterpret_cast<jbyte *>(cp));//一般当字节大于11KB时则不会产生副本
    LOGI("Java_com_junmeng_libnative_JniStaticNative_byteCopy:[0]=%d",cp[0]);
    return ;
}





