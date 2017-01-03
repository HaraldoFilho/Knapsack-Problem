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
#include "heuristics.h"
#include "callback.h"
#include "solvers.h"

data_out_str solve_by_intlinearprog(data_in_str d, int tmax) {

	/******************************************************************************
	 Formulacao do problema em PLI:
	 
	 maximizar: 
	 t = SOMATORIO(0 <= i <= m-1) p(i)*x(i), p(i) real
	 
	 sujeito a: 
	 y(i) = SOMATORIO(0 <= i <= m-1) s(k,i)*x(i), 0 <= k <= n-1, s(k,i) = { 0, 1 }
	 
	 e limites de variaveis: 
	 y(i) <= 1       x(i) = { 0, 1 } 

	******************************************************************************/

	int i, j, k, s;
	data_out_str r;
	cb_info_str cb_info;
	
	printf("Iniciando o resolvedor GLPK...\n");
	
	glp_prob *mip;
	glp_smcp lp_parm;
	glp_iocp mip_parm;
	glp_long lp_start, lp_end, mip_start, mip_end;
	long lp_time, mip_time;

	int* ia = malloc((1+d.n*d.m)*sizeof(int)); 			// numero das linhas na matriz do sistema PL
	int* ja = malloc((1+d.n*d.m)*sizeof(int)); 			// numero das colunas na matriz do sistema PL
	double* ar = malloc((1+d.n*d.m)*sizeof(double)); 	// valores na matriz do sistema PL

	mip = glp_create_prob();							// cria problema PLI
	glp_set_obj_dir(mip, GLP_MAX);						// problema e' de maximizacao

	glp_add_rows(mip, d.n);								// adiciona n linhas ao problema
	for (i = 1; i<=d.n; i++)
		glp_set_row_bnds(mip, i, GLP_UP, 0.0, 1.0);		// define y(i) <= 1

	glp_add_cols(mip, d.m);								// adiciona m colunas ao problema
	for (j = 1; j<=d.m; j++) {
		glp_set_col_kind(mip, j, GLP_BV);				// define x(i) binario
		glp_set_obj_coef(mip, j, d.p[j-1]);				// define valores de p(i)
	}

	k = 0;												// 
	for (i = 1; i <= d.n; i++)							// 
		for(j = 1; j <= d.m; j++) {						// 
			k++;										// 
			ia[k] = i;									// 
			ja[k] = j;									// 
			ar[k] = d.s[i-1][j-1];						// 
		}												// 
	glp_load_matrix(mip, d.n*d.m, ia, ja, ar);			// } carrega valores na matriz do glpk
	
	glp_init_smcp(&lp_parm);							// inicializa parametros com valores padrao
	lp_parm.msg_lev = GLP_MSG_ON;						// exibe apenas mensagens sobre a solucao
	lp_parm.tm_lim = tmax*1000;							// tempo maximo de execucao em milisegundos
	lp_parm.meth = GLP_DUALP;							// seleciona metodo dual/primal simplex
	printf("Executing GLPK simplex algorithm...\n");
	lp_start = glp_time();								// inicia contagem do tempo de execucao
	glp_simplex(mip, &lp_parm);							// executa o algoritmo simplex
	lp_end = glp_time();								// termina contagem do tempo de execucao
	lp_time = glp_difftime(lp_end, lp_start);			// calcula tempo de execucao do simplex
	if(lp_time > tmax) lp_time = tmax;					
	if(glp_get_status(mip) == GLP_OPT) printf("Optimal solution found: %.2f\n", glp_get_obj_val(mip));

	glp_init_iocp(&mip_parm);							// inicializa parametros com valores padrao
	mip_parm.msg_lev = GLP_MSG_ON;						// exibe apenas mensagens sobre a solucao
	mip_parm.tm_lim = (tmax-lp_time)*1000;				// tempo maximo de execucao em milisegundos
	mip_parm.br_tech = GLP_BR_MFV;						// tecnica de branching: variavel mais fracionaria
	mip_parm.pp_tech = GLP_PP_ROOT;						// tecnica de pre-processamento: so' no nivel da raiz
	mip_parm.cb_func = usr_callback;					// rotina callback para o branch&cut do MIP
	cb_info.ctrl = 0;									// variavel de controle para execucao da heuristica no callback
	cb_info.tmax = (int)(tmax-lp_time)/4;				// tempo maximo para a execucao das heuristicas no callback
	cb_info.d = copy_in_struct(d);						// dados de entrada para a execucao das heuristicas no callback
	mip_parm.cb_info = &cb_info;						// passa estrutura com informacoes para o callback
	printf("Executing GLPK integer optimizer...\n");
	mip_start = glp_time();								// inicia contagem do tempo de execucao
	glp_intopt(mip, &mip_parm);							// executa o algoritmo MIP
	mip_end = glp_time();								// termina contagem do tempo de execucao
	mip_time = glp_difftime(mip_end, mip_start);		// calcula tempo de execucao do MIP

	r.s = glp_mip_obj_val(mip);							// obtem resultado
	s = glp_mip_status(mip);							// obtem tipo da solucao

	if (s == GLP_OPT) {									// solucao otima?
		r.a = 'E';
		printf("Optimal solution found: %.1f\n", r.s);
	}
	else {
		r.a = 'e';
		if (s == GLP_FEAS) printf("Feasible solution found: %.1f\n", r.s);
	}
	
	r.v = malloc(d.m*sizeof(r.v));						// inicializa vetor de vencedores
	k = 0;												// inicializa com 0 vencedores

	if ((s == GLP_OPT)||(s == GLP_FEAS)) 				// se solucao e' otima ou viavel
		for (i = 0; i < d.m; i++) {						//
			r.v[i] = glp_mip_col_val(mip, i+1);			// } obtem valores de x(i) para resultado
			if (r.v[i] == 1) k++; 						// } e conta a quantidade de "vencedores"
		}
	else
		for (i = 0; i < d.m; i++)						//
			r.v[i] = 0;									// } nao ha vencedores
	
	r.q = k;											// numero de vencedores
	
	r.m = d.m;											// numero de participantes do leilao

	r.t = (int) lp_time + mip_time;						// calcula tempo de execucao total
	
	glp_delete_prob(mip);								// libera toda a memoria alocada

	return r;
}

