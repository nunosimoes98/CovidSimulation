#include "functions.h"


void mostraPercentagem(espaco *novoEspaco){
    
    espaco *aux, *AuxP = NULL;
    int contaInfetados = 0;
    float percentagem;
    
    aux = novoEspaco;
    
    
    while(aux != NULL){
        
        AuxP = aux->listaPessoas;
        
        while(AuxP != NULL){
            if (AuxP->pessoa->estado == 'D') {
                contaInfetados++;
            }
           
        }
        percentagem = (float)(contaInfetados / aux->nPessoas) * 100;
        
        printf("A sala tem %f ")
        aux = aux->prox;
    }
    
    
}
void preencheEspaco(local *novoLocal,espaco *novoEspaco) {
	novoEspaco->local = novoLocal;
	novoEspaco->nPessoas = 0;
	novoEspaco->pessoasImunes = 0;
	novoEspaco->pessoasDoentes = 0;
	novoEspaco->pessoasSaudaveis = 0;
	novoEspaco->nPessoasAdd = 0;
	novoEspaco->nPessoasTranf=0;
	novoEspaco->nDias = 1;
	novoEspaco->prox = NULL;
	novoEspaco->listaPessoas = NULL;
}

espaco* insereEspacoFinalLista(espaco *eLista,espaco *novoEspaco) {
	espaco *aux=NULL;

	if (eLista == NULL) {
		eLista = novoEspaco;
	}
	else {
		aux = eLista;

		while (aux->prox != NULL){
			aux = aux->prox;
		}
	
		aux->prox = novoEspaco;
	}

	return eLista;
}

espaco* criaEspaco(espaco *eLista, local *salas, int nSalas) {

	espaco *novoEspaco=NULL;
	local  *novoLocal=NULL;
		
	for (int i = 0; i < nSalas; i++) {
	
		novoLocal = &(salas[i]);
	
		novoEspaco = malloc(sizeof(espaco));

		if (novoEspaco == NULL) {
			printf("[Erro] alocar memoria para um novo espaco!!\n");
			exit(EXIT_FAILURE);

		}

	    preencheEspaco(novoLocal, novoEspaco);

            eLista=insereEspacoFinalLista(eLista, novoEspaco);
	 }

	return eLista;
}

void geraNumeroAleatorioSalas(int *n,int nSalas) {
	*n=intUniformRnd(0, nSalas - 1);
}

void preenchePopulacao(espaco *aux, populacao *novaPopulacao, pessoa *pessoa) {

	novaPopulacao->pessoa = pessoa;
	novaPopulacao->pessoa->localOndeSeEncontra = aux->local;
	novaPopulacao->prox = NULL;
	aux->nPessoas+=  1;
	
	if (novaPopulacao->pessoa->estado == 'I') {
		aux->pessoasImunes += 1;
	}
	else if (novaPopulacao->pessoa->estado == 'D') {
		aux->pessoasDoentes += 1;
	}
	else {
		aux->pessoasSaudaveis += 1;
	}
}

void inserePopulacaoFinalLista(espaco *aux, populacao *novaPopulacao) {

	populacao *auxP= NULL;

	if (aux->listaPessoas == NULL) {
		aux->listaPessoas = novaPopulacao;
	}
	else {
		auxP = aux->listaPessoas;

		while (auxP->prox != NULL) {
			auxP = auxP->prox;
		}
		auxP->prox = novaPopulacao;
	}
}

espaco* criaPopulacao(espaco *eLista, local *salas, int nSalas, pessoa *pessoas, int nPessoas) {
	int n;
	espaco* aux=NULL;
	populacao *novaPopulacao=NULL;
	populacao* auxP = NULL;

	for (int i = 0; i < nPessoas; i++) {

			geraNumeroAleatorioSalas(&n, nSalas);

			aux = NULL;
			aux = eLista;

			while (aux->local->id != salas[n].id) {
				aux = aux->prox;

			}

			if (aux->local->capacidade > aux->nPessoas) {

				novaPopulacao = malloc(sizeof(populacao));

				if (novaPopulacao == NULL) {
					printf("Erro alocar memoria para uma populacao!!\n");
					exit(EXIT_FAILURE);
				}

				preenchePopulacao(aux, novaPopulacao, &(pessoas[i]));

				inserePopulacaoFinalLista(aux,novaPopulacao);
			}
	}
	return eLista;
}

