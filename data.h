/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   data.h
 * Author: nunot
 *
 * Created on 6 de Maio de 2020, 10:02
 */

#ifndef DATA_H
#define DATA_H

#include "defines.h"

// salas lidas do ficheiro binário
typedef struct sala local, * plocal;
struct sala {
    int id; 
    int capacidade; 
    int liga[3]; 
};

typedef struct ids Ids, * pIds;
struct ids{
	int idLocal;
	char idPessoa[TAM_TEXTO];
};

// pessoas lidas do ficheiro de texto
typedef struct Pessoa pessoa, * pPessoa;
struct Pessoa
{   
	char id[TAM_TEXTO];
	int idade;
	char estado;
	int infetadaNoDiaAtual;
	int curadaNoDiaAtual;
	int nrDiasInfetado;
	int ficouImune;
	int Curada;
	int pessoaA;
	int pessoaTranf;
	local *localOndeSeEncontra; // aponta para a sala onde se encontra
};

//lista de pessoas
typedef struct Populacao populacao, *pPopulacao;
struct Populacao
{
	pessoa *pessoa;
	populacao *prox;
};

// espaço é uma lista de listas
typedef struct Espaco espaco, *pEspaco;
struct Espaco{
	local *local;
	int nPessoas;
	int nPessoasAdd;
	int nPessoasTranf;
	int pessoasSaudaveis;
	int pessoasDoentes;
	int pessoasImunes;
	int nDias;
	espaco *prox;
	populacao *listaPessoas;
};

// dados de cada sala
typedef struct dadosLocal DadosLocal, *pDadosLoca;
struct dadosLocal
{	int idLocal;
	int nPs;
	int nPessoasA;
	int pessoasS;
	int pessoasD;
	int pessoasI;
	int nD;
	int nPtranf;
};


#endif /* DATA_H */

