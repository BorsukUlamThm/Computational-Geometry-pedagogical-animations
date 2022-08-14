#pragma once

#include "Figure.h"


namespace graphics
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	class Animation
	{
	private:
		std::vector<Figure> frames;
		std::vector<Figure> figures;

	public:
		Animation() = default;
		explicit Animation(unsigned nb_figures);
		~Animation() = default;

		void make_new_frame();
		void make_new_frame(unsigned index);
		template<typename... Indexes>
		void make_new_frame(unsigned index,
							Indexes ... indexes);

		unsigned nb_frames() const;
		Figure get_ith_frame(unsigned i) const;
		Figure& get_ith_frame(unsigned i);

		Figure operator[](unsigned i) const;
		Figure& operator[](unsigned i);

	private:
		void aux_make_new_frame(unsigned index);
		template<typename... Indexes>
		void aux_make_new_frame(unsigned index,
							Indexes ... indexes);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

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

	template<typename... Indexes>
	void Animation::make_new_frame(unsigned int index,
								   Indexes... indexes)
	{
		frames.emplace_back();
		aux_make_new_frame(index);
		aux_make_new_frame(indexes...);
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

	template<typename... Indexes>
	void Animation::aux_make_new_frame(unsigned int index,
									   Indexes... indexes)
	{
		aux_make_new_frame(index);
		aux_make_new_frame(indexes...);
	}
}