package co.netguru.vrhouseframework

import android.content.Context
import android.graphics.*
import android.support.annotation.Nullable
import android.util.AttributeSet
import android.view.View

/**
 * Overlay to draw detected walls on image of plan.
 * This overlay should have the same size as image and be above it.
 */
class WallsOverlayView : View {

    constructor(context: Context) : super(context)

    constructor(context: Context, @Nullable attrs: AttributeSet) : super(context, attrs)

    constructor(context: Context, @Nullable attrs: AttributeSet, defStyleAttr: Int) : super(
        context,
        attrs,
        defStyleAttr
    )

    private val walls = mutableListOf<List<PointF>>()
    private val paint = Paint().apply {
        style = Paint.Style.STROKE
        color = Color.RED
        strokeWidth = 5f
    }
    private val path = Path()

    private var xScale = 0f
    private var yScale = 0f

    fun drawWalls(walls: Array<FloatArray>, bitmap: Bitmap) {
        drawWalls(NativeRecognizer().mapWallOutputToPoints(walls), bitmap)
    }

    fun drawWalls(walls: List<List<PointF>>, bitmap: Bitmap) {
        this.walls.addAll(walls)
        this.post {
            xScale = this.width.toFloat() / bitmap.width.toFloat()
            yScale = this.height.toFloat() / bitmap.height.toFloat()
            walls.forEach { it.forEach { point ->
                point.x *= xScale
                point.y *= yScale
            } }
            invalidate()
        }
    }

    override fun onDraw(canvas: Canvas) {
        super.onDraw(canvas)
        for (wall in walls) {
            path.reset()
            for (point in wall) {
                if (wall.indexOf(point) == 0) {
                    path.moveTo(point.x, point.y)
                } else {
                    path.lineTo(point.x, point.y)
                }
            }
            canvas.drawPath(path, paint)
        }
    }
}
