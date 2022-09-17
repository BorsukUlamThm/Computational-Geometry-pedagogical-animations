#pragma once

#include <memory>
#include "graphics/model/Geometric_object.h"


namespace graphics
{
	enum State_acq
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
		std::string name {};
		unsigned nb_acquisitions = -1;
		std::vector<Geometric_object_ptr> acquired_shapes;

	public:
		virtual State_acq starting_state() const = 0;

		unsigned get_nb_acquisitions() const;
		unsigned get_size() const;

		const Geometric_object_ptr& get(unsigned i) const;
		Geometric_object_ptr& get(unsigned i);

		template<typename Object>
		std::vector<Object> get_objects() const;

		std::string get_name() const;
	};

	template<typename Object>
	std::vector<Object> Acquisition::get_objects() const
	{
		std::vector<Object> objects;
		for (auto& as : acquired_shapes)
		{
			std::shared_ptr<Object> obj = std::dynamic_pointer_cast<Object>(as);
			objects.template emplace_back(*obj);
		}

		return objects;
	}
}