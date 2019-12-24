package com.junmeng.libnative

/**
 * 演示普通方法
 */
class JniNative private constructor() {


    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }

        private var instance: JniNative? = null

        fun getInstance(): JniNative? {
            if (instance == null) {
                synchronized(JniNative::class.java) { instance = JniNative() }
            }
            return instance
        }
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
}