espaco* criacaoLocalPessoa(espaco *eLista,local *salas, int nSalas, pessoa *pessoas, int nPessoas) {

	eLista=criaEspaco(eLista,salas,nSalas);
	
	eLista = criaPopulacao(eLista, salas, nSalas, pessoas, nPessoas);

	return eLista;
}

int obtemRandomNoArray(int* pessoasSelecionadas, int nrPessoas, int nPessoasAux) { //devolve numero aleatorio po array de inteiros

	int verificaRandom;
	int valorRandom;
	int i;

	while (1) {

		valorRandom = intUniformRnd(0, (nPessoasAux - 1));

		verificaRandom = 0;

		for (i = 0; i < nrPessoas; i++) {
			if (pessoasSelecionadas[i] == valorRandom) {
				verificaRandom = 1;
				break;
			}
		}

		if (verificaRandom == 0) {
			return valorRandom;
		}
	}
}

espaco* doenteInfetaPessoas(espaco* eLista,pessoa *pessoas, int nPessoas) {
	espaco* aux = NULL;
	populacao* auxP;
	populacao* aux1P;
	int nrPessoasAinfetar;
	int nPessoasAux,valorRandom;
	int *pessoasSelecionadas = NULL;
	pessoa *pessoasNoMesmoLocal;
	pessoa *aux1=NULL;
	int flag;
	int j;
	int res;

	aux = eLista;

	while (aux != NULL){

		auxP = NULL;
		auxP = aux->listaPessoas;
		
		while (auxP != NULL) {
			
			if (auxP->pessoa->estado == 'D') { //percorre ate encontrar uma pessoa doente
				nrPessoasAinfetar =(int)TAXA_DISSEMINACAO * aux->nPessoas; //1;
				flag = NAO_CRIOU_VETOR;
				aux1P = NULL;
				aux1P = aux->listaPessoas;
				if (nrPessoasAinfetar >0 && (aux->nPessoas-nrPessoasAinfetar)>=1) {   // pessoas que vai infetar naquele local tem que existir mais que uma pessoa, pode estar uma so uma doente na lista
					j = 0;
					pessoasNoMesmoLocal = NULL;
			
					aux1 = NULL;
					while (aux1P !=NULL ) {    //percorrer novamente o local para encontrar as pessoas que nao estao doentes
						
						if (strcmp(aux1P->pessoa->id,auxP->pessoa->id)!=0 ) { //para nao adicionar a pessoa que propagou a virus
							for (int i = 0; i < nPessoas; i++) {  //percorrer o vetor de pessoas para verificar as que estao no mesmo local
								if (aux->local->id == pessoas[i].localOndeSeEncontra->id && strcmp(aux1P->pessoa->id,pessoas[i].id)==0) {   //pessoas que estao naquele local e 
									flag = CRIOU_VETOR;
								
									aux1 = realloc(pessoasNoMesmoLocal, sizeof(pessoa) * (j + 1));                       
									if (aux1 == NULL) {
										free(pessoasNoMesmoLocal);
										printf("[Erro]sem memoria para pessoas nos locais para infetar!!\n");
										exit(EXIT_FAILURE);
									}

									pessoasNoMesmoLocal = aux1;

									pessoasNoMesmoLocal[j] = pessoas[i];
									j++;
								}
							}
						}
						aux1P = aux1P->prox;
					}

					if (flag==CRIOU_VETOR) {
						nPessoasAux = j;

						pessoasSelecionadas = malloc(sizeof(int) * nrPessoasAinfetar);

						if (pessoasSelecionadas == NULL) {
							free(pessoasNoMesmoLocal);
							printf("[Erro]sem memoria para pessoas selecionadas para infetar!!\n");
							exit(EXIT_FAILURE);
						}

						for (int k = 0; k < nrPessoasAinfetar; k++) {                //obter arrays de inteiros 

							valorRandom = obtemRandomNoArray(pessoasSelecionadas, nrPessoasAinfetar, nPessoasAux);
							pessoasSelecionadas[k] = valorRandom;
						}

						for (int z = 0; z < nrPessoasAinfetar; z++) {
							for (int y = 0; y < nPessoas; y++) {

								if (strcmp(pessoasNoMesmoLocal[pessoasSelecionadas[z]].id, pessoas[y].id) == 0) {       
									                                                                                  //atualizar array original de pessoas, pois na lista ligada esta apontar para este array
									if (pessoas[y].estado == 'S') {

										pessoas[y].estado = 'D';
										pessoas[y].infetadaNoDiaAtual = SIM; //nao faz sentido recuperar no dia atual 
										aux->pessoasDoentes+=1;
										aux->pessoasSaudaveis -= 1;;
										res = pessoas[y].idade / 10;
										pessoas[y].nrDiasInfetado = 5 + res;
									}
								}
							}
						}
						free(pessoasNoMesmoLocal);
						free(pessoasSelecionadas);
					}
				}

			}
			auxP = auxP->prox;
		}
		aux = aux->prox;
	}

	return eLista;
}

