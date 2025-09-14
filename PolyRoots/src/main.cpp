#include <iostream>
#include "PolyRoots.h"

int main()
{
    std::vector<double> input = {3,5,-4};  //3 x^(2) +  x^(1) - 4
    double x = 2;
    std::cout << bisection_between_2_points(input,0,1000, 1e-5);
  
    

}
