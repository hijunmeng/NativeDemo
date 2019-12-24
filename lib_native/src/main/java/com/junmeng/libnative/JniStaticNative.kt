package com.junmeng.libnative

/**
 * 演示静态方法
 */
object JniStaticNative {

    init {
        System.loadLibrary("native-lib")
    }


    external fun stringFromJNI(): String


}