espaco* atualizaDadosNaLista(espaco* eLista, pessoa *pessoa) {
	espaco* aux = NULL;
	populacao* aux1 = NULL;

	aux = eLista;

		while (aux != NULL) {

			aux1 = NULL;
			aux1=aux->listaPessoas;

			while (aux1 != NULL) {
				if (strcmp(aux1->pessoa->id, pessoa->id) == 0) {
					aux->pessoasDoentes -= 1;
					aux->pessoasSaudaveis += 1;
			    }
				aux1 = aux1->prox;
			}
			aux = aux->prox;
		}
		return eLista;
}

espaco* AtualizaInfecao(espaco* eLista, pessoa* pessoas, int nPessoas) {
	

	for (int i = 0; i < nPessoas; i++) {
		if (pessoas[i].estado == 'D' && pessoas[i].infetadaNoDiaAtual == NAO && pessoas[i].localOndeSeEncontra != NULL){

			pessoas[i].nrDiasInfetado -= 1;

			if (pessoas[i].nrDiasInfetado==0) {
				pessoas[i].Curada = SIM;
				pessoas[i].estado = 'S';
				pessoas[i].curadaNoDiaAtual = SIM;
				eLista=atualizaDadosNaLista(eLista, &(pessoas[i]));
			}
		}	
	}
	return eLista;
}

espaco* probabilidadeDeRecuperacao(espaco *eLista, pessoa *pessoas, int nPessoas) {
	int res;
	float valor;


	for (int i = 0; i < nPessoas;i++) {
	
		if (pessoas[i].estado == 'D' && pessoas[i].infetadaNoDiaAtual == NAO && pessoas[i].localOndeSeEncontra != NULL) { //!=NULL quer dizer que esta na simulacao
		   
			valor = (float)1/ pessoas[i].idade;
			
			res = probEvento(valor);
		   
			if (res == RECUPERADA) {
				pessoas[i].Curada = SIM;
				pessoas[i].estado = 'S';
				pessoas[i].nrDiasInfetado = 0;
				pessoas[i].curadaNoDiaAtual = SIM;
				atualizaDadosNaLista(eLista,&(pessoas[i]));
			}
		
		} 
	
	}

	return eLista;
}

espaco* atualizaImunidadeNaLista(espaco *eLista, pessoa *pessoa) {
	espaco* aux = NULL;
	populacao* aux1 = NULL;

	aux = eLista;

	while (aux != NULL) {

		aux1 = NULL;
		aux1 = aux->listaPessoas;

		while (aux1 != NULL) {

			if (strcmp(aux1->pessoa->id, pessoa->id) == 0) {


				aux->pessoasSaudaveis -= 1;
				if (aux->pessoasSaudaveis <= 0){
					aux->pessoasSaudaveis = 0;
				}
				
				aux->pessoasImunes += 1;

			}
			aux1 = aux1->prox;

		}

		aux = aux->prox;

	}

	return eLista;

}

void atualizacaoDoDia(espaco* eLista) {
	espaco *aux=NULL;
	
	aux = eLista;

	while (aux != NULL) {
	
		aux->nDias++;

		aux = aux->prox;
	}


}

void atualizaInformacao(pessoa *pessoas,int nPessoas){
	for (int i = 0; i < nPessoas; i++) {


		pessoas[i].curadaNoDiaAtual = NAO;   // e para testar a taxa de imunidade , caso recupere no dia atual, nao faz sentido ficar imune
		pessoas[i].infetadaNoDiaAtual = NAO;  //para saber quando uma pessoa foi infetada neste dia para nao poder recuperar no mesmo dia
	}

}

