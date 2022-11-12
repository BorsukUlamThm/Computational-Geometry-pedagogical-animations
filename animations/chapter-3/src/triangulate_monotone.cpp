#include "../include/triangulate_monotone.h"
#include "geometry/utils/point_comparisons.h"


namespace polygon_triangulation
{
	bool are_on_different_chains(vertex* v1,
								 vertex* v2)
	{
		bool chain1 = geo::point_above_point(v1, v1->inc_edge->next->origin);
		bool chain2 = geo::point_above_point(v2, v2->inc_edge->next->origin);
		return chain1 != chain2;
	}

	bool wrong_turn(const stack& S,
					vertex* v)
	{
		unsigned n = S.size();
		if (n < 2)
		{ return false; }

		if (geo::point_above_point(v, v->inc_edge->next->origin))
		{// we are on left chain
			return geo::point_left_line(v, S[n - 2], S[n - 1]);
		}
		else
		{// we are on right chain
			return geo::point_right_line(v, S[n - 2], S[n - 1]);
		}
	}

	void plot_stack(const stack& S,
					gr::Animation& animation)
	{
		animation[STACK].clear();
		for (unsigned i = 1; i < S.size(); ++i)
		{
			gr::Coordinate x1(S[i - 1]->x);
			gr::Coordinate y1(S[i - 1]->y);
			gr::Coordinate x2(S[i]->x);
			gr::Coordinate y2(S[i]->y);

			animation[STACK].add_segment(x1, y1, x2, y2, gr::GREEN);
		}
	}

	void triangulate_monotone(DCEL& D,
							  face* f,
							  gr::Animation& animation)
	{
		plot_monotone_face(f, animation);
		animation.make_new_frame();

		queue Q = init_Q_and_inc_edges(f);
		gr::Coordinate y(Q[0]->y);
		animation[LINE].add_horizontal_line(y);
		animation.make_new_frame();

		stack S;
		S.push_back(Q[0]);
		S.push_back(Q[1]);

		plot_stack(S, animation);
		y = gr::Coordinate(Q[1]->y);
		animation[LINE].clear();
		animation[LINE].add_horizontal_line(y);
		animation.make_new_frame();

		std::vector<diagonal> diags;
		for (unsigned i = 2; i < Q.size() - 1; ++i)
		{
			y = gr::Coordinate(Q[i]->y);
			animation[LINE].clear();
			animation[LINE].add_horizontal_line(y);
			animation.make_new_frame();

			if (are_on_different_chains(Q[i], S.back()))
			{
				while (S.size() > 1)
				{
					vertex* v = S.back();
					plot_stack(S, animation);
					add_diagonal(Q[i], v, diags, animation);
					S.pop_back();
				}

				S.pop_back();
				S.push_back(Q[i - 1]);
				S.push_back(Q[i]);
				plot_stack(S, animation);
				animation.make_new_frame();
			}
			else
			{
				while (wrong_turn(S, Q[i]))
				{
					S.pop_back();
					plot_stack(S, animation);
					add_diagonal(Q[i], S.back(), diags, animation);
				}
				S.push_back(Q[i]);
				plot_stack(S, animation);
				animation.make_new_frame();
			}
		}

		S.pop_back();
		while (S.size() > 1)
		{
			vertex* v = S.back();
			plot_stack(S, animation);
			add_diagonal(Q.back(), v, diags, animation);
			S.pop_back();
		}

		animation[LINE].clear();
		animation[STACK].clear();
		animation[MONOTONE_FACE].clear();
		animation.make_new_frame();
	}
}