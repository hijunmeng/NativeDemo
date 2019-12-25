#include <jni.h>
#include <string>
#include <ALog.h>

#define JAVA_CLASS "com/junmeng/libnative/JniDynamic" //java层对应的类的全路径


//此函数与java层方法对应，函数名可任意取
jint junmeng_addone(JNIEnv *env,
                      jclass clazz, //由于是静态方法，因此这里为jclass,如果是普通方法，则这里为jobject
                      int i) {
    LOGI("junmeng_addone:i=%d",i);
    i++;
    return i;

}
jstring junmeng_stringFromJNI(JNIEnv *env,
                      jclass clazz, //由于是静态方法，因此这里为jclass,如果是普通方法，则这里为jobject
                      jstring _s) {

    const char * s=env->GetStringUTFChars(_s,NULL);

    LOGI("junmeng_stringFromJNI:s=%s",s);

    std::string hello = "Hello from C++";

    env->ReleaseStringUTFChars(_s,s);
    return env->NewStringUTF(hello.c_str());

}



//方法签名等信息，如有多个方法就写多个
static JNINativeMethod gMethods[]{
        {"addone",//java层的方法名
                "(I)I", //签名
                (void *) junmeng_addone //native层的实现函数
        },
        {"stringFromJNI",//java层的方法名
                "(Ljava/lang/String;)Ljava/lang/String;", //签名
                (void *) junmeng_stringFromJNI //native层的实现函数
        }
};

int registerNativeMethods(JNIEnv *env,
                          const char *classname,//类名
                          const JNINativeMethod *methods,//注册方法数组
                          jint nMethods//注册方法数
) {

    jclass jcls;
    jcls = env->FindClass(classname);
    if (jcls == nullptr) {
        LOGE("找不到类，请确认类路径是否正确");
        return JNI_ERR;
    }
    int ret = env->RegisterNatives(jcls, methods, nMethods);
    if (ret != JNI_OK) {
        return ret;
    }

    return JNI_OK;

}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGI("JNI_OnLoad");
    //当Android的VM(Virtual Machine)执行到C组件(即so)里的System.loadLibrary()函数时便会执行JNI_OnLoad函数

    //因此可以在此执行一些初始化的工作，比如函数动态注册等

    JNIEnv *env = NULL; //注册时在JNIEnv中实现的，所以必须首先获取它
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) { //从JavaVM获取JNIEnv
        LOGE("获取JNIEnv失败");
        return JNI_ERR;
    }
    int ret = registerNativeMethods(env, JAVA_CLASS, gMethods,
                                    sizeof(gMethods) / sizeof(JNINativeMethod));
    if (ret != JNI_OK) {
        LOGE("动态注册失败，可能是方法发生了变化，请仔细核对");
        return ret;
    };

    LOGI("JNI_OnLoad end");

    //返回值告诉vm使用的jni版本，如果没有JNI_OnLoad函数，那么默认是最旧的1.1版本
    //由于新版的JNI做了许多扩充，如果需要使用JNI的新版功能，
    //例如JNI 1.4的java.nio.ByteBuffer,就必须藉由JNI_OnLoad()函数来告知VM
    return JNI_VERSION_1_6;

}

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    LOGI("JNI_OnUnload");
}

