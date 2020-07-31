package com.yangdainsheng.bean

import android.util.Log

class Cat(override var name:String = "") :Animal(name){

    fun getName() = {  "my name is $name" }
}