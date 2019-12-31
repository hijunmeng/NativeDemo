package com.junmeng.libnative

import android.graphics.Bitmap

/**
 * 此演示需要在ＣMakeLists.txt中增加库jnigraphics
 * 如果想在native层直接使用jclass的话，则不能使用object类型，必须为companion object
 */
class JniBitmap {
    companion object {
        init {
            System.loadLibrary("native-lib")
        }

        /**
         * 将图片镜像翻转
         */
        @JvmStatic//如果想在native层直接使用jclass,则必须加上此注解
        external fun mirrorBitmap(bitmap: Bitmap): Bitmap


    }


}