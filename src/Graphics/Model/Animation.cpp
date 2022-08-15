#include "Graphics/Model/Animation.h"


namespace graphics
{
	Animation::Animation(unsigned nb_figures)
	{
		figures = std::vector<Figure>(nb_figures);
	}

	void Animation::make_new_frame()
	{
		frames.emplace_back();
		for (auto& fig : figures)
		{
			frames.back().merge_figure(fig);
		}
	}

	void Animation::make_new_frame(unsigned index)
	{
		frames.emplace_back();
		aux_make_new_frame(index);
	}

	unsigned Animation::nb_frames() const
	{ return frames.size(); }

	Figure Animation::get_ith_frame(unsigned i) const
	{ return frames[i]; }

	Figure& Animation::get_ith_frame(unsigned i)
	{ return frames[i]; }

	Figure Animation::operator[](unsigned i) const
	{ return figures[i]; }

	Figure& Animation::operator[](unsigned i)
	{ return figures[i]; }

	void Animation::aux_make_new_frame(unsigned int index)
	{
		frames.back().merge_figure(figures[index]);
	}
}