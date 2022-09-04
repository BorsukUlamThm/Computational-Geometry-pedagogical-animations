#pragma once

#include <fstream>
#include <vector>
#include "utils/file_management.h"
#include "Point_2.h"
#include "Segment_2.h"


namespace geometry
{
	template<typename real>
	std::istream& operator>>(std::istream& is,
							 Point_2<real>& p);
	template<typename real>
	std::istream& operator>>(std::istream& is,
							 Segment_2<real>& s);

	template<typename real>
	std::istream& operator>>(std::istream& is,
							 std::vector<Point_2<real>>& points);
	template<typename real>
	std::istream& operator>>(std::istream& is,
							 std::vector<Segment_2<real>>& segments);

	/*!
	 * Construct a vector of Point_2 from a file\n
	 * Format :\n
	 * - first an integer n, the number of points to read
	 * - then n pairs of numbers (x, y) which represent the n points
	 */
	template<typename real>
	std::vector<Point_2<real>> load_point_2_set(const std::string& file);
	/*!
	 * Construct a vector of Segment_2 from a file\n
	 * Format :\n
	 * - first an integer n, the number of segments to read
	 * - then n lists of four numbers (x1, y1, x2, y2) which represent the n
	 * segments
	 */
	template<typename real>
	std::vector<Segment_2<real>> load_segment_2_set(const std::string& file);

	template<typename real>
	std::ostream& operator<<(std::ostream& os,
							 const Point_2<real>& p);
	template<typename real>
	std::ostream& operator<<(std::ostream& os,
							 const Segment_2<real>& s);

	/*!
	 * Saves the points in a file\n
	 * Format :\n
	 * - first an integer n, the number of points to save
	 * - then n pairs of numbers (x, y) which represent the n points
	 */
	template<typename real>
	void save_point_2_set(const std::string& file,
						  const std::vector<Point_2<real>>& points);
	/*!
	 * Saves the segments in a file\n
	 * Format :\n
	 * - first an integer n, the number of segments to save
	 * - then n lists of four numbers (x1, y1, x2, y2) which represent the n
	 * segments
	 */
	template<typename real>
	void save_segment_2_set(const std::string& file,
							const std::vector<Segment_2<real>>& segments);


	// +-----------------------------------------------------------------------+
	// |                         TEMPLATE DEFINITIONS                          |
	// +-----------------------------------------------------------------------+

	template<typename real>
	std::istream& operator>>(std::istream& is,
							 Point_2<real>& p)
	{
		is >> p.x
		   >> p.y;
		return is;
	}

	template<typename real>
	std::istream& operator>>(std::istream& is,
							 Segment_2<real>& s)
	{
		is >> s.p1.x
		   >> s.p1.y
		   >> s.p2.x
		   >> s.p2.y;
		return is;
	}

	template<typename real>
	std::istream& operator>>(std::istream& is,
							 std::vector<Point_2<real>>& points)
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

	template<typename real>
	std::istream& operator>>(std::istream& is,
							 std::vector<Segment_2<real>>& segments)
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

	template<typename real>
	std::vector<Point_2<real>> load_point_2_set(const std::string& file)
	{
		std::filesystem::path data_dir = utils::get_data_directory();
		std::ifstream ifs(data_dir / file);

		std::vector<Point_2<real>> points;
		ifs >> points;

		return points;
	}

	template<typename real>
	std::vector<Segment_2<real>> load_segment_2_set(const std::string& file)
	{
		std::filesystem::path data_dir = utils::get_data_directory();
		std::ifstream ifs(data_dir / file);

		std::vector<Segment_2<real>> segments;
		ifs >> segments;
		return segments;
	}

	template<typename real>
	std::ostream& operator<<(std::ostream& os,
							 const Point_2<real>& p)
	{
		os << p.x << " " << p.y;
		return os;
	}

	template<typename real>
	std::ostream& operator<<(std::ostream& os,
							 const Segment_2<real>& s)
	{
		os << s.p1 << " " << s.p2;
		return os;
	}

	template<typename real>
	void save_point_2_set(const std::string& file,
						  const std::vector<Point_2<real>>& points)
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

	template<typename real>
	void save_segment_2_set(const std::string& file,
							const std::vector<Segment_2<real>>& segments)
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