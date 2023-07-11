#include<iostream>
#include<cstring>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")

const int BUFFER_SIZE = 1024;
int main(){
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2),&wsaData) !=0){
		std::cerr<<"Error: Failed to initialize Socket.\n";
		return 1;
	}
	SOCKET clientSocket;
	struct sockaddr_in serverAddress;
	
	//Create client Socket
	clientSocket =socket(AF_INET,SOCK_STREAM, 0);
	if(clientSocket == INVALID_SOCKET){
		std::cerr<<"Error: Could not create socket.\n";
		WSACleanup();
		return 1;
	}
	
	//Setup Server Address
	ServerAddress.sin_family=AF_INET;
	ServerAddress.sin_port=htons(1900);
	ServerAddress.sin_addr.s_addr = inet_addr("169.254.245.132");
	
	//Connect to server
	if(connect(clientSocket, (struct sockaddr *)&serverAddress , sizeof(serverAddress))== SOCKET_ERROR){
		std::cerr<<"Error: Connection failed. Error code:"<<WSAGetLastError()<<std::endl;
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}
	
	std::cout<<"Connected to the server.\n";
	
	
	while(true){
	 
	//Send Data to the server
	string msg="";
	char a;
	cout<<"Flight Phase detection System\n";
	cout<<"Enter the data:\n";
	cout<<"Left UnderCarriage :";
	cin>>a;
	if(a=='-1'){
		break;
	}
	msg+=a;
	cout<<"Right UnderCarriage :";
	cin>>a;
	msg+=a;
	cout<<"Nose UnderCarriage :";
	cin>>a;
	msg+=a;
	cout<<"Left UnderCarriage Door :";
	cin>>a;
	msg+=a;
	cout<<"Right UnderCarriage Door :";
	cin>>a;
	msg+=a;
	cout<<"Nose UnderCarriage :";
	cin>>a;
	msg+=a;
	
	cout<<"Wheel up :";
	cin>>a;
	msg+=a;
	cout<<"Wheel down :";
	cin>>a;
	msg+=a;
	
	if(send(clientSocket,msg,strlen(msg),0)<0){
		std::cerr<<"Error";
		return 1;
	}
	std::cout<<"Message Sent\n";
	
	//Receive the response
	string res;
	if(recv(clientSocket,res,strlen(res),0)<0){
		std::cerr<<"Error\n";
		return 1;
	}
	std::cout<<"Flight Phase:"<<res<<endl;
   }
   close(clientSocket);
   return 0;
}
