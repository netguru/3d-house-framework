package co.netguru.vrhouseframework

import android.graphics.Bitmap

class NativeRecognizer : Recognizer {

    external override fun cropSelectedArea(bitmap: Bitmap, points: FloatArray): Bitmap

    external override fun recognizePlane(bitmap: Bitmap): FloatArray

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}
