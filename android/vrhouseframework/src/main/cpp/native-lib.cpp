#include <jni.h>
#include <string>
#include <opencv2/opencv.hpp>
#include "../../../../../Shared/SheetDetection.hpp"
#include <android/bitmap.h>
#include <android/log.h>

using namespace std;

SheetDetection sd;

Mat *nBitmapToMat2
        (JNIEnv *env, jobject bitmap, bool needUnPremultiplyAlpha);

jobject mat_to_bitmap(JNIEnv *env, Mat &src, jobject bitmap_config, bool needPremultiplyAlpha);


extern "C" JNIEXPORT jfloatArray JNICALL
Java_co_netguru_vrhouseframework_NativeRecognizer_recognizePlane(
        JNIEnv *env,
        jobject _this,
        jobject bitmap) {

    Mat *input = nBitmapToMat2(env, bitmap, false);
    vector<Point> resultVector = sd.findCorners(*input);
    delete input;

    unsigned long resultSize = resultVector.size() * 2;
    jfloatArray result = env->NewFloatArray(static_cast<jsize>(resultSize));
    float *data;
    data = new float[resultSize];
    int i = 0;
    for (auto &point : resultVector) {
        data[i] = point.x;
        data[i + 1] = point.y;
        i += 2;
    }
    env->SetFloatArrayRegion(result, 0, static_cast<jsize>(resultSize), data);
    delete[] data;
    return result;
}

extern "C" JNIEXPORT jobject JNICALL
Java_co_netguru_vrhouseframework_NativeRecognizer_cropSelectedArea(
        JNIEnv *env,
        jobject _this,
        jobject bitmap,
        jfloatArray points) {

    float *corners = env->GetFloatArrayElements(points, 0);
    vector<Point2f> coordinates;
    for (int i = 0; i < env->GetArrayLength(points); i += 2) {
        coordinates.push_back(Point2f(corners[i], corners[i + 1]));
    }
    delete[] corners;
    Mat *input = nBitmapToMat2(env, bitmap, false);
    Mat result = sd.cropSelectedArea(*input, coordinates[0], coordinates[1], coordinates[3],
                                     coordinates[2]);
    delete input;
    coordinates.clear();

    jclass java_bitmap_class = (jclass) env->FindClass("android/graphics/Bitmap");
    jmethodID mid = env->GetMethodID(java_bitmap_class, "getConfig",
                                     "()Landroid/graphics/Bitmap$Config;");
    jobject bitmap_config = env->CallObjectMethod(bitmap, mid);
    jobject _bitmap = mat_to_bitmap(env, result, bitmap_config, false);

    AndroidBitmap_unlockPixels(env, bitmap);

    return _bitmap;
}


