#pragma once

#include <fstream>
#include <vector>
#include "point_2.h"
#include "segment_2.h"


namespace geometry
{
	std::istream& operator>>(std::istream& is,
							 real& x);
	std::istream& operator>>(std::istream& is,
							 point_2& p);
	std::istream& operator>>(std::istream& is,
							 segment_2& s);

	std::istream& operator>>(std::istream& is,
							 std::vector<point_2>& points);
	std::istream& operator>>(std::istream& is,
							 std::vector<segment_2>& segments);

	/*!
	 * Construct a vector of point from a file\n
	 * Format :\n
	 * - first an integer n, the number of points to read
	 * - then n pairs of numbers (x, y) which represent the n points
	 */
	std::vector<point_2> load_point_2_set(const std::string& file);
	/*!
	 * Construct a vector of segment from a file\n
	 * Format :\n
	 * - first an integer n, the number of segments to read
	 * - then n lists of four numbers (x1, y1, x2, y2) which represent the n
	 * segments
	 */
	std::vector<segment_2> load_segment_2_set(const std::string& file);

	std::ostream& operator<<(std::ostream& os,
							 const real& x);
	std::ostream& operator<<(std::ostream& os,
							 const point_2& p);
	std::ostream& operator<<(std::ostream& os,
							 const segment_2& s);

	/*!
	 * Saves the points in a file\n
	 * Format :\n
	 * - first an integer n, the number of points to save
	 * - then n pairs of numbers (x, y) which represent the n points
	 */
	void save_point_2_set(const std::string& file,
						  const std::vector<point_2>& points);
	/*!
	 * Saves the segments in a file\n
	 * Format :\n
	 * - first an integer n, the number of segments to save
	 * - then n lists of four numbers (x1, y1, x2, y2) which represent the n
	 * segments
	 */
	void save_segment_2_set(const std::string& file,
							const std::vector<segment_2>& segments);
}