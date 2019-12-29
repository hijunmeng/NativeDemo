//
// Created by hwj on 19-12-29.
//

#include "GJvm.h"


static JavaVM* gJvm=nullptr;

void setJvm(JavaVM * jvm){
    gJvm=jvm;
}

JavaVM* getJvm(){
    return gJvm;
}
