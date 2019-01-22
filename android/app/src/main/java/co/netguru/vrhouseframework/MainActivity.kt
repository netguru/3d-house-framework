package co.netguru.vrhouseframework

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    private val recognizer = NativeRecognizer()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val bitmap = BitmapFactory.decodeResource(resources, R.drawable.house_plan)
        image.setImageResource(R.drawable.house_plan)

        recognizePlan(bitmap)
        detectWalls(bitmap)
    }

    private fun recognizePlan(bitmap: Bitmap) {
        val result = recognizer.recognizePlane(bitmap)
        val resultText =
            if (result.isEmpty()) getString(R.string.empty)
            else getString(R.string.not_empty, "${result[0]}, ${result[1]}, ${result[2]}, ${result[3]}")

        above_text.text = getString(R.string.result_of_recognizePlane, resultText)
    }

    private fun detectWalls(bitmap: Bitmap) {
        val result = recognizer.findWalls(bitmap)
        walls_overlay.drawWalls(result, bitmap)
    }
}