espaco* avancaUmDia(espaco *eLista,pessoa *pessoas, int nPessoas,local *salas,int nSalas) {

	atualizaInformacao(pessoas, nPessoas);

	eLista=doenteInfetaPessoas(eLista,pessoas,nPessoas);

	eLista=probabilidadeDeRecuperacao(eLista,pessoas, nPessoas);

	eLista=AtualizaInfecao(eLista, pessoas, nPessoas);

	eLista=verificarSeFicaImune(eLista,pessoas,nPessoas);

	atualizacaoDoDia(eLista);

	return eLista;
}

void libertaLista(espaco *eLista) {

	espaco *aux;
	populacao *aux1;


	while (eLista != NULL) {

		aux = eLista;
		eLista = eLista->prox;

		aux1 = aux->listaPessoas;

		while (aux->listaPessoas != NULL) {
			aux1 = aux->listaPessoas;
			aux->listaPessoas= aux->listaPessoas->prox;
			free(aux1);

		}

		free(aux);
	}
}

void  ObtemDadosDoente(pessoa *pessoaAdd, pessoa *pessoas, int nPessoas, local *salas, int nSalas,espaco *eLista) {
	int idLocal;
	char idPessoa[TAM_TEXTO];
	int idade;
	int nrDiasInf;
	espaco *aux=NULL;
	
	

	pedirEverificarIdLocal(salas, nSalas, &idLocal,eLista);
     
	pedirEverificarIdPessoa(idPessoa,pessoas,nPessoas);

	pedirEverificarIdade(&idade);

	pedirEverificarNumeroDiaDeInfecao(&nrDiasInf,idade);

	pessoaAdd->Curada = NAO;
	pessoaAdd->curadaNoDiaAtual = NAO;
	pessoaAdd->estado = 'D';
	strcpy(pessoaAdd->id, idPessoa);
	pessoaAdd->idade = idade;
	pessoaAdd->infetadaNoDiaAtual = NAO;
	pessoaAdd->nrDiasInfetado = nrDiasInf;
	pessoaAdd->pessoaA = SIM;
	pessoaAdd->ficouImune = NAO;
	pessoaAdd->pessoaTranf = NAO;

	for (int i = 0; nSalas; i++) {
	
		if (idLocal == salas[i].id) {
			pessoaAdd->localOndeSeEncontra = &(salas[i]);
			break;
		}
	}

	aux = eLista;

	while (aux->local->id != pessoaAdd->localOndeSeEncontra->id) {
		aux = aux->prox;
	}

	aux->nPessoas += 1;
	aux->nPessoasAdd += 1;
	aux->pessoasDoentes += 1;

}

pessoa* addPessoaAoArrayPessoas(pessoa* pessoaAdd, pessoa* pessoas, int* nPessoas) {
	pessoa* aux = NULL;


	aux = malloc(sizeof(pessoa) * (*nPessoas + 1));

	if (aux == NULL) {
		printf("[Erro]sem memoria para a pessoa adicionada!!\n");
		exit(EXIT_FAILURE);
	}


	for (int i = 0; i < *nPessoas; i++) {
		aux[i].Curada = pessoas[i].Curada;
		aux[i].estado = pessoas[i].estado;
		strcpy(aux[i].id, pessoas[i].id);
		aux[i].idade = pessoas[i].idade;
		aux[i].localOndeSeEncontra = pessoas[i].localOndeSeEncontra;
		aux[i].nrDiasInfetado = pessoas[i].nrDiasInfetado;
		aux[i].ficouImune = pessoas[i].ficouImune;
		aux[i].pessoaA = pessoas[i].pessoaA;
		aux[i].pessoaTranf = pessoas[i].pessoaTranf;
	
	}

	  free(pessoas);
	  pessoas = NULL;

	  aux[*nPessoas].Curada = pessoaAdd->Curada;
	  aux[*nPessoas].estado = pessoaAdd->estado;
	  strcpy(aux[*nPessoas].id, pessoaAdd->id);
	  aux[*nPessoas].idade = pessoaAdd->idade;
	  aux[*nPessoas].localOndeSeEncontra = pessoaAdd->localOndeSeEncontra;
	  aux[*nPessoas].nrDiasInfetado = pessoaAdd->nrDiasInfetado;
	  aux[*nPessoas].curadaNoDiaAtual = pessoaAdd->curadaNoDiaAtual;
	  aux[*nPessoas].infetadaNoDiaAtual = pessoaAdd->infetadaNoDiaAtual;
	  aux[*nPessoas].ficouImune= pessoaAdd->ficouImune;
	  aux[*nPessoas].pessoaTranf = pessoaAdd->pessoaTranf;
	  aux[*nPessoas].pessoaA = pessoaAdd->pessoaA;

	  pessoas = aux;

	
	  *nPessoas+=1;
	   

	return pessoas;
}

