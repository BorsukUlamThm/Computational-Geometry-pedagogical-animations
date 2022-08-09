#pragma once

#include "Point_acq.h"
#include "Segment_acq.h"


namespace gr
{
	enum Acquisition_type
	{
		POINT_ACQ,
		SEGMENT_ACQ
	};

	class Acquisition
	{
	private:
		Acquisition_type acquisition_type;
		union
		{
			Point_acq u_point;
			Segment_acq u_segment;
		};

	public:
		explicit Acquisition(Acquisition_type type);
		explicit Acquisition(const Point_acq& point);
		explicit Acquisition(const Segment_acq& segment);
		Acquisition(const Acquisition& other);
		~Acquisition();

		Acquisition_type type() const;
		Point_acq point() const;
		Segment_acq segment() const;
	};

	Acquisition::Acquisition(Acquisition_type type)
	{
		acquisition_type = type;
		switch(type)
		{
			case POINT_ACQ:
				new (&u_point) Point_acq();
				break;
			case SEGMENT_ACQ:
				new (&u_segment) Segment_acq();
				break;
		}
	}

	Acquisition::Acquisition(const Point_acq& point):
			acquisition_type(POINT_ACQ),
			u_point(Point_acq(point))
	{}

	Acquisition::Acquisition(const Segment_acq& segment):
			acquisition_type(SEGMENT_ACQ),
			u_segment(Segment_acq(segment))
	{}

	Acquisition::Acquisition(const Acquisition& other)
	{
		acquisition_type = other.acquisition_type;
		switch(acquisition_type)
		{
			case POINT_ACQ:
				new (&u_point) Point_acq(other.u_point);
				break;
			case SEGMENT_ACQ:
				new (&u_segment) Segment_acq(other.u_segment);
				break;
		}
	}

	Acquisition::~Acquisition()
	{
		switch(acquisition_type)
		{
			case POINT_ACQ:
				u_point.~Point_acq();
				break;
			case SEGMENT_ACQ:
				u_segment.~Segment_acq();
				break;
		}
	}

	Acquisition_type Acquisition::type() const
	{
		return acquisition_type;
	}

	Point_acq Acquisition::point() const
	{
		return u_point;
	}

	Segment_acq Acquisition::segment() const
	{
		return u_segment;
	}
}