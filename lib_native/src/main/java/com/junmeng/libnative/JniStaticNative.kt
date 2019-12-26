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
    external fun stringFromJNI(s: String): String


    /**
     * 演示JNI_COMMIT,如果字节产生了副本，则Native层的修改会影响java层，同时副本不会释放，如果没产生复制，自然会影响到java层
     */
    external fun byteReleaseWithCommit(bs: ByteArray)

    /**
     * 演示JNI_ABORT,如果字节产生了副本，则Native层的修改不会影响java层，如果没产生复制，自然会影响到java层
     */
    external fun byteReleaseWithAbort(bs: ByteArray)

    /**
     * 演示NULL,如果字节产生了副本，则Native层的修改会影响java层，如果没产生复制，自然会影响到java层
     */
    external fun byteReleaseWithNull(bs: ByteArray)


}