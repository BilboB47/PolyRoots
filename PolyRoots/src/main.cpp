#include <iostream>
#include <vector>
#include "PolyRoots.h"  

int main() {

   
    std::vector<double> input = { 1, -3, -3, 11, -6 };
    std::cout << polyFromVector(input) << std::endl; 

    std::vector<Point> extrema = extremumPoly(input);

    std::vector<double> roots = rootsPoly(input,true);
    std::cout << "Roots:" << std::endl;
    for (const auto& r : roots)std::cout << r << std::endl;



    return 0;
}
