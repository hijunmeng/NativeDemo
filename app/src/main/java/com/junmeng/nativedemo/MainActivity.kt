package com.junmeng.nativedemo

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import com.junmeng.libnative.*
import com.junmeng.libnative.bean.XY
import kotlinx.android.synthetic.main.activity_main.*
import java.lang.IllegalArgumentException

class MainActivity : AppCompatActivity() {
    val TAG = MainActivity::class.java.toString()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)


        //静态注册演示
        //普通方式
        sample_text.text = JniNative.getInstance()?.stringFromJNI()
        //静态方式
        var s1 = System.currentTimeMillis()
        JniStaticNative.stringFromJNI("static")
        var e1 = System.currentTimeMillis()
        Log.i(TAG, "静态注册方式第一次调用耗时（ms）：" + (e1 - s1))
        var s2 = System.currentTimeMillis()
        JniStaticNative.stringFromJNI("static")
        var e2 = System.currentTimeMillis()
        Log.i(TAG, "静态注册方式第二次调用耗时（ms）：" + (e2 - s2))//第二次调用会比首次快很多


        //传递对象演示
        var xy = JniObject.change(XY())
        Log.i(TAG, "传递对象xy={" + xy.x + "," + xy.y + "}")//输出{1,1}

        //动态注册演示
        var s3 = System.currentTimeMillis()
        var i = JniDynamic.addone(2)
        var e3 = System.currentTimeMillis()
        Log.i(TAG, "动态注册方式首次调用耗时（ms）：" + (e3 - s3))//比静态注册会快一些
        var s4 = System.currentTimeMillis()
        JniDynamic.stringFromJNI("dynamic")
        var e4 = System.currentTimeMillis()
        Log.i(TAG, "动态注册方式首次调用耗时（ms）：" + (e4 - s4))


        //字节操作演示
        //由于长度过小，Native层产生副本
        var ba = ByteArray(5)
        JniStaticNative.byteReleaseWithCommit(ba)
        Log.i(TAG, "byteReleaseWithCommit：[0]=" + ba[0])//[0]=2
        ba = ByteArray(5)
        JniStaticNative.byteReleaseWithAbort(ba)
        Log.i(TAG, "byteReleaseWithAbort：[0]=" + ba[0])//[0]=0
        ba = ByteArray(5)
        JniStaticNative.byteReleaseWithNull(ba)
        Log.i(TAG, "byteRealeseWithNull：[0]=" + ba[0])//[0]=2
        //由于长度过长，Native层未产生副本
        ba = ByteArray(12 * 1024)
        JniStaticNative.byteReleaseWithCommit(ba)
        Log.i(TAG, "byteReleaseWithCommit：[0]=" + ba[0])//[0]=2
        ba = ByteArray(12 * 1024)
        JniStaticNative.byteReleaseWithAbort(ba)
        Log.i(TAG, "byteReleaseWithAbort：[0]=" + ba[0])//[0]=2
        ba = ByteArray(12 * 1024)
        JniStaticNative.byteReleaseWithNull(ba)
        Log.i(TAG, "byteRealeseWithNull：[0]=" + ba[0])//[0]=2
        JniStaticNative.byteCopy(byteArrayOf(0x01, 0x02))


        //回调演示
        JniCallback.callback(object : ICallback {
            override fun cb(s: String) {
                Log.i(TAG, "current_thread_id=" + Thread.currentThread().id + ",callback＝" + s)

            }
        })

        JniCallback.threadCallback(object : ICallback {
            override fun cb(s: String) {
                Log.i(TAG, "current_thread_id=" + Thread.currentThread().id + ",callback＝" + s)

            }
        })


        //演示三种引用类型
        var sr: String = JniReference.localReference()
        Log.i(TAG, "localReference=" + sr)

        JniReference.globalReference()
        JniReference.globalReference()

        JniReference.weakReference()
        JniReference.weakReference()

        // var ret=JniReference.errorWithTooManyLocalRef()//此句无法正常执行
        // Log.i(TAG,"errorWithTooManyLocalRef ret="+ret)//你会发现这句ｌｏｇ无法被执行到


        JniException.invokeJavaException()

        try {
            JniException.throwException()
        } catch (e: IllegalArgumentException) {
            Log.e(TAG, "throwException:" + e.message)
        }


    }

    fun onClickTest(view: View) {
        JniReference.globalReference()
        JniReference.weakReference()
    }


}

