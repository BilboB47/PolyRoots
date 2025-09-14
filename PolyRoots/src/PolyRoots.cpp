#include "PolyRoots.h"

#include <iostream>
#include <cmath>

std::vector<double> make_derivative_from_poly(const std::vector<double>& coeffs) {

	std::vector<double> derivative; 
	const int degree = coeffs.size()-1;

	for (int i = 0;i < degree;i++) {
		derivative.emplace_back(coeffs[i] * (degree-i));
	}

	return derivative;
}

std::string make_poly_from_vector(const std::vector<double>& coeffs) {
	const int degree = coeffs.size();
	if (degree < 1)return "";

	std::string poly = "";

	for (int i = 0;i < degree;i++) {
		if (coeffs[i] == 0)continue;

		if (coeffs[i] > 0 && i>0) poly += '+';
		poly += std::to_string(coeffs[i]);

		if (i == degree-1)break;
		poly += "x^";
		poly += std::to_string(degree-i-1);
	}

	return poly;
}

double point_zero_from_linear(const std::vector<double>& coeffs){
	if (coeffs.size() > 2)throw std::invalid_argument("Vector does not represent a linear polynomial OR none zero point");

	return coeffs[1] * (-1) / coeffs[0];
}

double value_of_poly_at_x(const std::vector<double>& coeffs,const double& x) {
	const int max_coeff = coeffs.size();
	double y = coeffs[max_coeff-1];
	double curr_power_x = x; 

	for (int i = 1;i < max_coeff;i++) {
		y += coeffs[max_coeff - i - 1] * curr_power_x;
		curr_power_x *= x;
	}

	return y;
}

Point extrema_from_linear(const std::vector<double>& coeffs) {

	if (coeffs.size() != 2)throw std::invalid_argument("Vector does not represent a linear polynomial");
	
	double p = point_zero_from_linear(coeffs);

	if (value_of_poly_at_x(coeffs, p - 1) < 0) {
		return {Point(p,MINIMUM)};
	}
	else {
		return { Point(p,MAXIMUM) };
	}

}

double bisection_between_2_points(const  std::vector<double>& coeffs, double left, double right, const double precision) {
	if(left>right) throw std::invalid_argument("Wrong interval");

	double value_left = value_of_poly_at_x(coeffs, left);
	double value_right = value_of_poly_at_x(coeffs, right);

	if(value_left < 0 && value_right < 0 || value_left > 0 && value_right > 0)throw std::invalid_argument("Wrong interval");
	
	bool left_positive = value_left > 0;

	while (std::fabs(left - right) > precision) {

		double midle = (left + right) / 2.0;
		double value_midle = value_of_poly_at_x(coeffs, midle);

		if (value_midle > 0) {
			if (left_positive) left = midle;
			else right = midle;
		}else {
			if (left_positive) right = midle;
			else left = midle;
		}

	}


	return left;
}