package com.yangdainsheng.operations

import android.util.Log

class ThreadOp {
    external fun createNativeThread()
    external fun nativeInit()
    external fun nativeFree()

    /**
     * 打印线程名称，并且模拟耗时任务
     */
    private fun printThreadName() {
        Log.d("yyy","print thread name current thread name is " + Thread.currentThread().name)
        try {
            Thread.sleep(5000)
        } catch (e: InterruptedException) {
            e.printStackTrace()
        }
    }

    /**
     * Native 回到到 Java 的方法，打印当前线程名字
     * @param msg
     */
    private fun printNativeMsg(msg: String) {
        Log.d("yyy","native msg is $msg")
        Log.d("yyy", "print native msg current thread name is " + Thread.currentThread().name)
    }
}