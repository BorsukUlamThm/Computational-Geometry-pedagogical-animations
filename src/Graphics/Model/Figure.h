#ifndef ALPHA_FIGURE_H
#define ALPHA_FIGURE_H

#include "Plots/Plot.h"
#include "Plots/Point_plt.h"
#include "Plots/Segment_plt.h"
#include "Plots/Polygon_plt.h"

#include "Bounding_box.h"


namespace gr
{
class Figure
{
private:
    std::vector<Plot> plots;
    Bounding_box bounding_box{};
    bool need_remake_bounding_box = false;

public:
    Figure() = default;
    template<typename... Figures>
    explicit Figure(const Figure& figure, const Figures&... figures);
    ~Figure() = default;

    Bounding_box get_bounding_box() const;
    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;
    Plot get_last_plot() const;

    void add_point(const Point_plt& point);
    void add_point(const Coordinate& x, const Coordinate& y,
                   Color col = DEFAULT_PLOT_COLOR, float rad = 3);
    template<typename... Points>
    void add_point(const Point_plt& point, const Points&... points);
    void add_segment(const Segment_plt& segment);
    void add_segment(const Point_plt& ogn, const Point_plt& dst,
                     Color line_col = DEFAULT_PLOT_COLOR);
    void add_segment(const Coordinate& ogn_x, const Coordinate& ogn_y,
                     const Coordinate& dst_x, const Coordinate& dst_y,
                     Color line_col = DEFAULT_PLOT_COLOR,
                     Color end_points_col = DEFAULT_PLOT_COLOR);
    template<typename... Segments>
    void add_segment(const Segment_plt& segment, const Segments&... segments);
    void add_vector(const Vector_plt& vector);
    void add_vector(const Coordinate& ogn_x, const Coordinate& ogn_y,
                    const Coordinate& dst_x, const Coordinate& dst_y,
                    Color col = DEFAULT_PLOT_COLOR);
    void add_vector(const Point_plt& ogn, const Point_plt& dst,
                    Color col = DEFAULT_PLOT_COLOR);
    void add_vector(const Segment_plt& segment, Color col = DEFAULT_PLOT_COLOR);
    template<typename... Vectors>
    void add_vector(const Vector_plt& vector, const Vectors&... vectors);
    void add_polygon(const Polygon_plt& polygon);
    void add_polygon(const std::vector<Point_plt>& vertices,
                     Color lines_col = DEFAULT_PLOT_COLOR);
    template<typename... Polygons>
    void add_polygon(const Polygon_plt& polygon, const Polygons&... polygons);
    void add_circle(const Circle_plt& circle);
    void add_circle(const Coordinate& x, const Coordinate& y, const Coordinate& rad,
                    Color col = DEFAULT_PLOT_COLOR);
    template<typename... Circles>
    void add_circle(const Circle_plt& circle, const Circles&... circles);
    void add_line(const Line_plt& line);
    void add_line(const Coordinate& a, const Coordinate& b, const Coordinate& c,
                  Color col = DEFAULT_PLOT_COLOR);
    void add_line(const Segment_plt& segment, Color col = DEFAULT_PLOT_COLOR);
    void add_line(const Point_plt& point1, const Point_plt& point2,
                  Color col = DEFAULT_PLOT_COLOR);
    void add_line(const Coordinate& x1, const Coordinate& y1,
                  const Coordinate& x2, const Coordinate& y2,
                  Color col = DEFAULT_PLOT_COLOR);
    template<typename... Lines>
    void add_line(const Line_plt& line, const Lines&... lines);
    void add_vertical_line(const Coordinate& x,
                           Color col = DEFAULT_PLOT_COLOR);
    void add_horizontal_line(const Coordinate& y,
                             Color col = DEFAULT_PLOT_COLOR);
    void add_text(const Text_plt& text);
    void add_text(const std::string& text, const Coordinate& x, const Coordinate& y,
                  unsigned size = 16, float off_x = 0, float off_y = 0,
                  Color col = DEFAULT_PLOT_COLOR);
    void add_text(const std::string& text, const Point_plt& point, unsigned size = 16,
                  Color col = DEFAULT_PLOT_COLOR);
    void add_text(const std::string& text, const Segment_plt& segment, unsigned size = 16,
                  Color col = DEFAULT_PLOT_COLOR);
    void add_text(const std::string& text, const Vector_plt& vector, unsigned size = 16,
                  Color col = DEFAULT_PLOT_COLOR);

    void merge_figure(const Figure& other);
    template<typename... Figures>
    void merge_figure(const Figure& figure, const Figures&... figures);

    void erase_last_plot();
    void erase_last_k_plots(unsigned k);
    void make_bounding_box();
    void clear();