DadosLocal* obtemDadosLocal(espaco* eLista, DadosLocal* dadosL, int nSalas) {
	espaco* aux = NULL;
	DadosLocal* auxL=NULL;

	
	auxL = malloc(sizeof(DadosLocal) * nSalas);

	if (auxL == NULL) {
		printf("[Erro]sem memoria para os dados do local!!\n");
		exit(EXIT_FAILURE);
	}

	dadosL = auxL;
	aux = eLista;

	for (int i = 0; i < nSalas; i++) {
		
		dadosL[i].idLocal = aux->local->id;
		dadosL[i].nD = aux->nDias;
		dadosL[i].nPessoasA = aux->nPessoasAdd;
		dadosL[i].nPs = aux->nPessoas;
		dadosL[i].pessoasD = aux->pessoasDoentes;
		dadosL[i].pessoasI = aux->pessoasImunes;
		dadosL[i].pessoasS = aux->pessoasSaudaveis;
		dadosL[i].nPtranf = aux->nPessoasTranf;
		aux = aux->prox;
	}
	return dadosL;
}

espaco* eListarecontroiLista(espaco *eLista,Ids *id,DadosLocal *dadosL,pessoa *pessoas,int nPessoas,local *salas,int nSalas) {
	espaco *novoEspaco=NULL;
	populacao *novaPopulacao = NULL;
	populacao* auxP = NULL;
	

	for (int i = 0; i < nSalas;i++) {
	

		novoEspaco = malloc(sizeof(espaco));

		if (novoEspaco == NULL) {
			printf("[Erro] alocar memoria para um novo espaco!!\n");
			exit(EXIT_FAILURE);

		}

		novoEspaco->local = &(salas[i]);
		

		for (int j = 0; j < nSalas; j++) {
			if (novoEspaco->local->id == dadosL[i].idLocal) {
				novoEspaco->nDias = dadosL[i].nD;
				novoEspaco->nPessoas = dadosL[i].nPs;
				novoEspaco->nPessoasAdd = dadosL[i].nPessoasA;
				novoEspaco->pessoasDoentes = dadosL[i].pessoasD;
				novoEspaco->pessoasImunes = dadosL[i].pessoasI;
				novoEspaco->pessoasSaudaveis = dadosL[i].pessoasS;
				novoEspaco->nPessoasTranf = dadosL[i].nPtranf;
				novoEspaco->prox = NULL;
				novoEspaco->listaPessoas = NULL;
			
			}
		
		}

		for (int k = 0; k < nPessoas; k++) {
		
			if (novoEspaco->local->id == pessoas[k].localOndeSeEncontra->id) {
				novaPopulacao = malloc(sizeof(populacao));

				if (novaPopulacao == NULL) {
					printf("Erro alocar memoria para uma populacao!!\n");
					exit(EXIT_FAILURE);

				}

				novaPopulacao->pessoa = &(pessoas[k]);
				novaPopulacao->prox = NULL;


				if (novoEspaco->listaPessoas == NULL) {
					novoEspaco->listaPessoas = novaPopulacao;
				}
				else {
					auxP = novoEspaco->listaPessoas;

					while (auxP->prox != NULL) {
						auxP = auxP->prox;
					}

					auxP->prox = novaPopulacao;
				}


			}

		}

		eLista = insereEspacoFinalLista(eLista, novoEspaco);
	
	
	}


	return eLista;
}

