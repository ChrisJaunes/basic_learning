/*
* designed a exp about simple echo servee
* noted : function inet_ntoa() will cause segment falut in x64, but not in x86
* we deal the problem that we include <arrpa/inet.h> 
* @author ChrisJaunes
*/

#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <malloc.h>
#include <unistd.h>
static void start_simple_echo_server() {
	const char* const echo_host = "127.0.0.1";
	uint16_t echo_port = 1117;
	struct sockaddr_in* server = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	server->sin_family = AF_INET;
	server->sin_port = htons(echo_port);
	server->sin_addr.s_addr = inet_addr(echo_host);
	
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(server_fd, (struct sockaddr*)server, sizeof(*server))) {
		printf("bind failed\n");
		return;
	}
	listen(server_fd, SOMAXCONN);

	struct sockaddr_in* client = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	socklen_t client_size = sizeof(*client);
	char* buf = (char*)malloc(1001);
	ssize_t bytes;

	int clientfd = accept(server_fd, (struct sockaddr*)client, &client_size);
	printf("Connected to %s: %u\n\n", inet_ntoa(client->sin_addr), ntohs(client->sin_port));
	printf("Numeric : %u\n", ntohl(client->sin_addr.s_addr));
	while(1) {
		bytes = read(clientfd, (void*)buf, 1000);
		if (bytes <= 0) {
			close(clientfd);
			printf("Connection closed.\n");
			return;
		}
		printf("Bytes recevied: %u\n", (int)bytes);
		printf("Text: %s\n", buf);
		write(clientfd, buf, bytes);
	}
}
static void start_simple_echo_client() {
	const char* const echo_host = "127.0.0.1";
	int echo_port = 1117;
	struct sockaddr_in* server = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	server->sin_family = AF_INET;
	server->sin_port = htons(echo_port);
	server->sin_addr.s_addr = inet_addr(echo_host);

	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	printf("Connecting to %s \n", echo_host);
	printf("Numeric : %u\n", server->sin_addr);
	
	connect(server_fd, (struct sockaddr*)server, sizeof(*server));

	char buf[1000];
	while (1)
	{
		bzero(buf, sizeof(buf));
		scanf("%s", buf);
		if (strncmp(buf, "exit", 4) == 0) {
			close(server_fd);
			return;
		}
		write(server_fd, buf, sizeof(buf));
		bzero(buf, sizeof(buf));
		read(server_fd, buf, sizeof(buf));
		printf("echo:%s\n", buf);
	}
}
void Socket_exp1() {
	if (fork() == 0) {
		start_simple_echo_server();
	}
	else {
		start_simple_echo_client();
	}
}