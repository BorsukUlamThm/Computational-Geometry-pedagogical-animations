#pragma once

/** @cond */
#include <iostream>
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Graphics/Model/Bounding_box.h"


namespace graphics
{
	class Canvas;
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

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
		Bounding_box get_bounding_box() const;
		virtual void draw(Canvas& canvas) const = 0;
		virtual void write(std::ostream& os) const = 0;
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Bounding_box Shape::get_bounding_box() const
	{ return bounding_box; }
}
