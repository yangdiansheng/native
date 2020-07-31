package com.yangdainsheng.bean

import android.util.Log

class Animal {

    var name:String = ""

    companion object{
        var num = 0

        @JvmStatic
        fun staticMethod(string: String):String{
            return "staticMethod string = $string"
        }

        @JvmStatic
        fun staticMethod(string: Array<String>,num:Int):String{
            return "staticMethod string arr = ${string[0]} num = $num"
        }
    }

    fun instanceMethod(num:Int){
        Log.d("yyy","instanceMethod num=$num")
    }


}