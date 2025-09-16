#pragma once
#include <vector>
#include <string>

enum State { MINIMUM, MAXIMUM };

struct Point {
	double x;
	State state;
	Point(double x_val, State st) : x(x_val), state(st) {};
};

std::string polyFromVector(const std::vector<double>& coeffs);

std::vector<double> derivativeFromPoly(const std::vector<double>& coeffs);

double zeroFromLinear(const std::vector<double>& coeffs);

double valueAtX(const std::vector<double>& coeffs, const double& x);  

Point classifyRoot(const std::vector<double>& coeffs);

Point rootExtremumType(const std::vector<double>& coeffs, const double x);

double bisection(const std::vector<double>& coeffs,double left, double right);

double findRootNewton(const std::vector<double>& coeffs, double root);

double findRootHybrid(const std::vector<double>& coeffs, double left, double right);

std::vector<Point> extremumPoly(const std::vector<double>& coeffs);

std::vector<double> rootsPoly(const std::vector<double>& coeffs);

bool isExtremumHaveRoot(const std::vector<double>& coeffs, const Point& p);

bool isDoubleRoot(const std::vector<double>& coeffs, const double x);