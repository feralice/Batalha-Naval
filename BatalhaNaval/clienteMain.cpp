#include "stdafx.h"
#include "targetver.h"
#include "cliente.h"

#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <stdlib.h>

#include <string>
#include <thread>

#define BUFLEN 64 

using namespace std;


//Variaveis globais
#define ATAQUE  1
#define ANOTA_ATAQUE 
#define DEFESA  3
#define VERIFICA  4
Jogador eu;



int main() {


	setlocale(LC_ALL, "Portuguese");

	cout << "Step 1 \n\n";
	int port = 55555;
	SOCKET clientSocket;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);

	if (wsaerr != 0) {
		cout << "The winsock dll not found!" << endl;
		return 0;

	}
	else {
		cout << "The winsock dll found!" << endl;
		cout << "The status: " << wsaData.szSystemStatus << endl;

	}


	cout << "\n\n\nStep 2 \n\n";
	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientSocket == INVALID_SOCKET) {
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "socket() is OK! " << endl;
	}



	cout << "\n\n\nStep 3 \n\n";

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);

	int resul = connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService));

	if (resul == SOCKET_ERROR) {
		cout << "Client: connect - falha " << WSAGetLastError() << endl;
		closesocket(clientSocket);
		WSACleanup();
		return 0;
	}
	cout << "Você está conectado\n";

	cout << "Digite seu nome para começar o jogo: ";
	char nome[10];
	cin >> nome;
	eu.inicio(nome);
	//manda o nome para o servidor
	send(clientSocket, nome, sizeof(nome), 0);

	eu.jogada();
	cout << "Espere seu adversário\n";


	char mensagem[4];
	char status[4];

	bool fim = false;
	int ok1 = 0;
	int ok2 = 0;

	while (!fim) {

		recv(clientSocket, mensagem, sizeof(mensagem), 0);

		if (strcmp(mensagem, "atq") == 0) {

			sprintf_s(mensagem, eu.ataque());
			send(clientSocket, mensagem, sizeof(mensagem), 0);
			ok1 = recv(clientSocket, mensagem, sizeof(mensagem), 0);
			eu.respostaAtaque(mensagem);
		}
		else if (strcmp(mensagem, "def") == 0) {

			ok2 = recv(clientSocket, mensagem, sizeof(mensagem), 0);
			strcpy_s(mensagem, eu.defesa(mensagem));
			send(clientSocket, mensagem, sizeof(mensagem), 0);
		}
		else if (strcmp(mensagem, "per") == 0) {

			strcpy_s(status, eu.perdeu());
			send(clientSocket, status, sizeof(status), 0);
			fim = (status[0] == 'X');

			if (fim) {
				cout << "Você perdeu :(" << endl;
			}

		}
		else if (strcmp(mensagem, "gan") == 0) {

			strcpy_s(status, eu.ganhou());
			send(clientSocket, status, sizeof(status), 0);
			fim = (status[0] == 'X');

			if (fim) {
				cout << "Você ganhou :D !!!!!!!!!!!!" << endl;
			}
		}
		if (ok1 < 0 || ok2 < 0) {
			cout << " Erro no recebimento" << ok1 << ok2 << endl;
			break;
		}
	}

	recv(clientSocket, mensagem, sizeof(mensagem), 0);
	cout << mensagem << endl;



	cout << "Fechando o socket..." << endl;


	closesocket(clientSocket);

	WSACleanup();
	return 0;

}