Mat *nBitmapToMat2
        (JNIEnv *env, jobject bitmap, bool needUnPremultiplyAlpha) {
    AndroidBitmapInfo info;
    void *pixels = 0;
    Mat *dst;

    try {
        __android_log_write(ANDROID_LOG_DEBUG, "native-lib", "nBitmapToMat");
        CV_Assert(AndroidBitmap_getInfo(env, bitmap, &info) >= 0);
        CV_Assert(info.format == ANDROID_BITMAP_FORMAT_RGBA_8888 ||
                  info.format == ANDROID_BITMAP_FORMAT_RGB_565);
        CV_Assert(AndroidBitmap_lockPixels(env, bitmap, &pixels) >= 0);
        CV_Assert(pixels);
        dst = new Mat(info.height, info.width, CV_8UC4);
        if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
            __android_log_write(ANDROID_LOG_DEBUG, "native-lib",
                                "nBitmapToMat: RGBA_8888 -> CV_8UC4");
            Mat tmp(info.height, info.width, CV_8UC4, pixels);
            if (needUnPremultiplyAlpha) cvtColor(tmp, *dst, COLOR_mRGBA2RGBA);
            else tmp.copyTo(*dst);
        } else {
            __android_log_write(ANDROID_LOG_DEBUG, "native-lib",
                                "nBitmapToMat: RGB_565 -> CV_8UC4");
            Mat tmp(info.height, info.width, CV_8UC2, pixels);
            cvtColor(tmp, *dst, COLOR_BGR5652RGBA);
        }
        AndroidBitmap_unlockPixels(env, bitmap);
        return dst;
    } catch (const cv::Exception &e) {
        AndroidBitmap_unlockPixels(env, bitmap);
        __android_log_print(ANDROID_LOG_ERROR, "native-lib",
                            "nBitmapToMat caught cv::Exception: %s", e.what());
        jclass je = env->FindClass("org/opencv/core/CvException");
        if (!je) je = env->FindClass("java/lang/Exception");
        env->ThrowNew(je, e.what());
        return nullptr;
    } catch (...) {
        AndroidBitmap_unlockPixels(env, bitmap);
        __android_log_print(ANDROID_LOG_ERROR, "native-lib",
                            "nBitmapToMat caught unknown exception (...)");
        jclass je = env->FindClass("java/lang/Exception");
        env->ThrowNew(je, "Unknown exception in JNI code {nBitmapToMat}");
        return nullptr;
    }
}


jobject mat_to_bitmap(JNIEnv *env, Mat &src, jobject bitmap_config, bool needPremultiplyAlpha) {

    jclass java_bitmap_class = (jclass) env->FindClass("android/graphics/Bitmap");
    jmethodID mid = env->GetStaticMethodID(java_bitmap_class,
                                           "createBitmap",
                                           "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");

    jobject bitmap = env->CallStaticObjectMethod(java_bitmap_class,
                                                 mid, src.size().width, src.size().height,
                                                 bitmap_config);
    AndroidBitmapInfo info;
    void *pixels = 0;

    try {
        //validate
        CV_Assert(AndroidBitmap_getInfo(env, bitmap, &info) >= 0);
        CV_Assert(src.type() == CV_8UC1 || src.type() == CV_8UC3 || src.type() == CV_8UC4);
        CV_Assert(AndroidBitmap_lockPixels(env, bitmap, &pixels) >= 0);
        CV_Assert(pixels);

        //type mat
        if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
            Mat tmp(info.height, info.width, CV_8UC4, pixels);
            if (src.type() == CV_8UC1) {
                cvtColor(src, tmp, CV_GRAY2RGBA);
            } else if (src.type() == CV_8UC3) {
                cvtColor(src, tmp, CV_RGB2RGBA);
            } else if (src.type() == CV_8UC4) {
                if (needPremultiplyAlpha) {
                    cvtColor(src, tmp, COLOR_RGBA2mRGBA);
                } else {
                    src.copyTo(tmp);
                }
            }

        } else {
            Mat tmp(info.height, info.width, CV_8UC2, pixels);
            if (src.type() == CV_8UC1) {
                cvtColor(src, tmp, CV_GRAY2BGR565);
            } else if (src.type() == CV_8UC3) {
                cvtColor(src, tmp, CV_RGB2BGR565);
            } else if (src.type() == CV_8UC4) {
                cvtColor(src, tmp, CV_RGBA2BGR565);
            }
        }
        AndroidBitmap_unlockPixels(env, bitmap);
        return bitmap;
    } catch (cv::Exception e) {
        AndroidBitmap_unlockPixels(env, bitmap);
        jclass je = env->FindClass("org/opencv/core/CvException");
        if (!je) je = env->FindClass("java/lang/Exception");
        env->ThrowNew(je, e.what());
        return bitmap;
    } catch (...) {
        AndroidBitmap_unlockPixels(env, bitmap);
        jclass je = env->FindClass("java/lang/Exception");
        env->ThrowNew(je, "Unknown exception in JNI code {nMatToBitmap}");
        return bitmap;
    }
}
