package com.yangdainsheng.operations

class StringType {
    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }

    external fun getAndReleaseString(s:String): String
    external fun reverseString(s:String): String
    external fun getHalfString(s:String): String
    external fun callNativeStringArray(arr:Array<String>): String
}