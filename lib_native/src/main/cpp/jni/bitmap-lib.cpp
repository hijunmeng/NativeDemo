#include <jni.h>
#include <ALog.h>
#include <android/bitmap.h>
#include <cstring>


jobject generateBitmap(JNIEnv *pEnv, int width, int height);

extern "C"
JNIEXPORT jobject JNICALL
Java_com_junmeng_libnative_JniBitmap_mirrorBitmap(
        JNIEnv *env,
        jclass clazz,//注意静态方法与普通方法的区别就是jobject变成了jclass
        jobject jbitmap
) {

    AndroidBitmapInfo bitmapInfo;
    AndroidBitmap_getInfo(env, jbitmap, &bitmapInfo);
    LOGI("bitmap width=%d,height=%d", bitmapInfo.width, bitmapInfo.height);

    void *bitmapPixels;
    AndroidBitmap_lockPixels(env, jbitmap, &bitmapPixels);//注意lock与unlock是成对出现的

    uint32_t newWidth = bitmapInfo.width;
    uint32_t newHeight = bitmapInfo.height;

    uint32_t *newBitmapPixels = new uint32_t[newWidth * newHeight];

    //图像本来是二维数组，但bitmapPixels是存储在一维数组中的，因此对每一行进行翻转需要自己去分割
    int index = 0;
    for (int i = 0; i < newHeight; i++) {//按行分割
        for (int j = newWidth - 1; j >= 0; j--) {
            uint32_t pixel = ((uint32_t *) bitmapPixels)[index++];
            newBitmapPixels[newWidth * i + j] = pixel;
        }

    }
    AndroidBitmap_unlockPixels(env, jbitmap);


    jobject newBitmap = generateBitmap(env, newWidth, newHeight);

    void *resultBitmapPixels;
    AndroidBitmap_lockPixels(env, newBitmap, &resultBitmapPixels);
    //将新的镜像图拷贝进resultBitmapPixels
    memcpy(resultBitmapPixels, newBitmapPixels, sizeof(uint32_t) * newWidth * newHeight);
    AndroidBitmap_unlockPixels(env, newBitmap);

    delete[] newBitmapPixels;

    return newBitmap;

}


/**
 * 生成Bitmap对象
 * @param pEnv
 * @param width  指定宽度
 * @param height 指定高度
 * @return
 */
jobject generateBitmap(JNIEnv *pEnv, int width, int height) {

    jclass bitmapCls = pEnv->FindClass("android/graphics/Bitmap");
    jmethodID createMid = pEnv->GetStaticMethodID(bitmapCls, "createBitmap",
                                                  "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
    jstring config = pEnv->NewStringUTF("ARGB_8888");
    jclass confCls = pEnv->FindClass("android/graphics/Bitmap$Config");

    jmethodID mid2 = pEnv->GetStaticMethodID(confCls, "valueOf",
                                             "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;");

    jobject bitmapConfig = pEnv->CallStaticObjectMethod(confCls, mid2, config);
    jobject newBitmap = pEnv->CallStaticObjectMethod(bitmapCls, createMid, width, height,
                                                     bitmapConfig);
    return newBitmap;
}
