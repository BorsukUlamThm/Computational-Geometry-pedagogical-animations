#ifndef ALPHA_SLIDE_SHOW_H
#define ALPHA_SLIDE_SHOW_H

#include "Figure.h"


namespace gr
{
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


#endif //ALPHA_SLIDE_SHOW_H
