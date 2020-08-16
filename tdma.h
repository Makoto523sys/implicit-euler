#ifndef _TDMA_H_
#define _TDMA_H_
#include<vector>
#include<iostream>

/**
 * Thomas Algorithm
 * We think simultaneous equation like below
 * b1*x1 + c1*x2				= d1
 * a2*x1 + b2*x2 + c2*x3 			= d2
 *         a3*x2 + b3*x3 + c3*x4		= d3
 *         .....
 *         an-1*xn-2 + bn-1*xn-1 + cn-1*xn	= dn-1
 *                     an-1*xn-1 + bn*xn	= dn
 * Thomas algorithm allows us to solve it quickly.I show basically flow in the following.
 * Step 1:Set g1 = b1, s1 = d1
 * Step 2:For i from 2 to n, set gi = bi - ai*ci-1 / gi-1, si = di - ai * si-1 / gi-1
 * Step 3:Set xn = sn / gn
 * Step 4:For i from n - 1 to 1, set xi = (si - ci*xi+1)/gi
 * */ 

inline std::vector<double> tdma(std::vector<double> a, std::vector<double> b, std::vector<double> c, std::vector<double> r);

std::vector<double> tdma(std::vector<double> a, std::vector<double> b, std::vector<double> c, std::vector<double> r){
	int n = a.size();
	std::vector<double> ans(n);
	std::vector<double> g(n); g[0] = b[0];
	std::vector<double> s(n); s[0] = r[0];
	ans[0] = s[0] / g[0];

	for(int i = 1; i < n; i++){
		g[i] = b[i] - a[i] * c[i - 1] / g[i - 1];
		s[i] = r[i] - a[i] * s[i - 1] / g[i - 1];
		ans[i] = s[i] / g[i];
	}

	for(int i = n - 2; i >= 0; i--) ans[i] = (s[i] - c[i] * ans[i + 1]) / g[i];
	return ans;
}
#endif
