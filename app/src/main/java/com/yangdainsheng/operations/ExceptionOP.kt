package com.yangdainsheng.operations

class ExceptionOP {
    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }

    /**
     * 调用operation() 并处理异常
     */
    external fun nativeInvokeJavaException()

    /**
     * native抛出异常给java
     */
    external fun nativeThrowException()

    /**
     * 调用callback抛出异常
     */
    external fun doit()

    /**
     * native调用会抛出异常
     */
    private fun operation(): Int {
        return 2 / 0
    }

    /**
     * Native 调用  Java 方式时，导致异常了并不会立即终止 Native 方法的执行
     *
     * @throws NullPointerException
     */
    @Throws(NullPointerException::class)
    private fun callback() {
        throw NullPointerException("CatchThrow.callback by Native Code")
    }
}