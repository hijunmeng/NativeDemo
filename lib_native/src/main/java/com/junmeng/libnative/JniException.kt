package com.junmeng.libnative

object JniException {
    init {
        System.loadLibrary("native-lib")
    }

    /**
     * 在native层执行到java层的异常时能检测到并清除掉，使得程序不会直接崩溃
     */
    external fun invokeJavaException()

    /**
     * 在native层抛出一个异常给java层
     */
    external fun throwException()


    /**
     * 此方法会发生异常
     */
    fun exception(): Int {
        return 1 / 0
    }
}