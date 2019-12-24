//
// Created by hwj on 19-12-24.
//

#include "ALog.h"

bool m_log_switch=true;
void setLogSwitch(bool bSwitch){
    m_log_switch=bSwitch;
}
void LOGV(const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    if (m_log_switch) __android_log_vprint(ANDROID_LOG_VERBOSE, DEFAULT_LOG_TAG, fmt, arg);
    va_end(arg);
}

void LOGTV(const char* tag,const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    if (m_log_switch) __android_log_vprint(ANDROID_LOG_VERBOSE, tag, fmt, arg);
    va_end(arg);

}
void LOGD(const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    if (m_log_switch) __android_log_vprint(ANDROID_LOG_DEBUG, DEFAULT_LOG_TAG, fmt, arg);
    va_end(arg);

}

void LOGTD(const char* tag,const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    if (m_log_switch) __android_log_vprint(ANDROID_LOG_DEBUG, tag, fmt, arg);
    va_end(arg);

}
void LOGI(const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    if (m_log_switch) __android_log_vprint(ANDROID_LOG_INFO, DEFAULT_LOG_TAG, fmt, arg);
    va_end(arg);

}

void LOGTI(const char* tag,const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    if (m_log_switch) __android_log_vprint(ANDROID_LOG_INFO, tag, fmt, arg);
    va_end(arg);

}

void LOGW(const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    if (m_log_switch) __android_log_vprint(ANDROID_LOG_WARN, DEFAULT_LOG_TAG, fmt, arg);
    va_end(arg);

}
void LOGTW(const char* tag,const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    if (m_log_switch) __android_log_vprint(ANDROID_LOG_WARN, tag, fmt, arg);
    va_end(arg);

}
void LOGE(const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    if (m_log_switch) __android_log_vprint(ANDROID_LOG_ERROR, DEFAULT_LOG_TAG, fmt, arg);
    va_end(arg);

}
void LOGTE(const char* tag,const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    if (m_log_switch) __android_log_vprint(ANDROID_LOG_ERROR, tag, fmt, arg);
    va_end(arg);

}
void LOGF(const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    if (m_log_switch) __android_log_vprint(ANDROID_LOG_FATAL, DEFAULT_LOG_TAG, fmt, arg);
    va_end(arg);

}
void LOGTF(const char* tag,const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    if (m_log_switch) __android_log_vprint(ANDROID_LOG_FATAL, tag, fmt, arg);
    va_end(arg);

}
