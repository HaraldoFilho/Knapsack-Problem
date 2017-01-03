/// MC548 - PROJETO E ANALISE DE ALGORITMOS II - 1s2010
/// Prof. Flavio Keidi Miyazawa
/// ---------------------------------------------------------------
/// PROJETO PRATICO: PROBLEMA DA MOCHILA COM RESTRICOES DE CONFLITO
/// Haraldo Sergio A. Pereira Filho (003059)


// Header da biblioteca heuristics.c
// Funcoes heuristicas para resolucao do problema da mochila

#define INFO_ON 	1
#define INFO_OFF 	0
#define NO_LIMIT   -1
#define YES 		1
#define NO 			0

data_out_str greedy_heuristic(data_in_str d, time_t tinit, int tmax, int modo);
/* heuristica gulosa basica: 															*/
/* 1) Caso modo == 1: Ordena conjuntos S(i) por ordem decrescente de p(i)/k(i)			*/
/* 1) Caso modo == 2: Ordena conjuntos S(i) por ordem decrescente de p(i)				*/
/* 2) Solucao <- NULL															    	*/
/* 3) Para i<-0 ate' m-1 e enquanto tempo de execucao < tmax faz 						*/
/* 4) 	Se nenhum objeto de S(i) ja' esta' na solucao									*/
/* 5)		Entao Solucao <- Solucao U S(i)												*/
/* 6) Retorna Solucao																	*/

data_out_str star_greedy_heuristic(data_in_str d, float f, time_t tinit, int tmax, int info, int modo);
/* heuristica gulosa inspirada no conceito de alinhamento estrela de bioinformatica:  	*/
/* 1)  Caso modo == 1: Ordena conjuntos S(i) por ordem decrescente de p(i)/k(i)			*/
/* 1)  Caso modo == 2: Ordena conjuntos S(i) por ordem decrescente de p(i)				*/
/* 2)  Melhor Solucao <- NULL													    	*/
/* 3)  Para l<-0 ate' m-1 e enquanto tempo de execucao < tmax faz 						*/
/* 4) 		Solucao <- NULL														    	*/
/* 5)		Solucao <- Solucao U S(l)													*/
/* 6)		Para i<-0 ate' l-1 e enquanto tempo de execucao < tmax faz					*/
/* 7) 			Se nenhum objeto de S(i) ja' esta' na solucao							*/
/* 8)				Entao Solucao <- Solucao U S(i)										*/
/* 9)		Para i<-l+1 ate' m-1 e enquanto tempo de execucao < tmax faz				*/
/* 10) 			Se nenhum objeto de S(i) ja' esta' na solucao							*/
/* 11)				Entao Solucao <- Solucao U S(i)										*/
/* 12)		Se Solucao > Melhor Solucao													*/
/* 13)			Entao Melhor Solucao = Solucao											*/
/* 14)		Se Solucao/Melhor Solucao < fator (%) * Melhor Solucao 						*/
/* 14)		   ou tempo de execucao >= tmax						 						*/
/* 15)			Entao interrompe procura por Melhor Solucao								*/
/* 16) 	Retorna Melhor Solucao															*/

int time_over(time_t tstart, int tmax);
/* Verifica se tempo limite de execucao da heuristica foi atingido */

