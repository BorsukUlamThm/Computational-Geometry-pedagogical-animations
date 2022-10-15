#include "geometry/algorithms/segment_intersections.h"
#include "geometry/algorithms/segment_intersections_components/face_computation.h"
#include "geometry/algorithms/segment_intersections_components/intersections_test.h"
#include "geometry/algorithms/segment_intersections_components/sic_utils.h"
#include "geometry/algorithms/segment_intersections_components/sic_tree.h"
#include "geometry/algorithms/segment_intersections_components/sic_events.h"
#include <map>


namespace geometry
{
	namespace sic = segment_intersections_components;

	DCEL segment_intersections(const std::vector<segment_2>& S)
	{
		DCEL D = sic::brute_dcel(S);
		sic::tree T;
		//		T.plot_segments(S);
		sic::queue Q(D, T);

		Q.handle_events();

		sic::compute_faces(D);

		return D;
	}

	bool edge_intersections_test(const DCEL& D)
	{
		std::map<DCEL::hedge*, unsigned> map = sic::make_index_map(D);

		std::vector<DCEL::hedge*> up_events = sic::make_up_events(D);
		std::vector<DCEL::hedge*> down_events = sic::make_down_events(D);
		sic::tree T;

		while (up_events.size() + down_events.size() > 0)
		{
			DCEL::hedge* u = (up_events.empty() ? nullptr :
							  up_events[up_events.size() - 1]);
			DCEL::hedge* d = (down_events.empty() ? nullptr :
							  down_events[down_events.size() - 1]);

			if (u == nullptr)
			{
				if (intersection_test_handle_down_edge(d, map, T))
				{ return true; }
				down_events.pop_back();

				//				std::cout << T.depth() << std::endl;
				continue;
			}
			if (d == nullptr)
			{
				if (intersection_test_handle_up_edge(u, map, T))
				{ return true; }
				up_events.pop_back();

				//				std::cout << T.depth() << std::endl;
				continue;
			}

			if (sic::hedge_below_hedge(d, u))
			{
				if (intersection_test_handle_up_edge(u, map, T))
				{ return true; }
				up_events.pop_back();
			}
			else
			{
				if (intersection_test_handle_down_edge(d, map, T))
				{ return true; }
				down_events.pop_back();
			}

			//			std::cout << T.depth() << std::endl;
		}

		return false;
	}
}