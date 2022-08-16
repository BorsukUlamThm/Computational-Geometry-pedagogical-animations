#pragma once

#include <memory>
#include "graphics/Model/Geometric_object.h"


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

	typedef std::shared_ptr<Geometric_object> Geometric_object_ptr;

	/*!
	 * An acquisition is a set of Geometric_object that will be acquired on an
	 * Acquisition_canvas. It also contains the number of desired objects to
	 * acquire
	 */
	class Acquisition
	{
	protected:
		unsigned nb_acquisitions = -1;
		std::vector<Geometric_object_ptr> acquired_shapes;

	public:
		virtual State starting_state() const = 0;

		unsigned get_nb_acquisitions() const;
		unsigned get_size() const;

		const Geometric_object_ptr& get(unsigned i) const;
		Geometric_object_ptr& get(unsigned i);
	};
}