espaco* fazMovimentacao(espaco* eLista, int idOrigem, int idDestino, int nPessoasMover, pessoa* pessoas, int nPessoas,local *salas, int nSalas) {
	espaco* aux = NULL;
	populacao* auxP = NULL,*anteriorP,*novaP;
	pessoa *pessoasAmover = NULL;
	pessoa *aux1 = NULL;
	int j, nPessoasAux,*pessoasSelecionadas,valorRandom;

	aux = eLista;

	while (aux->local->id != idOrigem){
		aux = aux->prox;
	}

	auxP = aux->listaPessoas;
	j = 0;
	while (auxP != NULL) {    

			for (int i = 0; i < nPessoas; i++) {  
				if (aux->local->id == pessoas[i].localOndeSeEncontra->id && strcmp(auxP->pessoa->id, pessoas[i].id) == 0) {  

					aux1 = realloc(pessoasAmover, sizeof(pessoa) * (j + 1));
					if (aux1 == NULL) {
						free(pessoasAmover);
						printf("[Erro]sem memoria para pessoas nos locais!!\n");
						exit(EXIT_FAILURE);
					}

					pessoasAmover = aux1;

					pessoasAmover[j] = pessoas[i];
					j++;
				}
			}

		auxP = auxP->prox;

	}

	nPessoasAux = j;

	pessoasSelecionadas = malloc(sizeof(int) * nPessoasMover);

	if (pessoasSelecionadas == NULL) {
		free(pessoasAmover);
		printf("[Erro]sem memoria para pessoas selecionadas a tranferir!!\n");
		exit(EXIT_FAILURE);

	}

	for (int k = 0; k < nPessoasMover; k++) {               

		valorRandom = obtemRandomNoArray(pessoasSelecionadas, nPessoasMover, nPessoasAux);
		pessoasSelecionadas[k] = valorRandom;

	}
	
		for (int z = 0; z< nPessoasMover; z++) {
			anteriorP = NULL;
			auxP = NULL;
			auxP = aux->listaPessoas;

			while (auxP != NULL && strcmp(pessoasAmover[pessoasSelecionadas[z]].id, auxP->pessoa->id) != 0){
				anteriorP = auxP;
				auxP = auxP->prox;
			}

			if (auxP != NULL) {

				for (int w = 0; w < nPessoas; w++) {
					if (strcmp(pessoas[w].id, auxP->pessoa->id) == 0) {

						if (pessoas[w].estado == 'D') {
							aux->pessoasDoentes -= 1;

						}
						else if (pessoas[w].estado == 'S') {
							aux->pessoasSaudaveis -= 1;
						}
						else {
							aux->pessoasImunes -= 1;

						}

						if (pessoas[w].pessoaA == SIM) {
							aux->nPessoasAdd -= 1;
						}
						
						aux->nPessoas -= 1;


						for (int t = 0; t < nSalas; t++) {
							if (salas[t].id == idDestino) {
								pessoas[w].localOndeSeEncontra = &(salas[t]);
							
							}
					
						}

					}

				}
				if (anteriorP == NULL) {
					aux->listaPessoas = auxP->prox;
				}
				else {
					anteriorP->prox = auxP->prox;
				}

				free(auxP);

			}
				
		}
		
		aux = NULL;
		aux = eLista;

		while (aux->local->id != idDestino) {
			aux = aux->prox;
		}

		for (int x = 0; x < nPessoasMover; x++) {
			
			novaP = NULL;
			novaP = malloc(sizeof(populacao));

			if (novaP == NULL) {
				printf("Erro alocar memoria para uma populacao para tranferir pessoas!!\n");
				exit(EXIT_FAILURE);

			}

			for (int q = 0; q < nPessoas; q++) {
				if ((aux->local->id == pessoas[q].localOndeSeEncontra->id) && (strcmp(pessoasAmover[pessoasSelecionadas[x]].id, pessoas[q].id) == 0)){
					novaP->pessoa = &(pessoas[q]);

				}

			}

			novaP->prox = NULL;

			inserePopulacaoFinalLista(aux, novaP);


			if (novaP->pessoa->estado == 'D') {
				aux->pessoasDoentes += 1;

			}
			else if (novaP->pessoa->estado == 'S') {
				aux->pessoasSaudaveis += 1;
			}
			else {
				aux->pessoasImunes += 1;

			}

			if (novaP->pessoa->pessoaA == SIM) {
				aux->nPessoasAdd += 1;
			}

			aux->nPessoas += 1;
			aux->nPessoasTranf += 1;

			novaP->pessoa->pessoaTranf = SIM;

		}


		free(pessoasAmover);
		free(pessoasSelecionadas);

	return eLista;
}

