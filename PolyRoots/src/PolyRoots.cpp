#include "PolyRoots.h"
#include "Config.h"

#include <iostream>
#include <cmath>
#include <algorithm>

std::vector<double> derivativeFromPoly(const std::vector<double>& coeffs) {

	std::vector<double> derivative; 
	const int degree = coeffs.size()-1;

	for (int i = 0;i < degree;i++) {
		derivative.emplace_back(coeffs[i] * (degree-i));
	}

	return derivative;
}

std::string polyFromVector(const std::vector<double>& coeffs) {
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

double zeroFromLinear(const std::vector<double>& coeffs){
	if (coeffs.size() > 2)throw std::invalid_argument("Vector does not represent a linear polynomial OR none zero point");

	return coeffs[1] * (-1) / coeffs[0];
}

double valueAtX(const std::vector<double>& coeffs,const double& x) {
	const int size = coeffs.size(); //3 x^(2) +  5x^(1) - 4     

	double y = coeffs[0];
	for (int i = 1;i < size;i++) {
		y = y * x + coeffs[i];
	}

	return y;
}

Point classifyRoot(const std::vector<double>& coeffs) {

	if (coeffs.size() != 2)throw std::invalid_argument("Vector does not represent a linear polynomial");
	
	double p = zeroFromLinear(coeffs);

	if (valueAtX(coeffs, p - DELTA) < 0) {
		return Point(p,MINIMUM);
	}
	else {
		return Point(p,MAXIMUM);
	}

}

Point rootExtremumType(const std::vector<double>& coeffs, const double x) {
	
	//double deb = std::fabs(valueAtX(coeffs, x));
	
	if (std::fabs(valueAtX(coeffs, x)) > DELTA)throw std::invalid_argument("x is not zero point");

	if (valueAtX(coeffs, x - DELTA) > 0)return Point(x, MAXIMUM);
	return Point(x, MINIMUM);
}

double bisection(const  std::vector<double>& coeffs, double left, double right) {
	if(left>right) throw std::invalid_argument("Wrong interval");

	double value_left = valueAtX(coeffs, left);
	double value_right = valueAtX(coeffs, right);

	if (value_left == 0.0)return left;
	if (value_right == 0.0)return right;

	if(value_left < 0 && value_right < 0 || value_left > 0 && value_right > 0)throw std::invalid_argument("Not 1 zero point");
	
	bool left_positive = value_left > 0;

	while (std::fabs(left - right) > PRECISION) {

		double midle = (left + right) / 2.0;
		double value_midle = valueAtX(coeffs, midle);

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

double findRootNewton(const std::vector<double>& coeffs, double root) {
	const std::vector<double> derivative = derivativeFromPoly(coeffs);

	for (int i = 0;i < PRECISION_NEWTON;i++) {
		root = root - (valueAtX(coeffs,root)/valueAtX(derivative, root));
	}

	return root;
}

double findRootHybrid(const std::vector<double>& coeffs, double left, double right){
	return findRootNewton(coeffs, bisection(coeffs, left, right));
}

std::vector<Point> extremumPoly(const std::vector<double>& coeffs, bool isTarget) {
	std::vector<double> derivative = derivativeFromPoly(coeffs);

	if (derivative.size() <= 1) return {};
	if (derivative.size() == 2) return { classifyRoot(derivative) };

	std::vector<Point> extrema;
	std::vector<double> zeros = rootsPoly(derivative,false);
	for (const auto& x : zeros) {
		if (isTarget || !isZeroPoint(coeffs, x)) extrema.push_back(rootExtremumType(derivative, x));
	}

	return extrema;
}

std::vector<Point> extremumPolyWithoutDouble(const std::vector<double>& coeffs) {
	std::vector<double> derivative = derivativeFromPoly(coeffs);

	if (derivative.size() <= 1) return {};
	if (derivative.size() == 2) return { classifyRoot(derivative) };

	std::vector<Point> extrema;
	std::vector<double> zeros = rootsPoly(derivative,false);
	for (const auto& x : zeros) {
		if(!isZeroPoint(coeffs,x))extrema.push_back(rootExtremumType(derivative, x));
	}

	return extrema;
}

std::vector<double> rootsPoly(const std::vector<double>& coeffs,bool isTarget) {
	if (coeffs.size() == 2)return {zeroFromLinear(coeffs)};
	
	std::vector<Point> extrema;

	extrema=extremumPoly(coeffs, isTarget);


	std::vector<double> range;

	
	if(!extrema.empty() && isExtremumHaveRoot(coeffs, extrema[0])) range.push_back(-1000);

	std::vector<double> roots;

	if (isTarget) {
		std::cout << "";
	}

	for (int i = 0; i < extrema.size();i++) {
		if (isExtremumHaveRoot(coeffs, extrema[i])) {
			range.push_back(extrema[i].x);
		}else {  //watch out
			if(!range.empty())range.pop_back();
		}
	}

	if(extrema[extrema.size()-1].state!=MAXIMUM)range.push_back(1000);
	
	for (int i = 1;i < range.size();i++) {
		roots.push_back(findRootHybrid(coeffs,range[i-1],range[i]));
	}

	return roots;
}

bool isExtremumHaveRoot(const std::vector<double>& coeffs,const Point& p) {
	double y = valueAtX(coeffs, p.x);
	if (y > 0 && p.state == MINIMUM)return false;
	if (y < 0 && p.state == MAXIMUM)return false;

	return true;
}

bool isZeroPoint(const std::vector<double>& coeffs, const double x) {
	if (std::fabs(valueAtX(coeffs, x)) > DELTA)return false;
	return true;
}