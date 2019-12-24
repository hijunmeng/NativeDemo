//
// 日志工具
// Created by hwj on 19-12-24.
//

#ifndef NATIVEDEMO_ALOG_H
#define NATIVEDEMO_ALOG_H

#include <android/log.h>

#define  DEFAULT_LOG_TAG    "yourTagName"
/**
 * 设置是否打印日志到logcat
 * @param bSwitch
 */
void setLogSwitch(bool bSwitch);

void LOGV(const char *fmt, ...);
void LOGTV(const char* tag,const char *fmt, ...);
void LOGD(const char *fmt, ...) ;
void LOGTD(const char* tag,const char *fmt, ...);
void LOGI(const char *fmt, ...) ;
void LOGTI(const char* tag,const char *fmt, ...);
void LOGW(const char *fmt, ...) ;
void LOGTW(const char* tag,const char *fmt, ...) ;
void LOGE(const char *fmt, ...);
void LOGTE(const char* tag,const char *fmt, ...) ;
void LOGF(const char *fmt, ...);
void LOGTF(const char* tag,const char *fmt, ...) ;

#endif //NATIVEDEMO_ALOG_H
