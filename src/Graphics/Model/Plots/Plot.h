#pragma once

/** @cond */
#include <iostream>
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Graphics/Model/Global_variables.h"

namespace gr
{
	class Canvas;
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * Wrapper class for all the plots
	 */
	class Plot
	{
	public:
		virtual Coordinate get_min_abscissa() const = 0;
		virtual Coordinate get_max_abscissa() const = 0;
		virtual Coordinate get_min_ordinate() const = 0;
		virtual Coordinate get_max_ordinate() const = 0;

		virtual void draw(Canvas& canvas) const = 0;
	};
}
