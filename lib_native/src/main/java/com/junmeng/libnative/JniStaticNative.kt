package com.junmeng.libnative

/**
 * 演示静态方法
 */
object JniStaticNative {

    init {
        System.loadLibrary("native-lib")
    }

    /**
     * 静态注册演示，native会有对应的函数如Java_com_junmeng_libnative_JniStaticNative_stringFromJNI
     */
    external fun stringFromJNI(): String



}