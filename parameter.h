#ifndef _PRAMETER_H_
#define _PRAMETER_H_
class parameter{
	/**
	 *I will declare some variables to solve PDE easily.
	 * The variables are shown below.
	 * kappa.This is thermal diffusion coefficient.In most cases, kappa is set to 1.0.
	 * l.    This is the length of wire.The l is also set to 1.0.
	 * nx	 This is the variable how many pieces of wire to split
	 * dx	 This is the space split.It is determined as l / nx.
	 * dt	 This is the time split.
	 * alpha This variable is determined as kappa * dt / dx
	 * */
	double kappa = 1.0;
	double l = 1.0;
	int nx;
	double dx;
	double dt;
	double alpha;
	parameter(double _kappa, double _l, int _nx, double _dt): kappa(_kappa), l(_l), nx(_nx), dt(_dt){
		dx = l / nx;
		alpha = kappa * dt / dx;
	}
	parameter(int _nx, double _dt): nx(_nx), dt(_dt){
		dx = l / nx;
	        alpha = kappa * dt / dx;
	}
};
#endif
