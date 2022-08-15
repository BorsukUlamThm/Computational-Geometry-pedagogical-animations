#pragma once

/** @cond */
#include <filesystem>
#include <fstream>
#include <vector>
/** @endcond */
#include "utils/File_management.h"
#include "Segment_2.h"


namespace geometry
{
	template<typename Real>
	std::istream& operator>>(std::istream& is,
							 Point_2<Real>& p);
	template<typename Real>
	std::istream& operator>>(std::istream& is,
							 Segment_2<Real>& s);

	template<typename Real>
	std::istream& operator>>(std::istream& is,
							 std::vector<Point_2<Real>>& points);
	template<typename Real>
	std::istream& operator>>(std::istream& is,
							 std::vector<Segment_2<Real>>& segments);

	template<typename Real>
	std::vector<Point_2<Real>> load_point_2_set(const std::string& file);
	template<typename Real>
	std::vector<Segment_2<Real>> load_segment_2_set(const std::string& file);

	template<typename Real>
	std::ostream& operator<<(std::ostream& os,
							 const Point_2<Real>& p);
	template<typename Real>
	std::ostream& operator<<(std::ostream& os,
							 const Segment_2<Real>& s);

	template<typename Real>
	void save_point_2_set(const std::string& file,
						  const std::vector<Point_2<Real>>& points);
	template<typename Real>
	void save_segment_2_set(const std::string& file,
							const std::vector<Segment_2<Real>>& segments);


	// +-----------------------------------------------------------------------+
	// |                         TEMPLATE DEFINITIONS                          |
	// +-----------------------------------------------------------------------+

	template<typename Real>
	std::istream& operator>>(std::istream& is,
							 Point_2<Real>& p)
	{
		is >> p.x
		   >> p.y;
		return is;
	}

	template<typename Real>
	std::istream& operator>>(std::istream& is,
							 Segment_2<Real>& s)
	{
		is >> s.p1.x
		   >> s.p1.y
		   >> s.p2.x
		   >> s.p2.y;
		return is;
	}

	template<typename Real>
	std::istream& operator>>(std::istream& is,
							 std::vector<Point_2<Real>>& points)
	{
		points.clear();
		unsigned n;
		is >> n;

		for (unsigned i = 0; i < n; ++i)
		{
			points.template emplace_back();
			is >> points.back();
		}

		return is;
	}

	template<typename Real>
	std::istream& operator>>(std::istream& is,
							 std::vector<Segment_2<Real>>& segments)
	{
		segments.clear();
		unsigned n;
		is >> n;

		for (unsigned i = 0; i < n; ++i)
		{
			segments.template emplace_back();
			is >> segments.back();
		}

		return is;
	}

	template<typename Real>
	std::vector<Point_2<Real>> load_point_2_set(const std::string& file)
	{
		std::filesystem::path project_dir
				= utils::get_project_directory();
		std::ifstream ifs(project_dir / file);

		std::vector<Point_2<Real>> points;
		ifs >> points;

		return points;
	}

	template<typename Real>
	std::vector<Segment_2<Real>> load_segment_2_set(const std::string& file)
	{
		std::filesystem::path project_dir
				= utils::get_project_directory();
		std::ifstream ifs(project_dir / file);

		std::vector<Segment_2<Real>> segments;
		ifs >> segments;
		return segments;
	}

	template<typename Real>
	std::ostream& operator<<(std::ostream& os,
							 const Point_2<Real>& p)
	{
		os << p.x << " " << p.y;
		return os;
	}

	template<typename Real>
	std::ostream& operator<<(std::ostream& os,
							 const Segment_2<Real>& s)
	{
		os << s.p1 << " " << s.p2;
		return os;
	}

	template<typename Real>
	void save_point_2_set(const std::string& file,
						  const std::vector<Point_2<Real>>& points)
	{
		std::filesystem::path data_dir = utils::get_data_directory();
		std::ofstream ofs(data_dir / file);

		unsigned n = points.size();
		ofs << n << std::endl;

		for (unsigned i = 0; i < n; ++i)
		{
			ofs << points[i] << std::endl;
		}
	}

	template<typename Real>
	void save_segment_2_set(const std::string& file,
							const std::vector<Segment_2<Real>>& segments)
	{
		std::filesystem::path data_dir = utils::get_data_directory();
		std::ofstream ofs(data_dir / file);

		unsigned n = segments.size();
		ofs << n << std::endl;

		for (unsigned i = 0; i < n; ++i)
		{
			ofs << segments[i] << std::endl;
		}
	}
}