#include "graphics/Model/Acquisitions/Acquisition.h"


namespace graphics
{
	unsigned Acquisition::get_nb_acquisitions() const
	{ return nb_acquisitions; }

	unsigned Acquisition::get_size() const
	{ return acquired_shapes.size(); }

	const Geometric_object_ptr& Acquisition::operator[](unsigned i) const
	{ return acquired_shapes[i]; }

	Geometric_object_ptr& Acquisition::operator[](unsigned i)
	{ return acquired_shapes[i]; }

	const Geometric_object_ptr& Acquisition::get(unsigned i) const
	{ return acquired_shapes[i]; }

	Geometric_object_ptr& Acquisition::get(unsigned i)
	{ return acquired_shapes[i]; }
}