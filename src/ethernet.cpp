/*
 * ethernet.cpp
 *
 *  Created on: Feb 2, 2016
 *      Author: Stephen
 */


#include "ethernet.h"

const int port_number = 1111;

void error(const char *msg){
    perror(msg);
}

info get_ethernet() {
	info status;
	int sockfd, newsockfd, pid;
	     socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	// TODO Read Ethernet
	// Might be done
	// TODO test Ethernet
		
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		error("ERROR opening socket");
	
		status.manual_override = false;
		status.play_music = false;
		return status;
	}

    bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
	    sizeof(serv_addr)) < 0) {
	    error("ERROR on binding");

		status.manual_override = false;
		status.play_music = false;
		close(sockfd);
		return status;
	}

	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd,
      	(struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) {
		error("ERROR on accept");
		
		status.manual_override = false;
		status.play_music = false;
		close(sockfd);
		return status;
	}

	pid = fork();
	if (pid < 0) {
		error("ERROR on fork");
		
		status.manual_override = false;
		status.play_music = false;
		close(sockfd);
		return status;
	}

	if (pid == 0)  {
		// Read Ethernet
		char buffer[3];
      
		bzero(buffer,3);
		int n = read(newsockfd,buffer,2);
		if (n < 0) {
			error("ERROR reading from socket");
			status.manual_override = false;
			status.play_music = false;
			close(newsockfd);
    		close(sockfd);
			return status;
		} else {
			status.manual_override = (buffer[0] == 't');
			status.play_music = (buffer[1] == 't');
		}
	}
	close(newsockfd);
    close(sockfd);

	return status;
}

void play_music(Song song) {
	//TODO send song via Ethernet to DE2
	int sockfd, newsockfd, pid;
	     socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	// TODO Read Ethernet
		
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket for play_song");
    bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
		    sizeof(serv_addr)) < 0) {
	    error("ERROR on binding for play_song");

		status.manual_override = false;
		status.play_music = false;
		return status;
	}
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd,
      	(struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0)
		error("ERROR on accept for play_song");
	pid = fork();
	if (pid < 0)
		error("ERROR on fork for play_song");
	if (pid == 0)  {
		int n = write(sock,song,sizeof(song));
		if (n < 0)
			error("ERROR writing song");
	}
}