data_out_str solve_by_heuristics(data_in_str d, int tmax, int info) {
	
	int t;
	int e1 = 1;
	int e2 = 2;
	
	data_out_str r1;

	if (info == INFO_ON) printf("\nExecutando heuristica gulosa 1...");
	r1 = greedy_heuristic(d, time(NULL), tmax, 1);
	if (info == INFO_ON) printf("\nSolucao encontrada = %.1f em %d seg\n", r1.s, r1.t);

	data_out_str br;
	br = copy_out_struct(r1);

	if((tmax == NO_LIMIT)||(br.t < tmax)) {
		
		data_out_str r2;
		
		if (info == INFO_ON) printf("\nExecutando heuristica gulosa 2...");
		r2 = greedy_heuristic(d, time(NULL), tmax-br.t, 2);
		if (info == INFO_ON) printf("\nSolucao encontrada = %.1f em %d seg\n", r2.s, r2.t);

		if(r2.s > br.s) {
			t = br.t;
			free_out_struct(br);
			br = copy_out_struct(r2);
			br.t += t;
			e1 = 2;
			e2 = 1;
		}
		else {
			br.t += r2.t;
			free_out_struct(r2);
		}
	}
	
	if((tmax == NO_LIMIT)||(br.t < tmax)) {

		data_out_str r3;
		
		if (info == INFO_ON) printf("\nExecutando heuristica gulosa estrela %d...", e1);
		r3 = star_greedy_heuristic(d, 0.8, time(NULL), tmax-br.t, info, e1);
		if (info == INFO_ON) printf("\nMelhor solucao encontrada = %.1f em %d seg\n", r3.s, r3.t);

		if(r3.s > br.s) {
			t = br.t;
			free_out_struct(br);
			br = copy_out_struct(r3);
			br.t += t;
		}
		else {
			br.t += r3.t;
			free_out_struct(r3);
		}
	}
	
	if((tmax == NO_LIMIT)||(br.t < tmax)) {

		data_out_str r4;
		
		if (info == INFO_ON) printf("\nExecutando heuristica gulosa estrela %d...", e2);
		r4 = star_greedy_heuristic(d, 0.8, time(NULL), tmax-br.t, info, e2);
		if (info == INFO_ON) printf("\nMelhor solucao encontrada = %.1f em %d seg\n", r4.s, r4.t);

		if(r4.s > br.s) {
			t = br.t;
			free_out_struct(br);
			br = copy_out_struct(r4);
			br.t += t;
		}
		else {
			br.t += r4.t;
			free_out_struct(r4);
		}
	}
	
	br.m = d.m;
	br.a = 'H';

	return br;
	
	
}
