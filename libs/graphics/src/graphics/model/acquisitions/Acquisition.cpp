#include "graphics/model/acquisitions/Acquisition.h"


namespace graphics
{
	unsigned Acquisition::get_nb_acquisitions() const
	{ return nb_acquisitions; }

	unsigned Acquisition::get_size() const
	{ return acquired_shapes.size(); }

	const Geometric_object_ptr& Acquisition::get(unsigned i) const
	{ return acquired_shapes[i]; }

	Geometric_object_ptr& Acquisition::get(unsigned i)
	{ return acquired_shapes[i]; }

	std::string Acquisition::get_name() const
	{ return name; }
}