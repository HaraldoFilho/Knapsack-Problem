/// MC548 - PROJETO E ANALISE DE ALGORITMOS II - 1s2010
/// Prof. Flavio Keidi Miyazawa
/// ---------------------------------------------------------------
/// PROJETO PRATICO: PROBLEMA DA MOCHILA COM RESTRICOES DE CONFLITO
/// Haraldo Sergio A. Pereira Filho (003059)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

data_in_str read_input_file(char* file) {

	FILE *in = fopen(file, "r");
	data_in_str d;
	int i, j, k;

	fscanf(in, "%d", &d.n);
	fscanf(in, "%d", &d.m);

	d.p = malloc(d.m*sizeof(d.p));
	d.k = malloc(d.m*sizeof(d.k));
	d.s = malloc(d.n*sizeof(d.s));
	for (i = 0; i < d.n; i++)
		d.s[i] = malloc(d.m*sizeof(d.s[i]));

	for (i = 0; i < d.m; i++)
		for (j = 0; j < d.n; j++)
			d.s[j][i] = 0;

	for (i = 0; i < d.m; i++) {

		fscanf(in, "%f", &d.p[i]);
		fscanf(in, "%d", &d.k[i]);

		for (j = 0; j < d.k[i]; j++) {

			fscanf(in, "%d", &k);
			d.s[k][i] = 1;
		}
	}

	fclose(in);

	return d;

}

int write_output_file(char* file, data_out_str r) {

	int i;

	FILE *out = fopen(file, "w");

	fprintf(out, "%d ", r.q);
	fprintf(out, "%c ", r.a);
	fprintf(out, "%d ", r.t);
	fprintf(out, "%.1f\n", r.s);
	for (i = 0; i < r.m; i++)
		if (r.v[i]==1) fprintf(out, "%d\n", i);

	fclose(out);
	
	return 1;

}

data_in_str copy_in_struct(data_in_str d) {

	return d;
}

data_out_str copy_out_struct(data_out_str r) {

	return r;
}

void free_in_struct(data_in_str d) {
	
	int i;
	
	for (i = 0; i < d.n; i++) free(d.s[i]);
	free(d.s);
	free(d.k);
	free(d.p);
	
}

void free_out_struct(data_out_str r) {
	
	free(r.v);
	
}
