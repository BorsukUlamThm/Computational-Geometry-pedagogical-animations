#pragma once

#include <fstream>
#include <vector>
#include "utils/file_management.h"
#include "point.h"
#include "segment.h"


namespace geometry
{
	std::istream& operator>>(std::istream& is,
							 real& x);
	std::istream& operator>>(std::istream& is,
							 point& p);
	std::istream& operator>>(std::istream& is,
							 segment& s);

	std::istream& operator>>(std::istream& is,
							 std::vector<point>& points);
	std::istream& operator>>(std::istream& is,
							 std::vector<segment>& segments);

	/*!
	 * Construct a vector of point from a file\n
	 * Format :\n
	 * - first an integer n, the number of points to read
	 * - then n pairs of numbers (x, y) which represent the n points
	 */
	std::vector<point> load_point_2_set(const std::string& file);
	/*!
	 * Construct a vector of segment from a file\n
	 * Format :\n
	 * - first an integer n, the number of segments to read
	 * - then n lists of four numbers (x1, y1, x2, y2) which represent the n
	 * segments
	 */
	std::vector<segment> load_segment_2_set(const std::string& file);

	std::ostream& operator<<(std::ostream& os,
							 const real& x);
	std::ostream& operator<<(std::ostream& os,
							 const point& p);
	std::ostream& operator<<(std::ostream& os,
							 const segment& s);

	/*!
	 * Saves the points in a file\n
	 * Format :\n
	 * - first an integer n, the number of points to save
	 * - then n pairs of numbers (x, y) which represent the n points
	 */
	void save_point_2_set(const std::string& file,
						  const std::vector<point>& points);
	/*!
	 * Saves the segments in a file\n
	 * Format :\n
	 * - first an integer n, the number of segments to save
	 * - then n lists of four numbers (x1, y1, x2, y2) which represent the n
	 * segments
	 */
	void save_segment_2_set(const std::string& file,
							const std::vector<segment>& segments);
}