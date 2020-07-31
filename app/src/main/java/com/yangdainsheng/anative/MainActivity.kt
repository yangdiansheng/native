package com.yangdainsheng.anative

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.yangdainsheng.bean.Animal
import com.yangdainsheng.bean.ICallBack
import com.yangdainsheng.operations.*
import com.yangdainsheng.utils.LogUtil
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    val jniBasicType = JNIBasicType()
    val stringType = StringType()
    val filedAndMethodOp = FiledAndMethodOp()
    val threadOp = ThreadOp()
    val invokeConstructorOp = InvokeConstructorOp()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        sample_text.text = stringFromJNI()
        tv_int.text = "callNativeInt = ${jniBasicType.callNativeInt(1)}\n" +
                "callNativeByte = ${jniBasicType.callNativeByte(2)}\n" +
                "callNativeChar = ${jniBasicType.callNativeChar('a')}\n" +
                "callNativeShort = ${jniBasicType.callNativeShort(5)}\n" +
                "callNativeLong = ${jniBasicType.callNativeLong(10L)}\n" +
                "callNativeFloat = ${jniBasicType.callNativeFloat(2.0f)}\n" +
                "callNativeDouble = ${jniBasicType.callNativeDouble(12.0)}\n" +
                "callNativeBoolean = ${jniBasicType.callNativeBoolean(false)}\n"
        tv_string.text = "getAndReleaseString = ${stringType.getAndReleaseString("abcdefg")}\n" +
                "reverseString = ${stringType.reverseString("abcdefg")}\n" +
                "getHalfString = ${stringType.getHalfString("abcdefg")}\n" +
                "callNativeStringArray = ${stringType.callNativeStringArray(arrayOf("aaaa","bbbb","cccc"))}\n"
        val animal = Animal()
        animal.name = "java animal"
        Animal.num = 3333
        filedAndMethodOp.callFiled(animal)
        filedAndMethodOp.callStaticFiled(animal)
        tv_object.text = "callFiled = ${animal.name}\n" +
                "callStaticFiled = ${Animal.num}\n" +
                "callIntanceMethod = ${filedAndMethodOp.callIntanceMethod(animal)}\n" +
                "callStaticMethod = ${filedAndMethodOp.callStaticMethod(animal)}\n"
        tv_callback.setOnClickListener {
            filedAndMethodOp.callCallback(object :ICallBack{
                override fun callBackMethod() {
                    LogUtil.d("callBackMethod")
                }
            })
        }
        tv_thread_create.setOnClickListener {
            threadOp.nativeInit()
            threadOp.createNativeThread()
//            threadOp.nativeFree()
        }
        val animal2 = invokeConstructorOp.invokeAnimalConstructor()
        val animal3 = invokeConstructorOp.allocObjectConstructor()
        tv_constructor.text = "invokeStringConstructor = ${invokeConstructorOp.invokeStringConstructor()}\n" +
                "invokeAnimalConstructor = ${animal2.name}\n" +
                "allocObjectConstructor = ${animal3.name}\n" +
                "callSuperMethod = ${invokeConstructorOp.callSuperMethod()}\n"
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    //静态注册
    external fun getString(): String

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}