    unsigned nb_plots() const;
    bool is_empty() const;
    const Plot& operator[](unsigned i) const;
};

template<typename... Figures>
Figure::Figure(const Figure& figure, const Figures&... figures)
{
    merge_figure(figure);
    merge_figure(figures...);
}

Bounding_box Figure::get_bounding_box() const
{
    return bounding_box;
}

Coordinate Figure::get_min_abscissa() const
{
    return bounding_box.get_min_abscissa();
}

Coordinate Figure::get_max_abscissa() const
{
    return bounding_box.get_max_abscissa();
}

Coordinate Figure::get_min_ordinate() const
{
    return bounding_box.get_min_ordinate();
}

Coordinate Figure::get_max_ordinate() const
{
    return bounding_box.get_max_ordinate();
}

Plot Figure::get_last_plot() const
{
    return plots.back();
}

void Figure::add_point(const Point_plt& point)
{
    Plot plot(point);
    plots.push_back(plot);
    bounding_box.extend(point);
}

void Figure::add_point(const Coordinate& x, const Coordinate& y,
                       Color col, float rad)
{
    Point_plt point(x, y, col, rad);
    add_point(point);
}

template<typename... Points>
void Figure::add_point(const Point_plt& point, const Points&... points)
{
    add_point(point);
    add_point(points...);
}

void Figure::add_segment(const Segment_plt& segment)
{
    plots.emplace_back(segment);
    bounding_box.extend(segment);
}

void Figure::add_segment(const Point_plt& ogn, const Point_plt& dst,
                         Color line_col)
{
    Segment_plt segment(ogn, dst, line_col);
    add_segment(segment);
}

void Figure::add_segment(const Coordinate& ogn_x, const Coordinate& ogn_y,
                         const Coordinate& dst_x, const Coordinate& dst_y,
                         Color line_col, Color end_points_col)
{
    Segment_plt segment(ogn_x, ogn_y, dst_x, dst_y, line_col, end_points_col);
    add_segment(segment);
}

template<typename... Segments>
void Figure::add_segment(const Segment_plt& segment, const Segments&... segments)
{
    add_segment(segment);
    add_segment(segments...);
}

void Figure::add_vector(const Vector_plt& vector)
{
    plots.emplace_back(vector);
    bounding_box.extend(vector);
}

void Figure::add_vector(const Coordinate& ogn_x, const Coordinate& ogn_y,
                        const Coordinate& dst_x, const Coordinate& dst_y,
                        Color col)
{
    Vector_plt vector(ogn_x, ogn_y, dst_x, dst_y, col);
    add_vector(vector);
}

void Figure::add_vector(const Point_plt& ogn, const Point_plt& dst, Color col)
{
    Vector_plt vector(ogn, dst, col);
    add_vector(vector);
}

void Figure::add_vector(const Segment_plt& segment, Color col)
{
    Vector_plt vector(segment, col);
    add_vector(vector);
}

template<typename... Vectors>
void Figure::add_vector(const Vector_plt& vector, const Vectors&... vectors)
{
    add_vector(vector);
    add_vector(vectors...);
}

void Figure::add_polygon(const Polygon_plt& polygon)
{
    plots.emplace_back(polygon);
    bounding_box.extend(polygon);
}

void Figure::add_polygon(const std::vector<Point_plt>& vertices,
                         Color lines_col)
{
    Polygon_plt polygon(vertices, lines_col);
    add_polygon(polygon);
}

template<typename... Polygons>
void Figure::add_polygon(const Polygon_plt& polygon, const Polygons&... polygons)
{
    add_polygon(polygon);
    add_polygon(polygons...);
}

void Figure::add_circle(const Circle_plt& circle)
{
    plots.emplace_back(circle);
    bounding_box.extend(circle);
}

void Figure::add_circle(const Coordinate& x, const Coordinate& y,
                        const Coordinate& rad, Color col)
{
    Circle_plt circle(x, y, rad, col);
    add_circle(circle);
}

template<typename... Circles>
void Figure::add_circle(const Circle_plt& circle, const Circles&... circles)
{
    add_circle(circle);
    add_circle(circles...);
}

void Figure::add_line(const Line_plt& line)
{
    plots.emplace_back(line);
    bounding_box.extend(line);
}

void Figure::add_line(const Coordinate& a, const Coordinate& b, const Coordinate& c,
                      Color col)
{
    Line_plt line(a, b, c, col);
    add_line(line);
}

void Figure::add_line(const Segment_plt& segment, Color col)
{
    Line_plt line(segment, col);
    add_line(line);
}

void Figure::add_line(const Point_plt& point1, const Point_plt& point2, Color col)
{
    Line_plt line(point1, point2, col);
    add_line(line);
}

void Figure::add_line(const Coordinate& x1, const Coordinate& y1,
                      const Coordinate& x2, const Coordinate& y2,
                      Color col)
{
    Line_plt line(x1, y1, x2, y2, col);
    add_line(line);
}

template<typename... Lines>
void Figure::add_line(const Line_plt& line, const Lines&... lines)
{
    add_line(line);
    add_line(lines...);
}

void Figure::add_vertical_line(const Coordinate& x, Color col)
{
    Line_plt line(1, 0, -x, col);
    add_line(line);
}

void Figure::add_horizontal_line(const Coordinate& y, Color col)
{
    Line_plt line(0, 1, -y, col);
    add_line(line);
}

void Figure::add_text(const Text_plt& text)
{
    plots.emplace_back(text);
    bounding_box.extend(text);
}

void Figure::add_text(const std::string& text, const Coordinate& x, const Coordinate& y,
                      unsigned size, float off_x, float off_y, Color col)
{
    Text_plt txt(text, x, y, size, off_x, off_y, col);
    add_text(txt);
}

void Figure::add_text(const std::string& text, const Point_plt& point, unsigned size,
                      Color col)
{
    Text_plt txt(text, point, size, col);
    add_text(txt);
}

void Figure::add_text(const std::string& text, const Segment_plt& segment, unsigned size,
                      Color col)
{
    Text_plt txt(text, segment, size, col);
    add_text(txt);
}

void Figure::add_text(const std::string& text, const Vector_plt& vector, unsigned size,
                      Color col)
{
    Text_plt txt(text, vector, size, col);
    add_text(txt);
}

void Figure::merge_figure(const Figure& other)
{
    for(unsigned i = 0; i < other.nb_plots(); ++i)
    {
        switch(other[i].type())
        {
            case POINT_PLT:
                add_point(other[i].point());
                break;
            case SEGMENT_PLT:
                add_segment(other[i].segment());
                break;
            case VECTOR_PLT:
                add_vector(other[i].vector());
                break;
            case POLYGON_PLT:
                add_polygon(other[i].polygon());
                break;
            case CIRCLE_PLT:
                add_circle(other[i].circle());
                break;
            case LINE_PLT:
                add_line(other[i].line());
                break;
            case TEXT_PLT:
                add_text(other[i].text());
                break;
        }
    }
}

template<typename... Figures>
void Figure::merge_figure(const Figure& figure, const Figures&... figures)
{
    merge_figure(figure);
    merge_figure(figures...);
}

void Figure::erase_last_plot()
{
    if(is_empty())
    {
        return;
    }
    Plot plot = plots.back();
    Coordinate xM = plot.get_max_abscissa();
    Coordinate xm = plot.get_min_abscissa();
    Coordinate yM = plot.get_max_ordinate();
    Coordinate ym = plot.get_min_ordinate();

    if(xM == get_max_abscissa() || xm == get_min_abscissa() ||
       yM == get_max_ordinate() || ym == get_min_ordinate())
    {
        need_remake_bounding_box = true;
    }

    plots.pop_back();
}

void Figure::erase_last_k_plots(unsigned int k)
{
    if(k >= nb_plots())
    {
        clear();
        return;
    }
    for(unsigned i = 0; i < k; ++i)
    {
        erase_last_plot();
    }
}

void Figure::make_bounding_box()
{
    if(need_remake_bounding_box)
    {
        bounding_box.clear();
        for(unsigned i = 0; i < nb_plots(); ++i)
        {
            switch(plots[i].type())
            {
                case POINT_PLT:
                    bounding_box.extend(plots[i].point());
                    break;
                case SEGMENT_PLT:
                    bounding_box.extend(plots[i].segment());
                    break;
                case VECTOR_PLT:
                    bounding_box.extend(plots[i].vector());
                    break;
                case POLYGON_PLT:
                    bounding_box.extend(plots[i].polygon());
                    break;
                case CIRCLE_PLT:
                    bounding_box.extend(plots[i].circle());
                    break;
                case LINE_PLT:
                    /* nothing to do but i let it in a comment just in case
                    bounding_box.extend(plots[i].line());*/
                    break;
                case TEXT_PLT:
                    bounding_box.extend(plots[i].text());
            }
        }
    }
}

void Figure::clear()
{
    plots.clear();
    bounding_box.clear();
}

unsigned Figure::nb_plots() const
{
    return plots.size();
}

bool Figure::is_empty() const
{
    return nb_plots() == 0;
}

const Plot& Figure::operator[](unsigned int i) const
{
    return plots[i];
}

std::istream& operator>>(std::istream& is, Figure& figure)
{
    figure.clear();
    std::string plot_name;
    Point_plt point;
    Segment_plt segment;
    Vector_plt vector;
    Polygon_plt polygon;
    Circle_plt circle;
    Line_plt line;

    while(!is.eof())
    {
        is >> plot_name;
        if(plot_name == POINT_NAME)
        {
            is >> point;
            figure.add_point(point);
        }
        else if(plot_name == SEGMENT_NAME)
        {
            is >> segment;
            figure.add_segment(segment);
        }
        else if(plot_name == VECTOR_NAME)
        {
            is >> vector;
            figure.add_vector(vector);
        }
        else if(plot_name == POLYGON_NAME)
        {
            is >> polygon;
            figure.add_polygon(polygon);
        }
        else if(plot_name == CIRCLE_NAME)
        {
            is >> circle;
            figure.add_circle(circle);
        }
        else if(plot_name == LINE_NAME)
        {
            is >> line;
            figure.add_line(line);
        }
        plot_name = "";
    }
    return is;
}
}


#endif //ALPHA_FIGURE_H
