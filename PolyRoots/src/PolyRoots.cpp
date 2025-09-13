#include "PolyRoots.h"

#include <iostream>

std::vector<double> make_derivative_from_poly(std::vector<double>& coeffs) {

	std::vector<double> derivative; 
	const int degree = coeffs.size()-1;

	for (int i = 0;i < degree;i++) {
		derivative.emplace_back(coeffs[i] * (degree-i));
	}

	return derivative;
}

std::string make_poly_from_vector(std::vector<double>& v) {
	const int degree = v.size();
	if (degree < 1)return "";

	std::string poly = "";

	for (int i = 0;i < degree;i++) {
		if (v[i] == 0)continue;

		if (v[i] > 0 && i>0) poly += '+';
		poly += std::to_string(v[i]);

		if (i == degree-1)break;
		poly += "x^";
		poly += std::to_string(degree-i-1);
	}

	return poly;
}

double point_zero_from_linear(std::vector<double>& v){
	if (v.size() > 2)throw std::invalid_argument("Vector does not represent a linear polynomial OR none zero point");

	return v[1] * (-1) / v[0];
}