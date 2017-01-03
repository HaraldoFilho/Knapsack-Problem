/// MC548 - PROJETO E ANALISE DE ALGORITMOS II - 1s2010
/// Prof. Flavio Keidi Miyazawa
/// ---------------------------------------------------------------
/// PROJETO PRATICO: PROBLEMA DA MOCHILA COM RESTRICOES DE CONFLITO
/// Haraldo Sergio A. Pereira Filho (003059)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h>
#include <time.h>
#include "data.h"
#include "solvers.h"
#include "heuristics.h"
#include "callback.h"

void usr_callback(glp_tree *tree, void *info) {

	int i, j;
	data_out_str r;
	cb_info_str *cb_info;
	glp_prob *mip;

	switch (glp_ios_reason(tree)) {	

		case GLP_IHEUR:															// se rotina foi chamada para execucao de heuristicas
			
			cb_info = info;														// recupera informacao de controle da execucao da heuristica

			if (cb_info->ctrl == 1) return;										// se heuristica ja foi executada anteriormente retorna

			printf("Executing heuristics to find an integer feasible solution...\n");
			r = solve_by_heuristics(cb_info->d, cb_info->tmax, INFO_OFF);		// executa conjunto de heuristicas

			double* sol = malloc((cb_info->d.m+1)*sizeof(double));
			for(i = 0; i < cb_info->d.m; i++) sol[i+1] = (double) r.v[i];		// copia vencedores para vetor solucao

			glp_ios_heur_sol(tree, sol);										// realimenta glpk com a solucao inteira
			
			free_out_struct(r);
			free(sol);
			
			cb_info->ctrl = 1;													// marca heuristica como ja executada
		
			break;

		default:																// ignora chamada por outras razoes
			break;
	}
	
	return;
}
