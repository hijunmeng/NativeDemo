package com.junmeng.libnative

/**
 * 演示三种引用类型
 */
object JniReference {


    init {
        System.loadLibrary("native-lib")
    }

    /**
     * 本地引用在函数返回时会被自动释放，但还是应该在其无用时就将其释放，否则在函数返回前这块内存相当于泄露了
     */
    external fun localReference():String


    /**
     * 全局引用除非手动释放，否则不会被回收
     */
    external fun globalReference():String

    /**
     * 弱全局引用在ｇｃ执行时有可能被回收，因此在使用弱全局引用时需要判断引用的对象是否为空
     */
    external fun weakReference():String

    /**
     *
     * 本地引用个数不宜过多，一般不能超过５１２个，这也说明了无用的本地引用要及时释放
     * 本方法实测会有一些异常情况，暂时不知原因
     */
    external fun errorWithTooManyLocalRef():Int
}