#pragma once

#include "Figure.h"


namespace graphics
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * A Slide_show is a sequence of Figure that will be displayed in the
	 * specified order\n
	 */
	class Slide_show
	{
	private:
		std::vector<Figure> slides;

	public:
		Slide_show() = default;
		~Slide_show() = default;

		void add_slide(const Figure& figure);
		template<typename... Figures>
		void add_slide(const Figure& figure, const Figures&... figures);

		unsigned nb_slides() const;
		Figure& operator[](unsigned i);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	void Slide_show::add_slide(const Figure& figure)
	{
		slides.emplace_back(figure);
	}

	template<typename... Figures>
	void Slide_show::add_slide(const Figure& figure, const Figures&... figures)
	{
		Figure new_figure(figure, figures...);
		add_slide(new_figure);
	}

	unsigned Slide_show::nb_slides() const
	{
		return slides.size();
	}

	Figure& Slide_show::operator[](unsigned int i)
	{
		return slides[i];
	}
}