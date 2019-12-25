package com.junmeng.nativedemo

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.junmeng.libnative.JniDynamic
import com.junmeng.libnative.JniNative
import com.junmeng.libnative.JniObject
import com.junmeng.libnative.JniStaticNative
import com.junmeng.libnative.bean.XY
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    val TAG=MainActivity::class.java.toString()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
//        sample_text.text = JniNative.getInstance()?.stringFromJNI()
        //sample_text.text = JniStaticNative.stringFromJNI()

        var s1=System.currentTimeMillis()
        JniStaticNative.stringFromJNI()
        var e1=System.currentTimeMillis()
        Log.i(TAG,"耗时s="+(e1-s1))
        var s2=System.currentTimeMillis()
        JniStaticNative.stringFromJNI()
        var e2=System.currentTimeMillis()
        Log.i(TAG,"耗时s="+(e2-s2))

        var s=System.currentTimeMillis()
        var i=JniDynamic.addone(2)
        var e=System.currentTimeMillis()
        Log.i(TAG,"耗时d="+(e-s))
        sample_text.text =JniDynamic.stringFromJNI("hello")

        var xy=JniObject.change(XY())
        Log.i(TAG,"xy={"+xy.x+","+xy.y+"}")



    }


}
