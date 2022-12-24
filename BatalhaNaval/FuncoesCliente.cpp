#include <iostream>
#include <string>
#include "cliente.h"

using namespace std;

void Jogador::imprimeTabuleiro(char tabuleiro[10][10]) {

	cout << "	A B C D E F G H I J\n\n";
	for (int i = 0; i < 10; i++) {
		cout << i + 1 << "	";
		for (int j = 0; j < 10; j++) {
			cout << tabuleiro[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n";

}



int Jogador::letraNumero(char letra) {

	switch (letra) {
	case 'A':
		return 0;
	case 'B':
		return 1;
	case 'C':
		return 2;
	case 'D':
		return 3;
	case 'E':
		return 4;
	case 'F':
		return 5;
	case 'G':
		return 6;
	case 'H':
		return 7;
	case 'I':
		return 8;
	case 'J':
		return 9;
	default:
		cout << letra << endl;
		return 0;
	}
}

char Jogador::numeroLetra(int numero) {

	switch (numero) {
	case 0:
		return 'A';
	case 1:
		return 'B';
	case 2:
		return 'C';
	case 3:
		return 'D';
	case 4:
		return 'E';
	case 5:
		return 'F';
	case 6:
		return 'G';
	case 7:
		return 'H';
	case 8:
		return 'I';
	case 9:
		return 'J';
	default:
		cout << numero << endl;
		return 'A';
	}

}

void Jogador::navios() {

	cout << "Restam "<< porta_aviao << " unidades	-	1x Porta - Avião(cinco quadrados) - P" << endl;
	cout << "Restam "<< navio_tanque << " unidades	-	1x Navio-tanque (quatro quadrados) - N" << endl;
	cout << "Restam " << contratorpederos << " unidades	-	2x Contratorpedeiros (três quadrados) - C" << endl;
	cout << "Restam " << submarinos << " unidades	-	3x Submarinos (dois quadrados) - S " << endl;

}


void Jogador::inicio(char* nomeEntrada) {

	cout << "\nBATALHA NAVAL" << endl;
	cout << "\nRegras do jogo: \nCada jogador coloca os seus navios em um de seus tabuleiros, alinhados horizontalmente ou verticalmente.\nO n�mero de navios permitidos � igual para ambos jogadores e os navios n�o podem se sobrepor\n";
	cout << "\nTIPOS DE NAVIOS: " << endl;
	navios();

	nome = nomeEntrada;
	cout << "Comecou o jogo para " << nome << "!" << endl;

	cout << "\n\n Esse é o seu tabuleiro: " << endl;
	imprimeTabuleiro(tabuleiroMeu);
	afundadoInimigo = 0;
	afundadoMeu = 0;
}

void Jogador::direcoes() {

	cout << "\nEsquerda - Digite E" << endl;
	cout << "Direita - Digite D" << endl;
	cout << "Cima - Digite C" << endl;
	cout << "Baixo - Digite B" << endl;


}

void Jogador::insere(int posicao, char direcao, int linha, int coluna, char letra) {


	int conf1 = linha;
	int conf2 = coluna;
	int contador = 0;
	int confere = 0;
	int cont = 0;


	//se a direção for a direita
	if (direcao == 'D') {

		//confere se está tudo vazio
		while (contador < posicao) {

			if (tabuleiroMeu[conf1][conf2] != '-') {
				cout << "Erro, as posições não estão vazias\n";
				confere++;
				break;
			}
			conf2++;
			contador++;
		}

		//insere o porta-avião
		while (linha <= 9 && coluna <= 9 && linha >= 0 && coluna >= 0 && cont < posicao && confere == 0) {

			if (coluna + posicao > 9 || coluna + posicao < 0) {
				cout << "\ncoluna inválida para as posições" << endl;
				break;
			}

			tabuleiroMeu[linha][coluna] = letra;
			coluna++;
			cont++;

		}
	}

	//Se a direção for a esquerda
	else if (direcao == 'E') {

		contador = posicao;

		//confere se está tudo vazio
		while (contador >= 0) {

			if (tabuleiroMeu[conf1][conf2] != '-') {
				cout << "Erro, as posições não estão vazias\n";
				confere++;
				break;
			}
			conf2--;
			contador--;
		}

		//insere o porta-avi�o
		while (linha <= 9 && coluna <= 9 && linha >= 0 && coluna >= 0 && cont < posicao && confere == 0) {

			if (coluna - posicao > 9 || coluna - posicao < 0) {
				cout << "\ninválido para as posições" << endl;
				break;
			}

			tabuleiroMeu[linha][coluna] = letra;
			coluna--;
			cont++;

		}


	}//se a direção for para baixo
	else if (direcao == 'B') {

		contador = 0;

		//confere se está tudo vazio
		while (contador < posicao) {

			if (tabuleiroMeu[conf1][conf2] != '-') {
				cout << "Erro, as posições não estão vazias\n";
				confere++;
				break;
			}
			conf1++;
			contador++;
		}

		//insere o porta-avi�o
		while (linha <= 9 && coluna <= 9 && linha >= 0 && coluna >= 0 && cont < posicao && confere == 0) {

			if (linha + posicao > 9) {
				cout << "\ninválido para as posições" << endl;
				break;
			}

			tabuleiroMeu[linha][coluna] = letra;
			linha++;
			cont++;
		}

	}
	//se a direção for para cima
	else if (direcao == 'C') {

		contador = 0;

		//confere se está tudo vazio
		while (contador < posicao) {

			if (tabuleiroMeu[conf1][conf2] != '-') {
				cout << "Erro, as posições não estão vazias\n";
				confere++;
				break;
			}
			conf1--;
			contador++;
		}

		//insere o porta-avião
		while (linha <= 9 && coluna <= 9 && linha >= 0 && coluna >= 0 && cont < posicao && confere == 0) {

			if (linha - posicao > 9 || linha - posicao < 0) {
				cout << "\ninválido para as posições" << endl;
				break;
			}

			tabuleiroMeu[linha][coluna] = letra;
			linha--;
			cont++;
		}


	}

}

int Jogador::verificaInsere(int linha, int coluna, char direcao, char barco) {

	linha--;

	//se for Porta-Avião
	if (barco == 'P') {

		if (porta_aviao == 0) {
			cout << "Os porta-aviões acabaram" << endl;
			return -1;
		}

		insere(5, direcao, linha, coluna, 'P');
		porta_aviao--;

	}
	else if (barco == 'N') {

		if (navio_tanque == 0) {
			cout << "Os navios-tanque acabaram" << endl;
			return -1;
		}

		insere(4, direcao, linha, coluna, 'N');
		navio_tanque--;

	}
	else if (barco == 'C') {

		if (contratorpederos == 0) {
			cout << "Os contratorpederos acabaram" << endl;
			return -1;
		}

		insere(3, direcao, linha, coluna, 'C');
		contratorpederos--;

	}
	else if (barco == 'S') {

		if (submarinos == 0) {
			cout << "Os submarinos acabaram" << endl;
			return -1;
		}

		insere(2, direcao, linha, coluna, 'S');
		submarinos--;

	}


	return 0;
}

void Jogador::jogada() {

	char escolha;
	char escolhaD;
	int linha, col;
	char coluna;

	cout << "\n\nSeu tabuleiro está assim: " << endl;
	imprimeTabuleiro(tabuleiroMeu);

	int soma = porta_aviao + navio_tanque + contratorpederos + submarinos;

	while (soma != 0) {

		cout << "Qual navio você deseja colocar? (P,N,C,S) : \n" << endl;
		navios();
		cin >> escolha;

		cout << "Escolha a linha que deseja inserir (número) : ";
		cin >> linha;
		cout << "Escolha a coluna que deseja inserir (letra) : ";
		cin >> coluna;
		col = letraNumero(coluna);
		direcoes();
		cin >> escolhaD;

		if (verificaInsere(linha, col, escolhaD, escolha) == 0) {
			imprimeTabuleiro(tabuleiroMeu);
		}
		soma--;

	}


}

bool validou(int linha, char coluna) {

	if (linha > 9 || linha < 0) {
		return false;
	}

	if (coluna > 'J' || coluna > 'A') {
		return false;
	}

	return true;
}



char* Jogador::ataque() {
	char colString;
	char linString[3];
	int lin, col;
	bool jogadaRuim = true;
	char* resposta = new char[4];

	cout << "\n\n Esse e o  tabuleiro inimigo: " << endl;
	imprimeTabuleiro(tabuleiroInimigo);

	while (jogadaRuim) {
		cout << nome << ", faça sua jogada:" << endl;
		cout << "Linha: ";
		cin >> linString;
		cout << "Coluna: ";
		cin >> colString;


		//Arruma as coordenadas
		colString = toupper(colString);
		col = letraNumero(colString);

		if (linString[0] == '1' && linString[1] == '0') {
			lin = 9;
		}
		else {
			lin = atoi(linString) - 1;
		}

		if (validou(lin, col)) {
			if (tabuleiroInimigo[lin][col] == '.')
				jogadaRuim = false;
			else
				cout << "Posição ja foi revelada, tente outra." << endl;
		}
		else {
			cout << "Coordenadas inválidas, digite novamente." << endl;
		}
	}
	resposta[0] = ' ';
	resposta[1] = lin + 1 + '0';
	resposta[2] = colString;
	resposta[3] = '\0';
	return resposta;
}
void Jogador::respostaAtaque(char* resposta) {
	//resposta tem 3 caracteres, o que acertou, linha e coluna
	

	int lin, col;
	if (resposta[0] == '-') {
		cout << "\nVocê acertou água :(" << endl;
	}
	else {
		if (resposta[0] == 'S') {
			cout << "\nVocê acertou um Submarino!! " << endl;
			barco++;
		}
		else if (resposta[0] == 'C') {
			cout << "\nVocê acertou um Contra-Torpedeiro!!! " << endl;
			barco++;

		}
		else if (resposta[0] == 'N') {
			cout << "\nVocê acertou um Navio_Tanque!!!!" << endl;
			barco++;

		}
		else if (resposta[0] == 'P') {
			cout << "\nVocê acertou um Porta-Avioes!!!!! " << endl;
			barco++;

		}
		afundadoInimigo++;
	}

	lin = resposta[1] - '0' - 1;
	col = letraNumero(resposta[2]);
	tabuleiroInimigo[lin][col] = resposta[0];

	imprimeTabuleiro(tabuleiroInimigo);
}

char* Jogador::defesa(char* coordenadas) {
	//coordenadas tem somente 2 caracteres: linha e coluna
	int lin, col;
	char* resposta = new char[4];

	lin = coordenadas[1] - '0' - 1;
	col = letraNumero(coordenadas[2]);
	cout << "Ataque recebido na posição: " << lin + 1 << coordenadas[2] << endl;
	resposta[0] = tabuleiroMeu[lin][col];
	if (tabuleiroMeu[lin][col] == '-') {
		tabuleiroMeu[lin][col] = '+';
	}
	else {
		tabuleiroMeu[lin][col] = tolower(resposta[0]);
		afundadoMeu++;
	}
	imprimeTabuleiro(tabuleiroMeu);


	resposta[1] = coordenadas[1];
	resposta[2] = coordenadas[2];
	resposta[3] = '\0';
	return(resposta);
}

char* Jogador::perdeu() {
	char* retorno = new char[4];
	if (afundadoMeu ==21) // (submarinos * 2 + contratorpederos * 3 + navio_tanque * 4 + porta_aviao * 5));
		retorno[0] = 'X';
	else
		retorno[0] = 'O';
	retorno[1] = '\0';
	return(retorno);
}

char* Jogador::ganhou() {
	char* retorno = new char[4];
	if (afundadoInimigo == 21) // (submarinos * 2 + contratorpederos * 3 + navio_tanque * 4 + porta_aviao * 5));
		retorno[0] = 'X';
	else
		retorno[0] = 'O';
	retorno[1] = '\0';
	return(retorno);
}