espaco* tranferirPessoas(espaco* eLista, pessoa* pessoas, int nPessoas, local* salas, int nSalas) {
	int idOrigem,idDestino,nPessoasMover;
	

	pedirEverificarIdsEnPessoasAmover(eLista,&idOrigem,&idDestino,&nPessoasMover,salas,nSalas);

	eLista=fazMovimentacao(eLista,idOrigem,idDestino,nPessoasMover,pessoas,nPessoas,salas,nSalas);


	return eLista;
}

void terminarSimulacao(espaco* eLista) {
	espaco *aux = NULL;
	populacao *auxP = NULL;
	FILE* fp;

	fp = fopen("report.txt", "wt");

	if (fp == NULL) {
		printf("Erro ao abrir/criar o ficheiro report.txt para escrita!!\n");
		exit(EXIT_FAILURE);
	}

	aux = eLista;

	if (aux->nDias - 1 == 0) {
		printf("\n\n\tNao passou nenhum dia!\n");
		fprintf(fp,"\n\n\tNao passou nenhum dia!\n");
	
	}
	else {
		printf("\n\tPassaram %d dia(s)!!\n\n",aux->nDias-1);
		fprintf(fp,"\n\tPassaram %d dia(s)!!\n\n", aux->nDias - 1);
	}

	while (aux != NULL) {
		printf("\n\n\tNumero da Sala:%d\n\tNumero de pessoas:%d\n\tPessoas Doentes:%d\n\tPessoas Imunes:%d\n\tPessoas Saudaveis:%d\n\tNumero pessoas adicionadas:%d\n\tNumero de pessoas tranferidas:%d\n", aux->local->id, aux->nPessoas, aux->pessoasDoentes, aux->pessoasImunes, aux->pessoasSaudaveis,aux->nPessoasAdd,aux->nPessoasTranf);
		fprintf(fp,"\n\n\tNumero da Sala:%d\n\tNumero de pessoas:%d\n\tPessoas Doentes:%d\n\tPessoas Imunes:%d\n\tPessoas Saudaveis:%d\n\tNumero pessoas adicionadas:%d\n\tNumero de pessoas tranferidas:%d\n", aux->local->id, aux->nPessoas, aux->pessoasDoentes, aux->pessoasImunes, aux->pessoasSaudaveis, aux->nPessoasAdd, aux->nPessoasTranf);
		auxP = NULL;
		auxP = aux->listaPessoas;

		while (auxP != NULL) {

			printf("\n\t\tPessoa ID:%s\n\t\tIdade:%d\n\t\tEstado:%c\n", auxP->pessoa->id, auxP->pessoa->idade,auxP->pessoa->estado);
			fprintf(fp,"\n\t\tPessoa ID:%s\n\t\tIdade:%d\n\t\tEstado:%c\n", auxP->pessoa->id, auxP->pessoa->idade, auxP->pessoa->estado);

			if (auxP->pessoa->estado == 'D'){
				printf("\t\tNumero de dias infetado:%d\n", auxP->pessoa->nrDiasInfetado);
				fprintf(fp,"\t\tNumero de dias infetado:%d\n", auxP->pessoa->nrDiasInfetado);
			}

			if (auxP->pessoa->Curada == SIM && auxP->pessoa->estado=='S') {
			     
				printf("\t\tEsta pessoa esta Curada!!\n");
				fprintf(fp,"\t\tEsta pessoa esta Curada!!\n");
			     
			}

			if (auxP->pessoa->Curada == SIM && auxP->pessoa->estado == 'I' && auxP->pessoa->ficouImune==SIM) {
				printf("\t\tEsta pessoa ficou Imune!!\n");
				fprintf(fp,"\t\tEsta pessoa ficou Imune!!\n");
			}

			if (auxP->pessoa->pessoaA==SIM) {
				printf("\t\tFoi uma pessoa adicionada!!\n");
				fprintf(fp,"\t\tFoi uma pessoa adicionada!!\n");
			}
			
			if (auxP->pessoa->pessoaTranf==SIM) {
				printf("\t\tFoi uma pessoa tranferida!!\n");
				fprintf(fp,"\t\tFoi uma pessoa tranferida!!\n");
			}

			auxP = auxP->prox;
		}

		aux = aux->prox;

	}

	fclose(fp);
}

