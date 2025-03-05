// Chat sender code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

#define BUF_SIZE 1024

char *SenderPipe = "/tmp/SenderPipe";
char *ReceiverPipe = "/tmp/ReceiverPipe";

// User-defined function
void cleanup() {
    unlink(SenderPipe);
    unlink(ReceiverPipe);
}

void signal_handler(int sig) {
    printf("\nUser exited the chat.\n");
    cleanup();
    exit(0);
}

// Main function
int main() {
    char buffer[BUF_SIZE];

    signal(SIGINT, signal_handler);

    if (mkfifo(SenderPipe, 0666) < 0 && errno != EEXIST) {
        perror("Error creating sender_fifo");
        exit(EXIT_FAILURE);
    }

    if (mkfifo(ReceiverPipe, 0666) < 0 && errno != EEXIST) {
        perror("Error creating receiver_fifo");
        unlink(SenderPipe);
        exit(EXIT_FAILURE);
    }

    printf("\n----------WELCOME TO MNH CHAT SYSTEM----------\n");
    printf("Instructions: Type 'exit' to quit.\n");
    printf("I am User 1 (😊)\n");

    while (1) {
        int Receiver = open(ReceiverPipe, O_WRONLY);
        if (Receiver < 0) {
            perror("Error opening receiver_fifo");
            cleanup();
            exit(EXIT_FAILURE);
        }

        printf("You (😊): ");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "exit") == 0) {
            char exitMessage[] = "User 1 has left the chat. Goodbye! 😊";
            write(Receiver, exitMessage, strlen(exitMessage) + 1);
            printf("Goodbye! Have a great day! 😊\n");
            break;
        }

        write(Receiver, buffer, strlen(buffer) + 1);
        close(Receiver);

        int Sender = open(SenderPipe, O_RDONLY);
        if (Sender < 0) {
            perror("Error opening sender_fifo");
            cleanup();
            exit(EXIT_FAILURE);
        }

        read(Sender, buffer, BUF_SIZE);
        printf("Sender (📩): %s\n", buffer);
        close(Sender);
        
        if (strcmp(buffer, "User 2 has left the chat. Goodbye! 😊") == 0) {
            break;
        }
    }

    cleanup();
    return 0;
}