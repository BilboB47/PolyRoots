#include "PolyRoots.h"
#include "Config.h"

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
	const int size = coeffs.size(); //3 x^(2) +  5x^(1) - 4     

	double y = coeffs[0];
	for (int i = 1;i < size;i++) {
		y = y * x + coeffs[i];
	}

	return y;
}

Point extrema_from_linear(const std::vector<double>& coeffs) {

	if (coeffs.size() != 2)throw std::invalid_argument("Vector does not represent a linear polynomial");
	
	double p = point_zero_from_linear(coeffs);

	if (value_of_poly_at_x(coeffs, p - PRECISION) < 0) {
		return Point(p,MINIMUM);
	}
	else {
		return Point(p,MAXIMUM);
	}

}

double bisection_extrema_between_2_points(const  std::vector<double>& coeffs, double left, double right) {
	if(left>right) throw std::invalid_argument("Wrong interval");

	double value_left = value_of_poly_at_x(coeffs, left);
	double value_right = value_of_poly_at_x(coeffs, right);

	if(value_left < 0 && value_right < 0 || value_left > 0 && value_right > 0)throw std::invalid_argument("Not 1 zero point");
	
	bool left_positive = value_left > 0;

	while (std::fabs(left - right) > PRECISION) {

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


	return (left + right) / 2.0;
}

Point extrema_from_zero(const std::vector<double>& coeffs,const double x){
	if(std::fabs(value_of_poly_at_x(coeffs,x)) > PRECISION*10)throw std::invalid_argument("x is not zero point");

	if (value_of_poly_at_x(coeffs, x - PRECISION) > 0)return Point(x,MAXIMUM);
	return Point(x, MINIMUM);
}

