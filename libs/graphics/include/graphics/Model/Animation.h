#pragma once

#include <vector>
#include "Figure.h"


namespace graphics
{
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

	template<typename... Indexes>
	void Animation::make_new_frame(unsigned int index,
								   Indexes... indexes)
	{
		frames.emplace_back();
		aux_make_new_frame(index);
		aux_make_new_frame(indexes...);
	}

	template<typename... Indexes>
	void Animation::aux_make_new_frame(unsigned int index,
									   Indexes... indexes)
	{
		aux_make_new_frame(index);
		aux_make_new_frame(indexes...);
	}
}