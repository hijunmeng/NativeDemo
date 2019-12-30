package com.junmeng.libnative

import java.lang.IllegalArgumentException

/**
 * 如果想在native层直接使用jclass的话，则不能使用object类型，必须为companion object
 */
class JniException {
    companion object{
        init {
            System.loadLibrary("native-lib")
        }

        /**
         * 在native层执行到java层的异常时能检测到并清除掉，使得程序不会直接崩溃
         */
        @JvmStatic//如果想在native层直接使用jclass,则必须加上此注解
        external fun invokeJavaException()

        /**
         * 在native层抛出一个异常给java层
         */
        @JvmStatic
        @Throws(IllegalArgumentException::class)
        external fun throwException()
    }



    /**
     * 此方法会发生异常
     */
    fun exception(): Int {
        return 1 / 0
    }
}