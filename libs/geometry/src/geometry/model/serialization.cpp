#include "geometry/model/serialization.h"
#include "geometry/algorithms/segment_intersections.h"
#include "utils/file_management.h"


namespace geometry
{
	std::istream& operator>>(std::istream& is,
							 real& x)
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

		real::integer p = std::stoi(num);
		real::integer q = std::stoi(den);
		x = real(p) / real(q);

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
			points.template emplace_back();
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
			segments.template emplace_back();
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
							 const real& x)
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