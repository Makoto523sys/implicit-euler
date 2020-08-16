#include<iostream>
#include<vector>
#include "tdma.h"

/**************************************************
 * I'll show how to use tdma solver.Consider below
 * problem.
 * 
 * 		 x + 2y      = 1
 * 		3x + 4y + 5z = 2
 * 		     6y + 7z = 3
 * The solution to this equation is 
 * 		x = 0
 * 		y = 1/2
 * 		z = 0
 * nsion coefficient matrix of this system of 
 * simultaneous equations is 
 * 	1 2 0
 * 	3 4 5
 * 	0 6 7
 * In this case,
 * vector a means {0, 3, 6}
 * vector b means {1, 4, 7}
 * vector c means {2, 5, 0}
 * vector r means {1, 2, 3}
 * .Let's try.
 **************************************************/

int main(void){
	std::vector<double> a = {0, 3, 6};
	std::vector<double> b = {1, 4, 7};
	std::vector<double> c = {2, 5, 0};
	std::vector<double> r = {1, 2, 3};
	auto ans = tdma(a, b, c, r);
	for(int i = 0; i < ans.size(); i++) std::cout << "x_" << i << " = " << ans[i] << std::endl;
	return 0;
}
