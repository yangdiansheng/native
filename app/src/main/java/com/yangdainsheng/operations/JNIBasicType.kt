package com.yangdainsheng.operations

class JNIBasicType {
    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }

    external fun callNativeInt(num:Int): Int
    external fun callNativeByte(b:Byte): Byte
    external fun callNativeChar(a:Char): Char
    external fun callNativeShort(s:Short): Short
    external fun callNativeLong(l:Long): Long
    external fun callNativeFloat(f:Float): Float
    external fun callNativeDouble(d:Double): Double
    external fun callNativeBoolean(b:Boolean): Boolean
}