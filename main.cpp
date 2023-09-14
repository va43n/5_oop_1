#include "Header.h"

int main() {
	char mode = 'a';
	//args: 0 - mu1, 1 - la1, 2 - nu1;
	//args: 3 - mu2, 4 - la2, 5 - nu2;
	double* args, *moments;
	double x, *X;

	int n;

	srand(time(NULL));

	while (mode != 'd' && mode != 'm' && mode != 'e' && mode != 't') {
		std::cout << "Enter one of the available modes (d - default, m - mix, e - emperical, t - test): ";
		std::cin >> mode;
	}

	if (mode == 'd') {
		args = new double[3];
		enter(args, 3);

		std::cout << "Enter x: ";
		x = check_x(args[0], args[1]);

		//__________________________f(x)_______________________________
		std::cout << "f(" << x << ") = " << get_f(x, args[0], args[1], args[2]) << std::endl;
		//__________________________f(x)_______________________________

		//_________________________M, D, y1, y2________________________
		moments = get_moments(args[0], args[1], args[2]);
		std::cout << "M = " << moments[0] << std::endl;
		std::cout << "D = " << moments[1] << std::endl;
		std::cout << "y1 = " << moments[2] << std::endl;
		std::cout << "y2 = " << moments[3] << std::endl;
		//_________________________M, D, y1, y2________________________

		//___________________________model_____________________________
		std::cout << "x(" << args[0] << ", " << args[1] << ", " << args[2] << ") = " << get_model(args[0], args[1], args[2]) << std::endl;
		//___________________________model_____________________________

		std::cout << "Enter n: ";
		std::cin >> n;

		//X = new double[n];
		std::ofstream x_d_data, d_data;
		x_d_data.open("x_d_data.txt");
		d_data.open("d_data.txt");
		for (int i = 0; i < n; i++) {
			x = get_model(args[0], args[1], args[2]);
			x_d_data << write_in_file(x) << std::endl;
			d_data << write_in_file(get_f(x, args[0], args[1], args[2])) << std::endl;
		}
		x_d_data.close();
		d_data.close();
	}
	else if (mode == 'm') {
		double param;

		args = new double[6];
		enter(args, 6);

		std::cout << "Enter p: ";
		param = check_variables(4);

		std::cout << "Enter x: ";
		x = check_variables(3);

		//________________________mix f(x)_____________________________
		std::cout << "(p = " << param <<") mix_f(" << x << ") = " << get_mix_f(x, args, param) << std::endl;
		//________________________mix f(x)_____________________________

		//_______________________mix M, D, y1, y2______________________
		moments = get_mix_moments(args, param);
		std::cout << "(p = " << param << ") mix M = " << moments[0] << std::endl;
		std::cout << "(p = " << param << ") mix D = " << moments[1] << std::endl;
		std::cout << "(p = " << param << ") mix y1 = " << moments[2] << std::endl;
		std::cout << "(p = " << param << ") mix y2 = " << moments[3] << std::endl;
		//_______________________mix M, D, y1, y2______________________

		//_________________________mix model___________________________
		std::cout << "(p = " << param << ") mix x(" << args[0] << ", " << args[1] << ", " << args[2] << ", " << args[3] << ", " << args[4] << ", " << args[5] << ") = " << get_mix_model(args, param) << std::endl;
		//_________________________mix model___________________________
	}
	else if (mode == 'e') {
		int* counter, k;
		double delta, * frequency, * density, min, max, mu, la, nu;

		std::cout << "Enter n: ";
		n = check_variables(5);

		while (mode != 'r' && mode != 'd') {
			std::cout << "Enter one of the available modes (r - random, d - default): ";
			std::cin >> mode;
		}

		//args[i] - X[i]
		args = new double[n];

		if (mode == 'r') {
			for (int i = 0; i < n; i++) {
				args[i] = randomize_X();
			}
		}
		else {
			std::cout << "Enter mu, lambda, nu: ";
			std::cin >> mu >> la >> nu;
			for (int i = 0; i < n; i++) {
				args[i] = get_model(mu, la, nu);
			}
		}
		k = get_k(n);
		std::cout << "k = " << k << std::endl;

		min = get_min(args, n);

		delta = get_delta(args, n, k);

		counter = get_empirical_counter(args, delta, n, k, min);
		frequency = get_empirical_frequency(counter, n, k);
		density = get_empirical_density(counter, n, k, delta);

		for (int i = 0; i < k; i++) {
			std::cout << counter[i] << "     " << frequency[i] << "     " << density[i] << std::endl;
		}

		std::cout << "Enter x: ";
		x = check_variables(3);

		//_____________________empirical f(x)__________________________
		std::cout << "empirical_f(" << x << ") = " << get_empirical_f(x, density, k, delta, min) << std::endl;
		//_____________________empirical f(x)__________________________

		//____________________empirical M, D, y1, y2___________________
		moments = get_empirical_moments(args, n);
		std::cout << "empirical M = " << moments[0] << std::endl;
		std::cout << "empirical D = " << moments[1] << std::endl;
		std::cout << "empirical y1 = " << moments[2] << std::endl;
		std::cout << "empirical y2 = " << moments[3] << std::endl;
		//____________________empirical M, D, y1, y2___________________

		//______________________empirical model________________________
		std::cout << "(delta = " << delta << ", k = " << k <<", min = " << min << ") empirical x = " << get_empirical_model(frequency, delta, k, min) << std::endl;
		//______________________empirical model________________________
	}
	else if (mode == 't') {
		test();
	}

	return 0;
}