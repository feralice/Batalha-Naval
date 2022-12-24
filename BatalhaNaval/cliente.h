#pragma once

#include <iostream>
#include <string>
using namespace std;
class Jogador {
public:

	char tabuleiroMeu[10][10]{

	{'-','-','-','-','-','-','-','-','-','-'},
	{'-','-','-','-','-','-','-','-','-','-'},
	{'-','-','-','-','-','-','-','-','-','-'},
	{'-','-','-','-','-','-','-','-','-','-'},
	{'-','-','-','-','-','-','-','-','-','-'},
	{'-','-','-','-','-','-','-','-','-','-'},
	{'-','-','-','-','-','-','-','-','-','-'},
	{'-','-','-','-','-','-','-','-','-','-'},
	{'-','-','-','-','-','-','-','-','-','-'},
	{'-','-','-','-','-','-','-','-','-','-'}
	};

	char tabuleiroInimigo[10][10]{

	{'.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.'}
	};

	int submarinos = 3; //2 quadrados
	int contratorpederos = 2; //3 q
	int navio_tanque = 1; //4 q
	int porta_aviao = 1; //5 q

	int barco = 0;
	int soma = 0;

	char* nome;
	int afundadoInimigo;
	int afundadoMeu;

	void inicio(char* nomeEntrada);
	void imprimeTabuleiro(char tabuleiro[10][10]);
	void navios();
	void direcoes();
	void jogada();

	void insere(int posicao, char direcao, int linha, int coluna, char letra);

	int verificaInsere(int linha, int coluna, char direcao, char barco);

	int letraNumero(char letra);
	char numeroLetra(int numero);


	char* ataque();
	void respostaAtaque(char* resposta);
	char* defesa(char* coordenaas);
	char* perdeu();
	char* ganhou();

};
