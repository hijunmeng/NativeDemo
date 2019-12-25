package com.junmeng.libnative

import com.junmeng.libnative.bean.XY

/**
 * 演示互相传递对象，但不推荐使用此种方式，因为传递对象的话在Native层解析对象时会进行多次jni调用，降低性能
 */
@Deprecated("传递对象不推荐使用")
object JniObject {

    init {
        System.loadLibrary("native-lib")
    }


    external fun change(xy: XY): XY
}