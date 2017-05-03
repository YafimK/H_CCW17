//
// Created by fimka on 13/03/17.
//

#include <stdio.h>
#include <stdlib.h>
#include "Acceptor.hpp"
#include "Metrics.hpp"

int main(int argc, char **argv) {
    if (argc < 2 || argc > 4) {
        printf("usage: server <port> [<ip>]\n");
        exit(1);
    }

    Stream *stream = NULL;
    Acceptor *acceptor = NULL;
    if (argc == 3) {
        acceptor = new Acceptor(atoi(argv[1]), argv[2]);
    } else {
        acceptor = new Acceptor(atoi(argv[1]));
    }
    if (acceptor->start() == 0) {
        while (1) {
            stream = acceptor->accept();
            if (stream != NULL) {
                int len;
                char line[MAX_PACKET_SIZE];
                while ((len = stream->receive(line, sizeof(line), 5)) > 0) {
                    line[len] = '\0';
                    stream->send(line, len);
                    printf("received - %s\n", line);
                }
                delete stream;
            }
        }
    }
    perror("Could not start the server");
    exit(-1);
}
