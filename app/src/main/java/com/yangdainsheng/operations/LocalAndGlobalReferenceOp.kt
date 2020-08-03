package com.yangdainsheng.operations

class LocalAndGlobalReferenceOp {

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }

    external fun errorCacheUseLocalReference():String
    external fun cacheWithGlobalReference():String
    external fun useWeakGlobalReference()
    external fun useLocalReferenceManageFuntions()

}