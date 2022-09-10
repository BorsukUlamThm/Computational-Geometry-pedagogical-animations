#include <map>
#include "segment_intersections_events.h"
#include "geometry/utils/point_comparisons.h"
#include "geometry/utils/point_comparisons.h"


namespace segment_intersections_events
{
	bool queue_cmp::operator()(const event& e1,
							   const event& e2) const
	{
		return geo::point_below_point(e1.p, e2.p);
	}

	event::event(const point& p,
				 gr::Animation* animation,
				 tree* T,
				 queue* Q) :
			p(p),
			animation(animation),
			T(T),
			Q(Q)
	{}

	void event::handle() const
	{
		auto y = boost::rational_cast<gr::Coordinate>(p.y);
		//		auto y = gr::Coordinate(p.y);
		animation->get(LINE).add_horizontal_line(y);
		animation->make_new_frame();

		std::cout << p << std::endl << "U :";
		for (auto& i : U)
			std::cout << " " << i;
		std::cout << std::endl << "L :";
		for (auto& i : L)
			std::cout << " " << i;
		std::cout << std::endl << std::endl;
	}

	queue init_queue_and_tree(segment_set& S,
							  gr::Animation& animation)
	{
		tree_cmp comp(S);
		tree T(comp);
		queue Q;

		struct point_cmp
		{
			bool operator()(const point& p,
							const point& q) const
			{
				if (p.x == q.x)
					return p.y < q.y;
				return p.x < q.x;
			}
		};
		std::map<point, event, point_cmp> map;

		for (unsigned i = 0; i < S.size(); ++i)
		{
			if (map.find(S[i].p1) == map.end())
			{
				map[S[i].p1] = event(S[i].p1, &animation, &T, &Q);
			}
			map[S[i].p1].U.push_back(i);

			if (map.find(S[i].p2) == map.end())
			{
				map[S[i].p2] = event(S[i].p2, &animation, &T, &Q);
			}
			map[S[i].p2].L.push_back(i);
		}

		for (auto& pair : map)
		{
			Q.push_event(pair.second);
		}

		return Q;
	}
}