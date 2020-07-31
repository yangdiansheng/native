package com.yangdainsheng.operations

import com.yangdainsheng.bean.Animal

class InvokeConstructorOp {
    external fun invokeStringConstructor():String
    external fun invokeAnimalConstructor():Animal

    // 调用 allocObject 方法来构造一个类
    external fun allocObjectConstructor(): Animal

    // 调用父类的方法
    external fun callSuperMethod()
}