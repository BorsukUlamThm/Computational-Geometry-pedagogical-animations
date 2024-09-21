#include "geometry/model/serialization.h"
#include "geometry/algorithms/segment_intersections.h"
#include "utils/file_management.h"


namespace geometry
{
	integer str_to_integer(const std::string& str)
	{
		integer n = 0;

		unsigned i = 0;
		integer sgn = 1;
		if (str[0] == '-')
		{
			sgn = -1;
			++i;
		}


		for (; i < str.size(); ++i)
		{
			integer digit = str[i] - '0';
			n += digit;
			n *= 10;
		}
		n /= 10;

		return sgn * n;
	}

	std::istream& operator>>(std::istream& is,
							 number& x)
	{
		std::string str;
		is >> str;

		std::string num;
		std::string den;
		unsigned i = 0;
		while (i < str.size() && str[i] != '/')
		{
			num += str[i];
			++i;
		}
		if (i == str.size())
		{
			den = "1";
		}
		else
		{
			den = str.substr(i + 1, str.size() - i - 1);
		}

		integer p = str_to_integer(num);
		integer q = str_to_integer(den);
		x = number(p) / number(q);

		return is;
	}

	std::istream& operator>>(std::istream& is,
							 point_2& p)
	{
		is >> p.x
		   >> p.y;
		return is;
	}

	std::istream& operator>>(std::istream& is,
							 segment_2& s)
	{
		is >> s.p1.x
		   >> s.p1.y
		   >> s.p2.x
		   >> s.p2.y;
		return is;
	}

	std::istream& operator>>(std::istream& is,
							 std::vector<point_2>& points)
	{
		points.clear();
		unsigned n;
		is >> n;

		for (unsigned i = 0; i < n; ++i)
		{
			points.emplace_back();
			is >> points.back();
		}

		return is;
	}

	std::istream& operator>>(std::istream& is,
							 std::vector<segment_2>& segments)
	{
		segments.clear();
		unsigned n;
		is >> n;

		for (unsigned i = 0; i < n; ++i)
		{
			segments.emplace_back();
			is >> segments.back();
		}

		return is;
	}

	std::vector<point_2> load_point_2_set(const std::string& file)
	{
		std::filesystem::path data_dir = utils::get_data_directory();
		std::ifstream ifs(data_dir / file);

		if (!ifs.is_open())
		{
			std::cerr << "invalid file read " << file << std::endl;
		}

		std::vector<point_2> points;
		ifs >> points;

		return points;
	}

	std::vector<segment_2> load_segment_2_set(const std::string& file)
	{
		std::filesystem::path data_dir = utils::get_data_directory();
		std::ifstream ifs(data_dir / file);

		if (!ifs.is_open())
		{
			std::cerr << "invalid file read " << file << std::endl;
		}

		std::vector<segment_2> segments;
		ifs >> segments;
		return segments;
	}

	DCEL load_DCEL(const std::string& file)
	{
		std::filesystem::path data_dir = utils::get_data_directory();
		std::ifstream ifs(data_dir / file);

		if (!ifs.is_open())
		{
			std::cerr << "invalid file read " << file << std::endl;
		}

		std::vector<segment_2> edges = load_segment_2_set(file);
		return segment_intersections(edges);
	}

	std::ostream& operator<<(std::ostream& os,
							 const number& x)
	{
		if (x.val.denominator() == 1)
		{
			os << x.val.numerator();
		}
		else
		{
			os << x.val;
		}
		return os;
	}

	std::ostream& operator<<(std::ostream& os,
							 const point_2& p)
	{
		os << p.x << " " << p.y;
		return os;
	}

	std::ostream& operator<<(std::ostream& os,
							 const segment_2& s)
	{
		os << s.p1 << " " << s.p2;
		return os;
	}

	void save_point_2_set(const std::string& file,
						  const std::vector<point_2>& points)
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

	void save_segment_2_set(const std::string& file,
							const std::vector<segment_2>& segments)
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

	void save_DCEL(const std::string& file,
				   DCEL& D)
	{
		std::filesystem::path data_dir = utils::get_data_directory();
		std::ofstream ofs(data_dir / file);

		unsigned n = D.half_edges.size() / 2;
		ofs << n << std::endl;

		DCEL::mark_t m = D.get_new_mark();
		for (auto& h : D.half_edges)
		{
			if (h->twin->is_marked(m))
			{ continue; }

			ofs << h->origin->x << " " << h->origin->y << " "
				<< h->twin->origin->x << " " << h->twin->origin->y
				<< std::endl;

			h->mark(m);
		}

		D.free_mark(m);
	}
}