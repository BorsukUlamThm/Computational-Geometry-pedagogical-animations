#pragma once

/** @cond */
#include <filesystem>
#include <fstream>
#include <vector>
/** @endcond */
#include "General_tools/General_tools.h"
#include "Segment_2.h"

namespace algorithms
{
template<typename Real>
Point_2<Real> read_point_2(std::istream& is);
template<typename Real>
Segment_2<Real> read_segment_2(std::istream& is);
template<typename Real>
std::vector<Point_2<Real>> read_point_2_set(std::ifstream& ifs);
template<typename Real>
std::vector<Point_2<Real>> read_point_2_set(const std::string& path);
template<typename Real>
std::vector<Segment_2<Real>> read_segment_2_set(std::ifstream& ifs);
template<typename Real>
std::vector<Segment_2<Real>> read_segment_2_set(const std::string& path);
template<typename Real>
std::ostream& operator<<(std::ostream& os, const Point_2<Real>& p);
template<typename Real>
std::ostream& operator<<(std::ostream& os, const Segment_2<Real>& s);
template<typename Real>
void save_point_2_set(const std::string& path, const std::vector<Point_2<Real>>& points);
template<typename Real>
void save_segment_2_set(const std::string& path, const std::vector<Segment_2<Real>>& segments);


template<typename Real>
Point_2<Real> read_point_2(std::istream& is)
{
    Real x, y;
    is >> x >> y;
    return Point_2<Real>(x, y);
}

template<typename Real>
Segment_2<Real> read_segment_2(std::istream& is)
{
    Real x1, y1, x2, y2;
    is >> x1 >> y1 >> x2 >> y2;
    return Segment_2<Real>(x1, y1, x2, y2);
}

template<typename Real>
std::vector<Point_2<Real>> read_point_2_set(std::ifstream& ifs)
{
    std::vector<Point_2<Real>> points;
    unsigned n;
    ifs >> n;

    for(unsigned i = 0; i < n; ++i)
    {
        points.push_back(read_point_2<Real>(ifs));
    }

    return points;
}

template<typename Real>
std::vector<Point_2<Real>> read_point_2_set(const std::string& path)
{
    std::filesystem::path Project_dir = general_tools::get_project_directory();
    std::ifstream ifs(Project_dir / path);

    return read_point_2_set<Real>(ifs);
}

template<typename Real>
std::vector<Segment_2<Real>> read_segment_2_set(std::ifstream& ifs)
{
    std::vector<Segment_2<Real>> segments;
    unsigned n;
    ifs >> n;

    for(unsigned i = 0; i < n; ++i)
    {
        segments.push_back(read_segment_2<Real>(ifs));
    }

    return segments;
}

template<typename Real>
std::vector<Segment_2<Real>> read_segment_2_set(const std::string& path)
{
    std::filesystem::path Project_dir = general_tools::get_project_directory();
    std::ifstream ifs(Project_dir / path);

    return read_segment_2_set<Real>(ifs);
}

template<typename Real>
std::ostream& operator<<(std::ostream& os, const Point_2<Real>& p)
{
    os << p.x << " " << p.y;
    return os;
}

template<typename Real>
std::ostream& operator<<(std::ostream& os, const Segment_2<Real>& s)
{
    os << s.ogn << " " << s.dst;
    return os;
}

template<typename Real>
void save_point_2_set(const std::string& path, const std::vector<Point_2<Real>>& points)
{
    std::filesystem::path project_dir = general_tools::get_project_directory();
    std::ofstream ofs(project_dir / path);

    unsigned n = points.size();
    ofs << n << std::endl;

    for(unsigned i = 0; i < n; ++i)
    {
        ofs << points[i] << std::endl;
    }
}

template<typename Real>
void save_segment_2_set(const std::string& path, const std::vector<Segment_2<Real>>& segments)
{
    std::filesystem::path project_dir = general_tools::get_project_directory();
    std::ofstream ofs(project_dir / path);

    unsigned n = segments.size();
    ofs << n << std::endl;

    for(unsigned i = 0; i < n; ++i)
    {
        ofs << segments[i] << std::endl;
    }
}
}