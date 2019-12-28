package com.junmeng.libnative

object JniCallback {

    init {
        System.loadLibrary("native-lib")
    }

    /**
     * 演示普通回调
     */
    external fun callback(callback:ICallback)

    /**
     * 演示在线程中回调
     */
    external fun threadCallback(callback:ICallback)
}