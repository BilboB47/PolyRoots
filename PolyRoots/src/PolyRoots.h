#pragma once
#include <vector>
#include <string>

std::string make_poly_from_vector(std::vector<double>& v);

std::vector<double> make_derivative_from_poly(std::vector<double>& coeffs);

double point_zero_from_linear(std::vector<double>& v);

