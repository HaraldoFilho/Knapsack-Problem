/// MC548 - PROJETO E ANALISE DE ALGORITMOS II - 1s2010
/// Prof. Flavio Keidi Miyazawa
/// ---------------------------------------------------------------
/// PROJETO PRATICO: PROBLEMA DA MOCHILA COM RESTRICOES DE CONFLITO
/// Haraldo Sergio A. Pereira Filho (003059)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "solvers.h"

void print_help() {

	printf("uso: exato -f <entrada> -t <tempomax> -o <saida>\n\n");
	printf("onde: <entrada>  = arquivo de entrada\n");
	printf("      <tempomax> = tempo maximo de execucao em segundos\n");
	printf("      <saida>    = arquivo de saida\n\n");
	printf("exemplo: exato -f entrada.txt -t 60 -o saida.txt\n\n");

}

int main(int argc, char *argv[]) {

	if ((argc!=7)||(strcmp(argv[1], "-f")!=0)||(strcmp(argv[3], "-t")!=0)
			||(strcmp(argv[5], "-o")!=0)) {
		print_help();
		return 0;
	}

	int tmax = atoi(argv[4]);

	printf("Lendo arquivo '%s'...\n", argv[2]);
	data_in_str d = read_input_file(argv[2]);
	printf("\nProblema tem %d objetos e %d compradores\n", d.n, d.m);
	
	printf("\nResolvendo o problema por Programacao Linear Inteira...\n");
	data_out_str r = solve_by_intlinearprog(d, tmax);

	if (r.a == 'E') printf("\nSOLUCAO OTIMA INTEIRA ENCONTRADA!!!");

	if(r.t >= tmax) printf("\nRESOLUCAO INTERROMPIDA!!! TEMPO MAXIMO EXCEDIDO!!!");
	printf("\n\nProblema resolvido em %d segundo", r.t);
	if(r.t != 1) printf("s");

	if (write_output_file(argv[6], r) == 1)
		printf("\n\nArquivo '%s' gravado!\n\n", argv[6]);
	else
		printf("\nERRO ao gravar arquivo '%s'!\n\n", argv[6]);
	
	free_in_struct(d);
	free_out_struct(r);

	return 1;

}
