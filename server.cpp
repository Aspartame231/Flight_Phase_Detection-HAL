#include<iostream>
#include<cstring>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")

int main(){
	
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2),&wsaData) !=0){
		std::cerr<<"Error: Failed to initialize Socket.\n";
		return 1;
	}
	//Create Server Socket
	serverSocket=socket(AF_INET,SOCK_STREAM,0);
	if(serverSocket == INVALID_SOCKET) {
		std::cerr<<"Error: Could not create socket.\n";
		WSACleanup();
		return 1;
	}
	
	//Setup Server Address
	ServerAddress.sin_family=AF_INET;
	ServerAddress.sin_port=htons(8888);
	ServerAddress.sin_addr.s_addr = INADDR_ANY;
	
	//Bind the server socket to a specific IP and port
	if(bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress))== SOCKET_ERROR){
		std::cerr<<"Error: Binding Failed. Error code:"<<WSAGetLastError() <<std::endl;
		closesocket(serversocket);
		WSACleanup();
		return 1;
	}
	
	//Listen for incomining traffic
	if(listen(serverSocket,SOMAXCONN)== SOCKET_ERROR){
		std:: cerr<<"Error: Listening failed.Error code:"<<WSAGetLastError()<<std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}
	std::cout<<"Server is listening for incoming connections..\n";
	
	int clientAddressSize=sizeof(clientAddress);
	clientSocket = accept(serverSocket,(struct sockAddr *)&clientAddress, &clientAddressSize);
	if(clientSocket== INVALID_SOCKET){
		std:: cerr<<"Error: Accepting connection failed. Error code:"<<WSAGetLastError()<<std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}
	cout<<"Client Connected";
	
	while(true){
		string in;
		
		if(recv(clientSocket,in,strlen(in),0)<0){
			std::cerr<<"Failed to receive data\n";
			return 1;
		}
		
		string out="";
		
		
		
		
		if(in=="10111111"){
			out+="Landing Phase";
		}
		else if(in=="01000111"){
			out+="Take Off Phase";
		}
		else if(in=="01000000"){
			out+="Normal Flight Phase";
		}
		else if(in=="10000111"){
			out+="Descent Phase";
		}
		else{
			out+="Not a Valid Phase";
		
		}
		if(send(sclientSocket,out,strlen(out),0)<0){
			std::cerr<<"Failed to send response\n";
			return 1;
		}
		std::cerr<<"Response Sent\n";
		
	}
	close(clientSocket);
	close(serverSocket);
	return 0;
}
