#pragma once

#include "graphics/model/Bounding_box.h"


namespace graphics
{
	class Canvas;

	/*!
	 * Abstract class for the drawable shapes\n
	 *
	 * - Point_shp
	 * - Segment_shp
	 * - Line_shp
	 * - Circle_shp
	 * - Polygon_shp
	 * - Vector_shp
	 * - Text_shp
	 *
	 * Each Shape has a Bounding_box which is the smallest rectangle that
	 * contains the Shape\n
	 */
	class Shape
	{
	protected:
		Bounding_box bounding_box;

	public:
		Shape() = default;
		Shape(const Shape& other) = default;

		Bounding_box get_bounding_box() const;
		virtual void draw(Canvas& canvas) const = 0;
		virtual void write(std::ostream& os) const = 0;
	};
}
