//
// Created by hwj on 19-12-29.
//

#ifndef NATIVEDEMO_GJVM_H
#define NATIVEDEMO_GJVM_H


#include <jni.h>

void setJvm(JavaVM * jvm);

JavaVM* getJvm();

#endif //NATIVEDEMO_GJVM_H
