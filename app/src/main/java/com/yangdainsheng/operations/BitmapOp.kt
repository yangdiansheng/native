package com.yangdainsheng.operations

import android.graphics.Bitmap

class BitmapOp {
    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }

    external fun callNativeMirrorBitmap(bitMap: Bitmap):Bitmap?
    external fun callNativeRotateBitmap(bitMap: Bitmap):Bitmap?
    external fun callNativeConvertBitmap(bitMap: Bitmap):Bitmap?
}