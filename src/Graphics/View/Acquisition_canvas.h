#pragma once

#include "Graphics/Model/Acquisitions/Acquisition.h"
#include "Canvas_events.h"


namespace gr
{
class Acquisition_canvas : public Canvas
{
private:
    enum State {BEGIN_ACQ, POINT_ACQ1, SEGMENT_ACQ1, SEGMENT_ACQ2, END_ACQ};

    std::vector<Acquisition> buffer;
    unsigned index = 0;
    Figure acquisitions;
    State state = BEGIN_ACQ;

public:
    Acquisition_canvas() = default;
    ~Acquisition_canvas() = default;

    void add_point_acquisition(Color col = DEFAULT_PLOT_COLOR,
                               float rad = 3);
    void add_segment_acquisition(Color line_col = DEFAULT_PLOT_COLOR,
                                 Color end_points_col = DEFAULT_PLOT_COLOR);

    Figure acquire_buffer();

private:
    void setup_bounding_box();
    void set_next_state();
    void acquire_point(Coordinate& x, Coordinate& y);

    void handle_events();
    void handle_point(Coordinate x, Coordinate y);
    void key_pressed_event(const sf::Event& event);
};

void Acquisition_canvas::add_point_acquisition(Color col, float rad)
{
    Point_acq point(col, rad);
    buffer.emplace_back(point);
}

void Acquisition_canvas::add_segment_acquisition(Color line_col,
                                                 Color end_points_col)
{
    Segment_acq segment(line_col, end_points_col);
    buffer.emplace_back(segment);
}

Figure Acquisition_canvas::acquire_buffer()
{
    config.margin = 0;
    open();
    set_next_state();
    while(window.isOpen() && state != END_ACQ)
    {
        handle_events();
        draw_figure(acquisitions);
        window.display();
    }

    return Figure(acquisitions);
}

void Acquisition_canvas::setup_bounding_box()
{
    if(acquisitions.is_empty())
    {
        gr::Point_plt p(0, 0);
        gr::Point_plt q((Coordinate(config.width)), Coordinate(config.height));

        bounding_box.clear();
        bounding_box.extend(p);
        bounding_box.extend(q);
    }
    else
    {
        bounding_box = Bounding_box(acquisitions.get_bounding_box());
    }
}

void Acquisition_canvas::set_next_state()
{
    if(index >= buffer.size())
    {
        state = END_ACQ;
        return;
    }

    switch(buffer[index].type())
    {
        case POINT_ACQ:
            state = POINT_ACQ1;
            break;

        case SEGMENT_ACQ:
            state = SEGMENT_ACQ1;
            break;
    }
}

void Acquisition_canvas::acquire_point(Coordinate& x, Coordinate& y)
{
    float ratio_x = mouse_x / float(config.width);
    float ratio_y = mouse_y / float(config.height);

    float view_size_x = view.getSize().x;
    float view_size_y = view.getSize().y;
    float xm = view.getCenter().x - view.getSize().x / 2;
    float ym = view.getCenter().y - view.getSize().y / 2;

    x = xm + ratio_x * view_size_x;
    y = -ym - ratio_y * view_size_y;
}
}