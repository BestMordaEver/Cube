#ifndef SOLVER_H
#define SOLVER_H

#include <list>
#include <vector>
#include "spin.h"

class Solver
{
public:
	std::vector<spin> Solve();
	void rotate(spin s);

private:
	char white[9] = { 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w' },
	red[9] = { 'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r' },
	orange[9] = { 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o' },
	blue[9] = { 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b' },
	green[9] = { 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g' },
	yellow[9] = { 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y' };

	std::vector<spin> way;

	bool rotate_clock(char choice);
	void print();
	void rotate_counter_clock(char choice);
	void swap(char &a, char &b);
	void white_bottom(char q);
	void right_alg(char a, char c);
	void white_right(char q);
	void left_alg(char a, char c);
	void white_left(char q);
	void top_alg(char a, char b, char c);
	void white_top(char q);
	void inv_alg(char a, char b, char c);
	void white_bottom_inverted(char q);
	void solve_white_cross();
	void white_corners_alg_left();
	void white_corners_alg_right();
	void solve_white_corners();
	void middle_place_left_alg(char left, char center);
	void middle_place_right_alg(char center, char right);
	void solve_middle_layer();
	void yellow_cross_algorithm();
	void solve_yellow_cross();
	void yellow_corners_algorithm();
	void solve_yellow_corners();
	void yellow_corner_orientation_algorithm();
	void yellow_corner_orientation();
	void yellow_edges_colour_arrangement_right();
	void yellow_edges_colour_arrangement_left();
	void yellow_edges_colour_arrangement();
};

#endif // SOLVER_H
