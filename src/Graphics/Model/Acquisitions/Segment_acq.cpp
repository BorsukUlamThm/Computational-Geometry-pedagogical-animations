#include "Graphics/Model/Acquisitions/Segment_acq.h"


namespace graphics
{
	Segment_acq::Segment_acq(unsigned nb_segments,
							 Color line_col,
							 Color endpoints_col)
	{
		nb_acquisitions = nb_segments;
		line_color = line_col;
		endpoints_color = endpoints_col;
	}

	State Segment_acq::starting_state() const
	{ return SEGMENT_ACQ1; }

	Color Segment_acq::get_line_color() const
	{ return line_color; }

	Color Segment_acq::get_endpoints_color() const
	{ return endpoints_color; }

	void Segment_acq::add_segment(const Coordinate& ogn_x,
								  const Coordinate& ogn_y,
								  const Coordinate& dst_x,
								  const Coordinate& dst_y)
	{
		Geometric_object_ptr segment =
				std::make_shared<Segment_obj>(ogn_x, ogn_y, dst_x, dst_y);
		acquired_shapes.emplace_back(segment);
	}

	void Segment_acq::add_origin(const Coordinate& ogn_x,
								 const Coordinate& ogn_y)
	{
		tmp_origin_x = ogn_x;
		tmp_origin_y = ogn_y;
	}

	void Segment_acq::add_destination(const Coordinate& dst_x,
									  const Coordinate& dst_y)
	{
		add_segment(tmp_origin_x, tmp_origin_y, dst_x, dst_y);
	}
}