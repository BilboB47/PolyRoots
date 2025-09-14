#pragma once
#include <vector>
#include <string>

enum State { MINIMUM, MAXIMUM };

struct Point {
	double x;
	State state;
	Point(double x_val, State st) : x(x_val), state(st) {};
};

std::string make_poly_from_vector(const std::vector<double>& coeffs);

std::vector<double> make_derivative_from_poly(const std::vector<double>& coeffs);

double point_zero_from_linear(const std::vector<double>& coeffs);

double value_of_poly_at_x(const std::vector<double>& coeffs, const double& x);  

Point extrema_from_linear(const std::vector<double>& coeffs);

double bisection_extrema_between_2_points(const std::vector<double>& coeffs,double left, double right);

Point extrema_from_zero(const std::vector<double>& coeffs,const double x);

