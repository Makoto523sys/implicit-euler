#include<iostream>
#include<vector>
#include<cmath>

template<typename T>
std::vector<T> linspace(T begin, T end, int nx){
	std::vector<T> line;
	if(nx == 0) return line;
	else if(nx == 1){
		line.push_back(begin);
		return line;
	}
	double dx = std::fabs(end - begin) / (nx - 1);

	for(int i = 0; i < nx; i++) line.push_back(begin + dx * i);
	return line;
}
