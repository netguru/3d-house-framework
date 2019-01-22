package co.netguru.vrhouseframework

import android.graphics.Bitmap
import android.graphics.PointF

interface Recognizer {
    fun recognizePlane(bitmap: Bitmap): FloatArray
    fun cropSelectedArea(bitmap: Bitmap, points: FloatArray): Bitmap
    fun findWalls(bitmap: Bitmap): Array<FloatArray>
    fun mapWallOutputToPoints(output: Array<FloatArray>): List<List<PointF>>
}
