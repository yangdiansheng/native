//
// Created by 杨殿生 on 2020/8/4.
//

#include <jni.h>
#include <logutil.h>
#include <pthread.h>
#include <queue>
#include <unistd.h>

using namespace std;
std::queue<int> data;

pthread_mutex_t dataMutex;
pthread_cond_t dataCond;

void *productThread(void *);
void *consumerThread(void *);

extern "C"
JNIEXPORT void JNICALL
Java_com_yangdainsheng_operations_ThreadOp_productAndConsumer(JNIEnv *env, jobject thiz) {
    pthread_mutex_init(&dataMutex, nullptr);
    pthread_cond_init(&dataCond, nullptr);
    pthread_t productHandle;
    pthread_t consumerHandle;
    pthread_create(&productHandle, nullptr,productThread, nullptr);
    pthread_create(&consumerHandle, nullptr, consumerThread, nullptr);
}

void *productThread(void *){
    while(data.size() < 10){
        pthread_mutex_lock(&dataMutex);
        LOGD("生产物资");
        data.push(1);
        if(data.size() > 0){
            LOGD("等待消费");
            pthread_cond_signal(&dataCond);
        }
        pthread_mutex_unlock(&dataMutex);
        sleep(3);
    }
    pthread_exit(0);
}

void *consumerThread(void *){
    while(1){
        pthread_mutex_lock(&dataMutex);
        if(data.size() > 0){
            LOGD("消费物品");
            data.pop();
        } else {
            LOGD("等待物品");
            pthread_cond_wait(&dataCond,&dataMutex);
        }
        pthread_mutex_unlock(&dataMutex);
        sleep(1);
    }
    pthread_exit(0);
}

