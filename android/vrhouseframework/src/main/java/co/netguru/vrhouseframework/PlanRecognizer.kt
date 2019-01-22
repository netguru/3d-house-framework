package co.netguru.vrhouseframework

import android.graphics.Bitmap
import android.graphics.PointF

class NativeRecognizer : Recognizer {

    external override fun cropSelectedArea(bitmap: Bitmap, points: FloatArray): Bitmap

    external override fun recognizePlane(bitmap: Bitmap): FloatArray

    external override fun findWalls(bitmap: Bitmap): Array<FloatArray>

    override fun mapWallOutputToPoints(output: Array<FloatArray>): List<List<PointF>> {
        val result = mutableListOf<MutableList<PointF>>()
        for (wall in output) {
            val path = mutableListOf<PointF>()
            for (i in 0..(wall.size - 1) step 2) {
                path.add(PointF(wall[i], wall[i +1]))
            }
            result.add(path)
        }
        return result
    }

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}
