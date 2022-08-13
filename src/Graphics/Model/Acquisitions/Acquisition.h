#pragma once

/** @cond */
#include <memory>
/** @endcond */
#include "Acquired_shape.h"


namespace graphics
{
	enum State
	{
		BEGIN_ACQ,
		POINT_ACQ1,
		SEGMENT_ACQ1,
		SEGMENT_ACQ2,
		END_ACQ
	};

	typedef std::shared_ptr<Acquired_shape> Acquired_shape_ptr;

	class Acquisition
	{
	protected:
		unsigned nb_acquisitions = -1;
		std::vector<Acquired_shape_ptr> acquired_shapes;

	public:
		virtual State starting_state() const = 0;
		unsigned get_nb_acquisitions() const;
		unsigned get_size() const;
		const Acquired_shape_ptr& operator[](unsigned i) const;
		Acquired_shape_ptr& operator[](unsigned i);
		const Acquired_shape_ptr& get(unsigned i) const;
		Acquired_shape_ptr& get(unsigned i);
	};

	unsigned Acquisition::get_nb_acquisitions() const
	{ return nb_acquisitions; }

	unsigned Acquisition::get_size() const
	{ return acquired_shapes.size(); }

	const Acquired_shape_ptr& Acquisition::operator[](unsigned i) const
	{ return acquired_shapes[i]; }

	Acquired_shape_ptr& Acquisition::operator[](unsigned i)
	{ return acquired_shapes[i]; }

	const Acquired_shape_ptr& Acquisition::get(unsigned i) const
	{ return acquired_shapes[i]; }

	Acquired_shape_ptr& Acquisition::get(unsigned i)
	{ return acquired_shapes[i]; }
}