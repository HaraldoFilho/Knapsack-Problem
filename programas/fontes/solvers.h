/// MC548 - PROJETO E ANALISE DE ALGORITMOS II - 1s2010
/// Prof. Flavio Keidi Miyazawa
/// ---------------------------------------------------------------
/// PROJETO PRATICO: PROBLEMA DA MOCHILA COM RESTRICOES DE CONFLITO
/// Haraldo Sergio A. Pereira Filho (003059)


// Header da biblioteca solvers.c       
// Funcoes para resolucao do problema da mochila

data_out_str solve_by_intlinearprog(data_in_str d, int tmax);
/* resolve por programacao linear inteira e retorna uma estrutura contendo os resultados */

data_out_str solve_by_heuristics(data_in_str d, int tmax, int info);
/* resolve por conjunto de heuristicas e retorna uma estrutura contendo os resultados */
