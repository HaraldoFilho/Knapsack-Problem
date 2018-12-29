## Problema da Mochila com Restrições de Conflito

O **problema da mochila** _(em inglês, Knapsack problem)_ é um problema de optimização combinatória. O nome dá-se devido ao modelo de uma situação em que é necessário preencher uma mochila com objetos de diferentes pesos e valores. O objetivo é que se preencha a mochila com o maior valor possível, não ultrapassando o peso máximo.

O problema da mochila é um dos 21 problemas NP-completos de Richard Karp, exposto em 1972. A formulação do problema é extremamente simples, porém sua solução é mais complexa. Este problema é a base do primeiro algoritmo de chave pública (chaves assimétricas).

_Fonte: [Wikipedia](https://pt.wikipedia.org/wiki/Problema_da_mochila)_

### Definição do problema
Um leiloeiro tem n objetos para leiloar, onde os objetos sao dados pelo conjunto N = {0, ..., n − 1}. Há m
pessoas interessadas nos objetos, onde as pessoas são dadas pelo conjunto M = {0, ..., m − 1}. Cada pessoa
está interessada em exatamente um subconjunto de objetos. A pessoa i está interessada no conjunto S i ⊆ N
e dá um lance de valor p i pelo conjunto todo. Neste leilão a pessoa está interessada em apenas este conjunto e
não tem interesse em pegar menos objetos que os de interesse. Naturalmente um objeto não pode ser vendido
para duas pessoas diferentes. Além disso, pode ser que alguns objetos não sejam vendidos para ninguém.
O problema consiste em definir as pessoas que vencem o leilão. Uma pessoa i é um vencedor do leilão, se
ela obtém todos os objetos em S i e com isso paga p i ao leiloeiro por todos os objetos que está levando. Os
perdedores não levam nada nem pagam nada.
O leiloeiro recebe todos os lances e só depois escolhe os vencedores. Como ele quer maximizar o valor da
venda, ele deve escolher os vencedores de maneira que o valor total pago a ele seja máximo.

### Referências
- [Enunciado do projeto](https://github.com/HaraldoFilho/Problema-da-Mochila-com-Restricoes-de-Conflito/blob/master/enunciado.pdf)
- [Relatório do projeto](https://github.com/HaraldoFilho/Problema-da-Mochila-com-Restricoes-de-Conflito/blob/master/relatorio.pdf)
- [Página do GLPK](https://www.gnu.org/software/glpk/)
