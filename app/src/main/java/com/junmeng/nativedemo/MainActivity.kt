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



        //静态注册演示
        //普通方式
        sample_text.text =JniNative.getInstance()?.stringFromJNI()
        //静态方式
        var s1=System.currentTimeMillis()
        JniStaticNative.stringFromJNI("static")
        var e1=System.currentTimeMillis()
        Log.i(TAG,"静态注册方式第一次调用耗时（ms）："+(e1-s1))
        var s2=System.currentTimeMillis()
        JniStaticNative.stringFromJNI("static")
        var e2=System.currentTimeMillis()
        Log.i(TAG,"静态注册方式第二次调用耗时（ms）："+(e2-s2))


        //传递对象演示
        var xy=JniObject.change(XY())
        Log.i(TAG,"传递对象xy={"+xy.x+","+xy.y+"}")

        //动态注册演示
        var s3=System.currentTimeMillis()
        var i=JniDynamic.addone(2)
        var e3=System.currentTimeMillis()
        Log.i(TAG,"动态注册方式首次调用耗时（ms）："+(e3-s3))
        var s4=System.currentTimeMillis()
        JniDynamic.stringFromJNI("dynamic")
        var e4=System.currentTimeMillis()
        Log.i(TAG,"动态注册方式首次调用耗时（ms）："+(e4-s4))












    }


}
