#include <iostream>
#include <vector>
#include "PolyRoots.h"  

int main() {
    std::vector<double> input = { 0.25, 0, -1.5, 2, 0 };//{1,0,-3,2};
    std::cout << polyFromVector(input) << std::endl; 

    std::vector<Point> extrema = extremumPoly(input);
    std::cout << "Extrema:" << std::endl;
    for (const auto& e : extrema) {
        std::cout << e.x << " ";
        if (e.state == MAXIMUM)std::cout << "MAXIMUM" << std::endl;
        if (e.state == MINIMUM)std::cout << "MINIMUM" << std::endl;
    }

    std::vector<double> roots = rootsPoly(input,true);
    std::cout << "Roots:" << std::endl;
    for (const auto& r : roots)std::cout << r << std::endl;

    return 0;
}
