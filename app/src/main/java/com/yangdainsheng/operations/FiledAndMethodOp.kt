package com.yangdainsheng.operations

import com.yangdainsheng.bean.Animal
import com.yangdainsheng.bean.ICallBack

class FiledAndMethodOp {

    external fun callFiled(animal:Animal)
    external fun callStaticFiled(animal:Animal)
    external fun callIntanceMethod(animal: Animal)
    external fun callStaticMethod(animal: Animal):String
    external fun callCallback(call: ICallBack)
}