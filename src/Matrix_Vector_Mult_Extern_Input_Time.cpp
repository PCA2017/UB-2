//============================================================================
// Name        : Matrix_Vector_Mult_Extern_Input_Time.cpp
// Description : (nxm) * (mx1) = (nx1)
// 				 Multipliziert eine zufällig erzeugte Matrix der Dimension (nxm) mit einem zufälligem Vektor der Größe (mx1)
// 				 Argument 1: n | Argument 2: m | Argument 3: seed
// 				 Beispielaufruf: ./Matrix_Vector_Mult_Extern_Input_Time 2 3 1337
//============================================================================

#include <iostream>
#include <new>
#include <sys/time.h>
using namespace std;

int main(int argc, char **argv) {

	int i, j, n, m, seed;

	int * v1;
	int * ve;   //Ergebnisvektor
	int ** m1;

	struct timeval start, stop;   // Zeitmessung mit gettimeofday
	long seconds, useconds;
	double duration;

	n = atoi(argv[1]);
	m = atoi(argv[2]);
	seed = atoi(argv[3]);

	srand(seed); // Selber seed -> Selbe Werte durch rand() bei sonst identischer Umgebung. (Mit time(0) als Argument zufällig in abh. der Zeit machen.)

	// Vektor mit m Einträgen
	v1= new (nothrow) int[m];

	// Ergebnisvektor mit n Einträgen
	ve= new (nothrow) int[n];

	// Matrix mit (nxm) Einträgen
	m1 = new int *[n];
	m1[0] = new int [n*m];
	for(i = 1; i<n; i++)
	    m1[i] = m1[0] + i*m;

	if (v1 == nullptr || ve == nullptr || m1 == nullptr)
		cout << "Error: memory could not be allocated";
	else
	{
		// Matrix aufbauen
		for (i=0; i<n; i++)
		{
			for (j=0; j<m; j++)
				m1[i][j] = rand()%100;  // Einträge in m1 zwischen 0 und 99
		}

		// Vektor aufbauen
		for (i=0; i<m; i++)
			v1[i] = rand()%100;  // Einträge in v1 zwischen 0 und 99

		// Zeit stoppen
		gettimeofday(&start, NULL);

		// Multiplikation bzw. Ergebnisvektor aufbauen
		for (i=0; i<n; i++)
		{
			ve[i] = m1[i][0]*v1[0];
			for (j=1; j<m; j++)
				ve[i] += m1[i][j]*v1[j];
		}

		// Zeit stoppen
		gettimeofday(&stop, NULL);

		// Dauer berechnen
		seconds  = stop.tv_sec  - start.tv_sec;
		useconds = stop.tv_usec - start.tv_usec;
		duration = seconds + useconds/1000000.0;  // Dauer in Sekunden

		cout << "Dauer: " << duration << " Sekunden" << endl;

		delete[] v1;
		delete[] ve;
		delete[] m1[0];
		delete[] m1;
	}

	return 0;
}
