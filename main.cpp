#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<string>
#include<iomanip>

/* Basic parameter */
double lx = 1.0;
double kappa = 1.0;
double t = 0.0;
int nx = 11;
double dx = lx/(nx - 1);
double dt = 1./50;
double alpha = kappa*dt/(dx * dx);

std::vector<double> tdma(int n, std::vector<double> a, std::vector<double> b, std::vector<double> c, std::vector<double> r){
	std::vector<double> xx(n);
	for(int i = 1; i < n; i++){
		b[i] = b[i] - c[i-1]/b[i-1]*a[i];
		r[i] = r[i] - r[i-1]/b[i-1]*a[i];
	}
	xx[n-1] = r[n-1]/b[n-1];
	for(int i = 1; i < n; i++)
		xx[n-1-i] = (r[n-1-i] - c[n-1-i]*xx[n-i])/b[n-1-i];
	return xx;
}

void output(std::vector<double> x, std::vector<double> u, double time){
	std::string filename = "test_" + std::to_string(time) + ".txt";
	std::ofstream out{filename};
	for(int i = 0; i < x.size(); i++)
		out << std::setprecision(5) << x[i] << '\t' << std::setprecision(7) << u[i] << std::endl;
	out.close();
}

std::vector<double> linspace(double begin, double end, int nx){
	std::vector<double> lin;
	double delta = (end - begin) / (nx - 1);
	for(int i = 0; i < nx; i++) lin.push_back(begin + i * delta);
	return lin;
}

void implicit_euler(std::vector<double>& u){
	std::vector<double> a(nx - 2);
	std::vector<double> b(nx - 2);
	std::vector<double> c(nx - 2);
	std::vector<double> r(nx - 2);
	std::vector<double> up1(nx - 2);
	std::vector<double> u_tmp(nx); std::copy(u.begin(), u.end(), u_tmp.begin());
	for(int i = 1; i < nx - 1;i ++){
		a[i - 1] = -alpha;
		b[i - 1] = 1. + 2. * alpha;
		c[i - 1] = -alpha;
		r[i - 1] = u[i];
	}
		r[0] = r[0] -a[0] * u[0];
		r[nx-3] = r[nx - 3] - c[nx-3]*u[nx-1];
		up1 = tdma(nx-2, a, b, c, r);
		std::copy(up1.begin(), up1.end(), u_tmp.begin() + 1);
		std::copy(u_tmp.begin() + 1, u_tmp.end() - 1, u.begin() + 1);
}

int main(void){
	std::cout << "alpha = " << alpha;
	std::cout << ", dt = " << dt;
	std::cout << ", dx = " << dx << std::endl;
	std::vector<double> u(nx); std::fill(u.begin(), u.end(), 1.0);
	u[0] = 0.0; u[nx-1] = 0.0;
	auto x = linspace(0, lx, nx);
	while(t < 1.0){
		t += dt;
		implicit_euler(u);
		output(x, u, t);
	}
}
