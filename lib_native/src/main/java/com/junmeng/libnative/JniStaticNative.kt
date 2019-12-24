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


    /**
     * 动态注册演示（比静态注册速度快，静态注册有个查找的过程），在JNI_OnLoad中实现动态注册
     */
    external fun dynamicRegister(i:Int):Int


}