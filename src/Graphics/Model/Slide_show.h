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

    void add_figure(const Figure& figure);

    unsigned nb_slides() const;
    const Figure& operator[](unsigned i) const;
};

void Slide_show::add_figure(const Figure& figure)
{
    slides.emplace_back(figure);
}

unsigned Slide_show::nb_slides() const
{
    return slides.size();
}

const Figure& Slide_show::operator[](unsigned int i) const
{
    return slides[i];
}
}


#endif //ALPHA_SLIDE_SHOW_H
