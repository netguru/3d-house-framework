package co.netguru.vrhouseframework

import android.graphics.Bitmap

interface Recognizer {
    fun recognizePlane(bitmap: Bitmap): FloatArray
    fun cropSelectedArea(bitmap: Bitmap, points: FloatArray): Bitmap
}
