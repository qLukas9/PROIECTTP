#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 5050
#define BUFFER_SIZE 1024

int main(void) {
    WSADATA wsa;
    SOCKET server_fd, client1, client2;
    struct sockaddr_in serveraddress, clientaddress;
    int addrlen = sizeof(clientaddress);
    char buffer[BUFFER_SIZE];
    FILE *user;
    char nume[32],pass[32],rating[10],passbuf[32];

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        return EXIT_FAILURE;
    }

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        printf("Socket creation failed. Error: %d\n", WSAGetLastError());
        WSACleanup();
        return EXIT_FAILURE;
    }

    serveraddress.sin_family = AF_INET;
    serveraddress.sin_addr.s_addr = INADDR_ANY;
    serveraddress.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&serveraddress, sizeof(serveraddress)) == SOCKET_ERROR) {
        printf("Bind failed. Error: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return EXIT_FAILURE;
    }
    if (listen(server_fd, 2) == SOCKET_ERROR) {
        printf("Listen failed. Error: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return EXIT_FAILURE;
    }

    printf("Server listening on Port: %d\n", PORT);
   
    if ((user = fopen("user.txt", "r+")) == NULL) {
        perror("Error opening user.txt");
        closesocket(server_fd);
        WSACleanup();
        return EXIT_FAILURE;
    }
    
    printf("Waiting for two players to connect...\n");
    char ch;
    int ok=0,playergasit=0,ok1=0,i=0,j=0,k;
    while (1) {
        memset(buffer,0,BUFFER_SIZE);
        passbuf[0]='\0';
        ok=0;
        playergasit=0;
        i=0;
        j=0;
        k=0;
        nume[0]='\0';
        pass[0]='\0';
        rating[0]='\0';
        ok1=0;
        client1 = accept(server_fd, (struct sockaddr*)&clientaddress, &addrlen);
        if (client1 == INVALID_SOCKET) {
            printf("Accept failed for client1. Error: %d\n", WSAGetLastError());
            continue;
        }
        printf("Player 1 connected!\n");
        while(playergasit!=1)
        {
            memset(buffer,0,BUFFER_SIZE);
        passbuf[0]='\0';
        ok=0;
        playergasit=0;
        i=0;
        j=0;
        k=0;
        nume[0]='\0';
        pass[0]='\0';
        rating[0]='\0';
        ok1=0;
        memset(buffer,0,BUFFER_SIZE);
        recv(client1,buffer,BUFFER_SIZE,0);
        recv(client1,passbuf,32*sizeof(char),0);
        while((ch=fgetc(user))!=EOF)
        {

            if(ok1==1)
            {
                if(ch=='\n')
            {
                strcpy(buffer,"ok");
                send(client1,buffer,BUFFER_SIZE,0);
                playergasit=1;
                break;
            }
                rating[k]=ch;
                k++;
            }
            else{
            if(ok==1)
            {
                if(ch=='\n')
                {   
                    send(client1,buffer,BUFFER_SIZE,0);
                    break;
                }
                else
                {
                    if(ch==';')
                    {
                        if(strcmp(pass,passbuf)==0)
                        {
                            ok1=1;
                            
                        }
                        else
                        {
                            send(client1,buffer,BUFFER_SIZE,0);
                            break;
                        }
                    }
                    pass[j]=ch;
                    j++;
                }
            }
            else
            {   if(ch==';')
                {
                    if(strcmp(nume,buffer)==0)
                        ok=1;
                    else
                    nume[0] = '\0';
                }
                else{
                if(ch=='\n')
                    nume[0] = '\0';
                else
                {
                    nume[i]=ch;
                    i++;
                }
            }
            }
        }
        }
       if(playergasit==0){ fprintf(user,"\n%s;%s;500",buffer,passbuf);
        strcpy(rating,"500");
        strcpy(buffer,"ok");
        send(client1,buffer,BUFFER_SIZE,0);}
        break;
    }   
        send(client1,rating,sizeof(rating),0);
        memset(buffer,0,BUFFER_SIZE);
        passbuf[0]='\0';
        ok=0;
        playergasit=0;
        i=0;
        j=0;
        k=0;
        nume[0]='\0';
        pass[0]='\0';
        rating[0]='\0';
        ok1=0;
        client2 = accept(server_fd, (struct sockaddr*)&clientaddress, &addrlen);
        if (client2 == INVALID_SOCKET) {
            printf("Accept failed for client2. Error: %d\n", WSAGetLastError());
            closesocket(client1);
            continue;
        }
        printf("Player 2 connected!\n");
        while(playergasit!=1)
        {
            memset(buffer,0,BUFFER_SIZE);
        passbuf[0]='\0';
        ok=0;
        playergasit=0;
        i=0;
        j=0;
        k=0;
        nume[0]='\0';
        pass[0]='\0';
        rating[0]='\0';
        ok1=0;
        memset(buffer,0,BUFFER_SIZE);
        recv(client2,buffer,BUFFER_SIZE,0);
        recv(client2,passbuf,32*sizeof(char),0);
        while((ch=fgetc(user))!=EOF)
        {printf("%sok=%d\n",nume,ok);
            if(ok1==1)
            {
                if(ch=='\n')
            {
                strcpy(buffer,"ok");
                send(client2,buffer,BUFFER_SIZE,0);
                playergasit=1;
                break;
            }
                rating[k]=ch;
                k++;
            }
            else{
            if(ok==1)
            {
                if(ch=='\n')
                {   
                    send(client2,buffer,BUFFER_SIZE,0);
                    break;
                }
                else
                {
                    if(ch==';')
                    {
                        if(strcmp(pass,passbuf)==0)
                        {
                            ok1=1;
                            
                        }
                        else
                        {
                            send(client2,buffer,BUFFER_SIZE,0);
                            break;
                        }
                    }
                    pass[j]=ch;
                    j++;
                }
            }
            else
            {   if(ch==';')
                {
                    if(strcmp(nume,buffer)==0)
                        ok=1;
                    else
                    nume[0]='\0';
                }
                else{
                if(ch=='\n')
                    nume[0] = '\0';
                else
                {
                    nume[i]=ch;
                    i++;
                }
            }
        }
        }
        }
        if(playergasit==0)
        {fprintf(user,"\n%s;%s;500",buffer,passbuf);
        strcpy(rating,"500");
        strcpy(buffer,"ok");
        send(client2,buffer,BUFFER_SIZE,0);}
        break;
        
    }  
        send(client2,rating,sizeof(rating),0);
        memset(buffer,0,BUFFER_SIZE);
        passbuf[0]='\0';
        ok=0;
        playergasit=0;
        i=0;
        j=0;
        k=0;
        nume[0]='\0';
        pass[0]='\0';
        rating[0]='\0';
        ok1=0; 

        strcpy(buffer, "START1");
        send(client1, buffer, strlen(buffer), 0);

        strcpy(buffer, "START2");
        send(client2, buffer, strlen(buffer), 0);

        int current_turn = 1;

        while (1) {
            memset(buffer, 0, BUFFER_SIZE);

            if (current_turn == 1) {
                int recv_len = recv(client1, buffer, BUFFER_SIZE, 0);
                if (recv_len <= 0) {
                    printf("Player 1 disconnected.\n");
                    closesocket(client2);
                    break;
                }
                printf("Received from client1: %s\n", buffer);
                send(client2, buffer, recv_len, 0);
                current_turn = 2;
            } else {
                int recv_len = recv(client2, buffer, BUFFER_SIZE, 0);
                if (recv_len <= 0) {
                    printf("Player 2 disconnected.\n");
                    closesocket(client1);
                    break;
                }
                printf("Received from client2: %s\n", buffer);
                send(client1, buffer, recv_len, 0);
                current_turn = 1;
            }

            if (strcmp(buffer, "GAME_OVER") == 0) {
                break;
            }
        }

        closesocket(client1);
        closesocket(client2);
    }

    fclose(user);
    closesocket(server_fd);
    WSACleanup();
    return 0;
}
