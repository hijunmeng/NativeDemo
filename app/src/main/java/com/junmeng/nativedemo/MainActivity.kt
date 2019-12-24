package com.junmeng.nativedemo

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.junmeng.libnative.JniNative
import com.junmeng.libnative.JniStaticNative
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
//        sample_text.text = JniNative.getInstance()?.stringFromJNI()
        sample_text.text = JniStaticNative.stringFromJNI()
    }


}
