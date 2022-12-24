
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <stdio.h>

//Variaveis globais
#define FINALIZA 0
#define ATAQUE  1
#define ANOTA_ATAQUE 2
#define DEFESA  3
#define VERIFICA  4


int vez, acao = ATAQUE;
char mensagem[4];
char nome[2][10];


SOCKET serverSocket, clientSocket[2];

using namespace std;

void joga(int id) {

	cout << " Comecou a thread" << id << endl;
	char token[4], status[4];
	int ok1 = 0;
	int ok2 = 0;
	int ok3 = 0;
	int ok4 = 0;

	while (acao != FINALIZA) {
		if (id == vez) {
			if (acao == ATAQUE) {
				//Faz o ataque
				sprintf_s(token, "atq");
				//Avisa que eh para fazer o ataque
				send(clientSocket[id], token, sizeof(token), 0);
				//Recebe as coords do ataque
				ok1 = recv(clientSocket[id], mensagem, sizeof(mensagem), 0);
				cout << nome[id] << " ataca:" << mensagem << endl;

				acao = DEFESA;
				vez = 1 - vez;

			}
			else if (acao == ANOTA_ATAQUE) {
				//Anota a resposta do ataque
				//envia o resultado do ataque
				send(clientSocket[id], mensagem, sizeof(mensagem), 0);
				cout << nome[id] << " resultado:" << mensagem << endl;
				acao = VERIFICA; //Manda o outro verificar se perdeu
				vez = 1 - vez;


				//Verifica se ganhou
				//Manda mensagem perguntando status
				sprintf_s(token, "gan");
				send(clientSocket[id], token, sizeof(token), 0);
				ok4 = recv(clientSocket[id], status, sizeof(status), 0);

				if (status[0] == 'X') {
					cout << nome[id] << " ganhou!!!" << endl;
					acao = FINALIZA;
					break;
				}

			}
			else if (acao == DEFESA) {
				//Recebe o ataque
				//Avisa da defesa
				sprintf_s(token, "def");
				send(clientSocket[id], token, sizeof(token), 0);
				//Manda a mensagem do ataque
				send(clientSocket[id], mensagem, sizeof(mensagem), 0);
				//Recebe o resultado do ataque
				ok2 = recv(clientSocket[id], mensagem, sizeof(mensagem), 0);
				cout << nome[id] << " responde:" << mensagem << ok2 << endl;
				acao = ANOTA_ATAQUE;
				vez = 1 - vez;


			}
			else if (acao == VERIFICA) {
				//Verifica se perdeu
				//Manda mensagem perguntando status
				sprintf_s(token, "per");
				send(clientSocket[id], token, sizeof(token), 0);
				ok3 = recv(clientSocket[id], status, sizeof(status), 0);

				if (status[0] == 'X') {
					cout << nome[id] << " perdeu!!!" << endl;
					acao = FINALIZA;
					vez = 1 - vez;
					break;
				}
				else {
					acao = ATAQUE;
					//Nao troca a vez, quem verifica tambem ataca.
				}
			}
			else if (acao == FINALIZA) {
				break;
			}
			if (ok1 < 0 || ok2 < 0 || ok3 < 0) {
				cout << "Falha na recepcao1:" << ok1 << ok2 << ok3 << endl;
				break;
			}
		}
	}
}



int main() {

	cout << " Passo 1 - Inicializar o WSA \n\n";

	int port = 55555;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);

	if (wsaerr != 0) {
		cout << "O winsock dll nao foi encontrado!" << endl;
		return 0;

	}
	else {
		cout << "The winsock dll found!" << endl;
		cout << "The status: " << wsaData.szSystemStatus << endl;

	}


	cout << "\n\n\nStep 2 \n\n";

	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (serverSocket == INVALID_SOCKET) {
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "socket() is OK! " << endl;
	}



	cout << "\n\n\nStep 3 \n\n";

	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);

	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		cout << "Server: connect - falha " << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else {
		cout << "Client connect is OK!" << endl;
	}

	cout << "\n\n\nStep 4 \n\n";

	if (listen(serverSocket, 2) == SOCKET_ERROR) {
		cout << "listen(): Error listening the socket" << WSAGetLastError() << endl;
	}
	else {
		cout << "listen() is ok, waiting for connections" << endl;
	}

	cout << "\n\n\nStep 5\n\n";
	//******************************************************************************************


	//Aceita e pede o nome do primeiro jogador
	clientSocket[0] = accept(serverSocket, NULL, NULL);
	recv(clientSocket[0], nome[0], sizeof(nome[0]), 0);


	//Aceita e pede o nome do segundo jogador
	clientSocket[1] = accept(serverSocket, NULL, NULL);
	recv(clientSocket[1], nome[1], sizeof(nome[1]), 0);


	thread tZero(joga, 0);
	thread tUm(joga, 1);

	tZero.join();
	tUm.join();



	sprintf_s(mensagem, "T+!");
	send(clientSocket[0], mensagem, sizeof(mensagem), 0);
	send(clientSocket[1], mensagem, sizeof(mensagem), 0);


	cout << "Jogo Finalizado." << endl;
	cout << "Fechando os sockets." << endl;

	closesocket(clientSocket[0]);
	closesocket(clientSocket[1]);
	closesocket(serverSocket);
	WSACleanup();

	return 0;
}

