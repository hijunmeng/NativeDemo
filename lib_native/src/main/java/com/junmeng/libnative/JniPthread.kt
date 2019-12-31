package com.junmeng.libnative

import java.lang.IllegalArgumentException

/**
 * 如果想在native层直接使用jclass的话，则不能使用object类型，必须为companion object
 */
class JniPthread {
    companion object{
        init {
            System.loadLibrary("native-lib")
        }

        /**
         * 创建并开启线程
         */
        @JvmStatic//如果想在native层直接使用jclass,则必须加上此注解
        external fun createThread()

        /**
         * 通过join等待线程执行完返回结果
         */
        @JvmStatic
        external fun joinThread()


        /**
         * 创建并开启线程
         */
        @JvmStatic//如果想在native层直接使用jclass,则必须加上此注解
        external fun waitThread()

        /**
         * 通过join等待线程执行完返回结果
         */
        @JvmStatic
        external fun notifyThread()



        /**
         * 生产消费模型
         */
        @JvmStatic
        external fun productConsumerThread()
    }




}