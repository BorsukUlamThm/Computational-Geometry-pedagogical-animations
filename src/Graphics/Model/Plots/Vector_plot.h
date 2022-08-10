#pragma once

#include "Segment_plot.h"


namespace gr
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * Contains the needed information to draw a circle\n
	 * \n
	 * -> coordinates of the endpoints of the vector\n
	 * -> color
	 */
	class Vector_plot : public Plot
	{
	private:
		Coordinate origin_x = 0;
		Coordinate origin_y = 0;
		Coordinate destination_x = 0;
		Coordinate destination_y = 0;
		Color color = DEFAULT_PLOT_COLOR;

	public:
		// standard constructors
		Vector_plot() = default;
		Vector_plot(const Coordinate& ogn_x,
					const Coordinate& ogn_y,
					const Coordinate& dst_x,
					const Coordinate& dst_y,
					Color col = DEFAULT_PLOT_COLOR);
		Vector_plot(const Vector_plot& other);

		//other constructors
		/*!
		 * Constructs the segment whose endpoints are ogn and dst
		 */
		Vector_plot(const Point_plot& ogn,
					const Point_plot& dst,
					Color col = DEFAULT_PLOT_COLOR);
		/*!
		 * Constructs the segment whose endpoints are the segment's endpoints
		 */
		explicit Vector_plot(const Segment_plot& segment,
							 Color col = DEFAULT_PLOT_COLOR);

		~Vector_plot() = default;

		Coordinate get_origin_x() const;
		Coordinate get_origin_y() const;
		Coordinate get_destination_x() const;
		Coordinate get_destination_y() const;
		Color get_color() const;

		Coordinate get_min_abscissa() const override;
		Coordinate get_max_abscissa() const override;
		Coordinate get_min_ordinate() const override;
		Coordinate get_max_ordinate() const override;

		void draw(Canvas& canvas) const override;

		friend std::istream& operator>>(std::istream& is,
										Vector_plot& vector);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Vector_plot::Vector_plot(const Coordinate& ogn_x,
							 const Coordinate& ogn_y,
							 const Coordinate& dst_x,
							 const Coordinate& dst_y,
							 Color col)
	{
		origin_x = ogn_x;
		origin_y = ogn_y;
		destination_x = dst_x;
		destination_y = dst_y;
		color = col;
	}

	Vector_plot::Vector_plot(const Vector_plot& other)
	{
		origin_x = Coordinate(other.origin_x);
		origin_y = Coordinate(other.origin_y);
		destination_x = Coordinate(other.destination_x);
		destination_y = Coordinate(other.destination_y);
		color = other.color;
	}

	Vector_plot::Vector_plot(const Point_plot& ogn,
							 const Point_plot& dst,
							 Color col)
	{
		origin_x = ogn.get_abscissa();
		origin_y = ogn.get_ordinate();
		destination_x = dst.get_abscissa();
		destination_y = dst.get_ordinate();
		color = col;
	}

	Vector_plot::Vector_plot(const Segment_plot& segment,
							 Color col)
	{
		origin_x = segment.get_origin().get_abscissa();
		origin_y = segment.get_origin().get_ordinate();
		destination_x = segment.get_destination().get_abscissa();
		destination_y = segment.get_destination().get_ordinate();
		color = col;
	}

	Coordinate Vector_plot::get_origin_x() const
	{
		return origin_x;
	}

	Coordinate Vector_plot::get_origin_y() const
	{
		return origin_y;
	}

	Coordinate Vector_plot::get_destination_x() const
	{
		return destination_x;
	}

	Coordinate Vector_plot::get_destination_y() const
	{
		return destination_y;
	}

	Color Vector_plot::get_color() const
	{
		return color;
	}

	Coordinate Vector_plot::get_min_abscissa() const
	{
		return std::min(origin_x, destination_x);
	}

	Coordinate Vector_plot::get_max_abscissa() const
	{
		return std::max(origin_x, destination_x);
	}

	Coordinate Vector_plot::get_min_ordinate() const
	{
		return std::min(origin_y, destination_y);
	}

	Coordinate Vector_plot::get_max_ordinate() const
	{
		return std::max(origin_y, destination_y);
	}

	std::ostream& operator<<(std::ostream& os,
							 const Vector_plot& vector)
	{
		os << VECTOR_NAME << " "
		   << vector.get_origin_x() << " "
		   << vector.get_origin_y() << " "
		   << vector.get_destination_x() << " "
		   << vector.get_destination_y();
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Vector_plot& vector)
	{
		is >> vector.origin_x
		   >> vector.origin_y
		   >> vector.destination_x
		   >> vector.destination_y;
		return is;
	}
}