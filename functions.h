/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   functions.h
 * Author: nunot
 *
 * Created on 6 de Maio de 2020, 10:07
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "defines.h"
#include "data.h"
#include<stdio.h>
#include<stdlib.h>
#include "utils.h"
#include <string.h>

// CONSOLA
void limpaStdin();
void pause();
void limpaEcra();
void menuInicial();
void mostraEstatisticas(espaco *eLista);

// FICHEIROS
int ficheiroPessoa(pessoa *p, FILE *fPessoa);
local* obtemFichSalas(local *salas, int *nSalas);
local* leFicheiroSalas(char * nomeFich, local *salas, int *nSalas);
pessoa* obtemFichPessoas(pessoa *pessoas, int *nPessoas);
pessoa* leFicheiroPessoas(char *nomeFich, pessoa *pessoas, int *nPessoas);
void escrevePessoasFich(char *nomeFich,pessoa *pessoas,int nPessoas);
void escreveFichPessoas(pessoa* pessoas, int nPessoas);

// VALIDAÇÕES
int verificaNumerosLidos(pessoa *p);
void validacoesSalasId(local* salas, int  nSalas);
void validacoesSalasLigacoes(local *salas, int nSalas);
void validacoesSalas(local  *salas, int nSalas);
void validacaoPessoasID(pessoa *pessoas,int  nPessoas);

// VERIFICA
void pedirEverificarIdLocal(local* salas, int nSalas, int *idLocal, espaco *eLista);
void pedirEverificarIdPessoa(char *idPessoa, pessoa *pessoas, int nPessoas);
void pedirEverificarIdade(int *idade);
void pedirEverificarNumeroDiaDeInfecao(int *nrDiasInf,int idade);
void pedirEverificarIdsEnPessoasAmover(espaco* eLista,int *idOrigem, int *idDestino,int *nPessoasMover,local *salas,int nSalas);
espaco*  verificarSeFicaImune(espaco *eLista,pessoa *pessoas, int nPessoas);

// SIMULAÇÃO
espaco* criaEspaco(espaco *eLista, local *salas, int nSalas);
void terminarSimulacao(espaco* eLista);
espaco* tranferirPessoas(espaco* eLista, pessoa* pessoas, int nPessoas, local* salas, int nSalas);
espaco* fazMovimentacao(espaco* eLista, int idOrigem, int idDestino, int nPessoasMover, pessoa* pessoas, int nPessoas,local *salas, int nSalas);
espaco* eListarecontroiLista(espaco *eLista,Ids *id,DadosLocal *dadosL,pessoa *pessoas,int nPessoas,local *salas,int nSalas);
DadosLocal* obtemDadosLocal(espaco* eLista, DadosLocal* dadosL, int nSalas);
void  ObtemDadosDoente(pessoa *pessoaAdd, pessoa *pessoas, int nPessoas, local *salas, int nSalas,espaco *eLista);
pessoa* addPessoaAoArrayPessoas(pessoa* pessoaAdd, pessoa* pessoas, int* nPessoas);
void libertaLista(espaco *eLista);
void atualizaInformacao(pessoa *pessoas,int nPessoas);
void atualizacaoDoDia(espaco* eLista);
espaco* avancaUmDia(espaco *eLista,pessoa *pessoas, int nPessoas,local *salas,int nSalas);
espaco* atualizaImunidadeNaLista(espaco *eLista, pessoa *pessoa);
espaco* probabilidadeDeRecuperacao(espaco *eLista, pessoa *pessoas, int nPessoas);
espaco* atualizaDadosNaLista(espaco* eLista, pessoa *pessoa);
espaco* AtualizaInfecao(espaco* eLista, pessoa* pessoas, int nPessoas);
espaco* doenteInfetaPessoas(espaco* eLista,pessoa *pessoas, int nPessoas);
int obtemRandomNoArray(int* pessoasSelecionadas, int nrPessoas, int nPessoasAux);
espaco* criacaoLocalPessoa(espaco *eLista,local *salas, int nSalas, pessoa *pessoas, int nPessoas);
espaco* criaPopulacao(espaco *eLista, local *salas, int nSalas, pessoa *pessoas, int nPessoas);
void inserePopulacaoFinalLista(espaco *aux, populacao *novaPopulacao);
void preenchePopulacao(espaco *aux, populacao *novaPopulacao, pessoa *pessoa);
void geraNumeroAleatorioSalas(int *n,int nSalas);
espaco* criaEspaco(espaco *eLista, local *salas, int nSalas);
espaco* insereEspacoFinalLista(espaco *eLista,espaco *novoEspaco);
void preencheEspaco(local *novoLocal,espaco *novoEspaco);

#endif /* FUNCTIONS_H */

