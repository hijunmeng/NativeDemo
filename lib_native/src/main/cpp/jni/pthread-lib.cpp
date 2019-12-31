#include <jni.h>
#include <ALog.h>
#include <pthread.h>
#include <cstring>
#include <unistd.h>
#include <queue>


typedef struct ThreadArgs {
    int id;
    char msg[64];

} ThreadParam;

/**
 * 线程执行函数
 * @param param 　参数
 * @return
 */
static void *workInThread(void *param) {//加上static是为了避免与其他文件产生同名

    ThreadParam *params = static_cast<ThreadParam *>(param);
    LOGI("进入线程:param:id=%d,msg=%s", params->id, params->msg);
    //此处可以执行耗时操作
    //usleep(5*1000*1000);//单位微秒
    sleep(3);//单位秒

    //用完记得释放
    delete params;
    LOGI("线程结束");

    pthread_exit(0);//显式线程退出，就不用return了
    //return nullptr;//如果没有显示退出线程，那么在return后线程也就退出了

}

static void *workInThread2(void *param) {//加上static是为了避免与其他文件产生同名

    ThreadParam *params = static_cast<ThreadParam *>(param);
    LOGI("进入线程:param:id=%d,msg=%s", params->id, params->msg);
    struct timeval begin;
    gettimeofday(&begin, nullptr);
    LOGI("begin time: %lld", begin.tv_sec);//时间戳，秒
    sleep(3);//单位秒

    struct timeval end;
    gettimeofday(&end, nullptr);
    LOGI("end time: %lld", end.tv_sec);
    LOGI("time use %d s", (end.tv_sec - begin.tv_sec));

    return params->msg;//如果没有显示退出线程，那么在return后线程也就退出了

}

extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libnative_JniPthread_createThread(
        JNIEnv *env,
        jclass clazz//注意静态方法与普通方法的区别就是jobject变成了jclass
) {

    pthread_t pthread;
    ThreadParam *threadParam = new ThreadParam;//这里必须得new一个，放置函数出栈时被释放
    threadParam->id = 123;
    strcpy(threadParam->msg, "hello msg");
    //创建线程，第一个参数为线程句柄；第二个为线程的配置，可为空；第三个则是线程执行函数的指针；第四个传递给线程执行函数的参数，可任意指定，也可为空
    int ret = pthread_create(&pthread, nullptr, workInThread, threadParam);
    if (ret == 0) {
        LOGI("线程创建成功");//不同于java的start,线程创建成功就立马执行了
    } else {
        LOGE("线程创建失败");

    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libnative_JniPthread_joinThread(
        JNIEnv *env,
        jclass clazz//注意静态方法与普通方法的区别就是jobject变成了jclass
) {

    pthread_t pthread;
    ThreadParam *threadParam = new ThreadParam;//这里必须得new一个，放置函数出栈时被释放
    threadParam->id = 123;
    strcpy(threadParam->msg, "hello msg");
    //创建线程，第一个参数为线程句柄；第二个为线程的配置，可为空；第三个则是线程执行函数的指针；第四个传递给线程执行函数的参数，可任意指定，也可为空
    int ret = pthread_create(&pthread, nullptr, workInThread2, threadParam);
    if (ret == 0) {
        LOGI("线程创建成功");//不同于java的start,线程创建成功就立马执行了
    } else {
        LOGE("线程创建失败");

    }

    void *result = nullptr;

    //join会挂起线程等待线程执行完毕,因此在java主线程可以感觉到停顿
    pthread_join(pthread, &result);

    LOGI("线程返回:%s", result);//线程返回:hello msg
}


pthread_mutex_t mutex;//锁
pthread_cond_t cond;//条件
pthread_t waitHandle;
pthread_t notifyHandle;
int flag = 0;

static void *waitThread(void *) {


    pthread_mutex_lock(&mutex);
    LOGI("waitThread lock");

    while (flag == 0) {
        LOGI("waitThread waiting");
        pthread_cond_wait(&cond, &mutex);//这一步会等待信号，同时将锁释放,在返回时会重新加锁
    }


    pthread_mutex_unlock(&mutex);
    LOGI("waitThread unlock");

    return nullptr;
}

static void *notifyThread(void *) {

    pthread_mutex_lock(&mutex);
    LOGI("notifyThread lock");
    flag = 1;
    LOGI("notifyThread flag=1");
    pthread_mutex_unlock(&mutex);
    LOGI("notifyThread unlock");

    pthread_cond_signal(&cond);//唤醒等待的线程
    LOGI("notifyThread signal");
    return nullptr;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libnative_JniPthread_waitThread(
        JNIEnv *env,
        jclass clazz//注意静态方法与普通方法的区别就是jobject变成了jclass
) {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond, nullptr);

    pthread_create(&waitHandle, nullptr, waitThread, nullptr);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libnative_JniPthread_notifyThread(
        JNIEnv *env,
        jclass clazz//注意静态方法与普通方法的区别就是jobject变成了jclass
) {

    pthread_create(&notifyHandle, nullptr, notifyThread, nullptr);
}

std::queue<int> data;//存放物资
pthread_mutex_t mutex2;
pthread_cond_t crod2;

static void *productThread(void *) {
    while (data.size() < 10) {
        pthread_mutex_lock(&mutex2);
        LOGI("生产物资");
        data.push(1);
        if (data.size() > 0) {
            LOGI("等待消费");
            pthread_cond_signal(&crod2);
        }

        pthread_mutex_unlock(&mutex2);
        sleep(3);
    }

    pthread_exit(0);
}

static void *consumerThread(void *) {


    while (true) {
        pthread_mutex_lock(&mutex2);
        if (data.size() > 0) {
            LOGD("消费物资");
            data.pop();
        } else {
            LOGD("等待生产");
            pthread_cond_wait(&crod2, &mutex2);
        }
        pthread_mutex_unlock(&mutex2);

        sleep(1);
    }

    pthread_exit(0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libnative_JniPthread_productConsumerThread(
        JNIEnv *env,
        jclass clazz//注意静态方法与普通方法的区别就是jobject变成了jclass
) {

    pthread_mutex_init(&mutex2, nullptr);
    pthread_cond_init(&crod2, nullptr);


    pthread_t productHandle;
    pthread_t consumerHandle;
    pthread_create(&productHandle, nullptr, productThread, nullptr);
    pthread_create(&consumerHandle, nullptr, consumerThread, nullptr);
}