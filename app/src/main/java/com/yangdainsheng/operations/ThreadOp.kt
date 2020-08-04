package com.yangdainsheng.operations

import android.util.Log
import com.yangdainsheng.utils.LogUtil

class ThreadOp {
    external fun createNativeThread()
    external fun createNativeThreadWithArgs()
    external fun joinNativeThread()
    external fun nativeInit()
    external fun nativeFree()
    external fun waitNativeThread()
    external fun waitNotifyThread()
    external fun productAndConsumer()

    /**
     * 打印线程名称，并且模拟耗时任务
     */
    private fun printThreadName() {
        LogUtil.d("print thread name current thread name is " + Thread.currentThread().name)
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
        LogUtil.d("native msg is $msg")
        LogUtil.d("print native msg current thread name is " + Thread.currentThread().name)
    }
}