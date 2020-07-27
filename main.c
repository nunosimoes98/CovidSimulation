#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "defines.h"
#include "data.h"
#include "functions.h"

int main(int argc, char** argv) {

	local *salas = NULL;
	pessoa *pessoas=NULL;
	espaco *eLista=NULL;
	espaco* aux = NULL;
	populacao* auxP = NULL;
	Ids *id=NULL;
	DadosLocal *dadosL=NULL;
	pessoa pessoaAdd;
	int nPessoas = 0;
	int nSalas=0;
	int opcao;

	initRandom(); // util.c, inicializar gerador de randoms

	menuInicial();

	salas=obtemFichSalas(salas,&nSalas);      
	validacoesSalas(salas,nSalas);
	pessoas = obtemFichPessoas(pessoas,&nPessoas);
	validacaoPessoasID(pessoas, nPessoas);
	eLista=criacaoLocalPessoa(eLista,salas, nSalas, pessoas, nPessoas);

	do {
		
		printf("\n\n\tMENU SIMULACAO:\n\t\t"
			"1 - Avancar 1 dia\n\t\t"
			"2 - Estatisticas\n\t\t"
			"3 - Adicionar Doente\n\t\t"
			"4 - Transferir Pessoas\n\t\t"
			"5 - Terminar simulacao\n\t\t"
		);

		printf("\n\tIntroduza uma opcao[0-1]:");
		scanf(" %d", &opcao);

		limpaStdin();

		switch (opcao)
		{
		
		case 1:
			eLista=avancaUmDia(eLista,pessoas,nPessoas,salas,nSalas);
			break;
		case 2:
			mostraEstatisticas(eLista);
			break;
			
		case 3:
			ObtemDadosDoente(&pessoaAdd, pessoas, nPessoas, salas, nSalas,eLista);
			dadosL=obtemDadosLocal(eLista, dadosL,nSalas);
			pessoas=addPessoaAoArrayPessoas(&pessoaAdd,pessoas,&nPessoas);
			libertaLista(eLista);
                        eLista = NULL;
			eLista = eListarecontroiLista(eLista, id, dadosL, pessoas, nPessoas,salas, nSalas);
			break;

		case 4:
			eLista = tranferirPessoas(eLista, pessoas, nPessoas, salas, nSalas);
			break;

		case 5:
			terminarSimulacao(eLista);
			break;
                    case 6:
                        mostraPercentagem(eLista);

		default:
			printf("\n\n\tO numero que introduziu e invalido!!\n");
			break;
		}

	} while (opcao != 5);

	escreveFichPessoas(pessoas, nPessoas);
	free(salas);
	free(pessoas);
	libertaLista(eLista);

	return (EXIT_SUCCESS);
}