using LinearAlgebra;
lx = 1.0;
nx = 11;
dx = lx / (nx - 1);
dt = 1.0/100;
t = 0.0;
tlim = 0.1;
kappa = 1.0
alpha = dt * kappa / (dx^2);

function linspace(start::Number, stop::Number, n::Int64)
	linx = zeros(Float64, n);
	delta = (stop - start) / (n - 1);
	for i = 1:n
		linx[i] = start + delta * (i - 1)
	end
	return linx;
end

function solve_linear(n::Int64, a::Float64, b::Float64, c::Float64, r::Array)
	A = zeros(n, n);
	for i = 2:n+1
		for j = 2:n+1
			if(i-1 == j-1-1)
				A[i-1, j-1] = c;
			elseif (i-1==j-1)
				A[i-1,j-1] = b;
			elseif (i-1-1 == j-1)
				A[i-1,j-1] = a;
			end
		end
	end
	return A \ r;
end

function implicit_euler(u::Array)
	a = Float64(0.0);
	b = Float64(0.0);
	c = Float64(0.0);
	r = zeros(Float64, nx - 2);
	for i = 2:nx-1
		a = -alpha;
		b = 1.0 + 2alpha;
		c = -alpha;
		r[i-1] = u[i];
	end
	r[begin] = r[begin] - a[begin]*u[begin]
	r[end] = r[end] - c[end] * u[end];
	u[2:end-1] = solve_linear(nx - 2, a, b, c, r) 
end

function output(x::Array, u::Array, t::Float64)
	open("implicit-euler" * string(t) * ".dat", "w") do io
		for i = 1:nx
			write(io, string(x[i]) * "\t" * string(u[i]) * "\n");
		end
	end;
end

function main()
	t = 0.0
	u = ones(Float64, nx);
	u[begin] = u[end] = 0.0;
	x = linspace(0, lx, nx);
	while t < tlim
		implicit_euler(u);
		output(x, u, t);
		t = t + dt;
	end
end

main()