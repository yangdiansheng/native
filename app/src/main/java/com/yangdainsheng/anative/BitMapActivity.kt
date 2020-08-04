package com.yangdainsheng.anative

import android.app.Activity
import android.content.Intent
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.yangdainsheng.bean.Animal
import com.yangdainsheng.bean.ICallBack
import com.yangdainsheng.operations.*
import com.yangdainsheng.utils.LogUtil
import kotlinx.android.synthetic.main.activity_bitmap.*

class BitMapActivity : AppCompatActivity() {

    val bitmapOp = BitmapOp()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_bitmap)
        val bitmap = BitmapFactory.decodeResource(resources,R.mipmap.elephant)
        tv_mirror.setOnClickListener {
            val bitmapMirror = bitmapOp.callNativeMirrorBitmap(bitmap)
            bitmapMirror?.let {
                iv_mirror.setImageBitmap(it)
            }
        }
        tv_rotate.setOnClickListener {
            val bitmapMirror = bitmapOp.callNativeRotateBitmap(bitmap)
            bitmapMirror?.let {
                iv_mirror.setImageBitmap(it)
            }
        }
        tv_covert.setOnClickListener {
            val bitmapMirror = bitmapOp.callNativeConvertBitmap(bitmap)
            bitmapMirror?.let {
                iv_mirror.setImageBitmap(it)
            }
        }
    }

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }

        fun startActivity(activity:Activity){
            val intent = Intent()
            intent.setClass(activity,BitMapActivity::class.java)
            activity.startActivity(intent)
        }
    }
}
