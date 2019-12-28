#include <jni.h>
#include <string>
#include <pthread.h>
#include <ALog.h>
#include <GJvm.h>
#include <sys/syscall.h>
#include <unistd.h>


extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libnative_JniCallback_callback(
        JNIEnv *env,
        jclass clazz,//注意静态方法与普通方法的区别就是jobject变成了jclass
        jobject jobj
) {

    jclass jcls = env->GetObjectClass(jobj);
    jmethodID mid = env->GetMethodID(jcls, "cb", "(Ljava/lang/String;)V");
    jstring ss = env->NewStringUTF("hello");
    env->CallVoidMethod(jobj, mid, ss);

    return;
}

//jclass cb_class;
jobject cb_obj;
jmethodID cb_mid;

void *workInThread(void *param) {

    LOGI("进入线程");
    int tid = (int)syscall(SYS_gettid);
    int pid = (int)syscall(SYS_getpid);
    LOGI("workInThread:pid=%d,tid=%d",pid,tid);

    LOGI("the param is %d", param);//the param is 123

    JavaVM *jvm = getJvm();
    JNIEnv *env= nullptr;
    if(jvm->AttachCurrentThread(&env, nullptr)==0){

        env->CallVoidMethod(cb_obj,cb_mid,env->NewStringUTF("hello thread"));
        jvm->DetachCurrentThread();

    }
    //删除引用
    env->DeleteGlobalRef(cb_obj);
    LOGI("线程结束");
    pthread_exit(0);


}

extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libnative_JniCallback_threadCallback(
        JNIEnv *env,
        jclass clazz,//注意静态方法与普通方法的区别就是jobject变成了jclass
        jobject jobj
) {

    cb_obj = env->NewGlobalRef(jobj);

    jclass cb_class = env->GetObjectClass(jobj);
    cb_mid = env->GetMethodID(cb_class, "cb", "(Ljava/lang/String;)V");


    pthread_t pthread_ptr;
    //创建线程，最后一个参数为传递给线程函数的参数，可为空
    pthread_create(&pthread_ptr, nullptr, workInThread, reinterpret_cast<void *>(123));

    return;
}


