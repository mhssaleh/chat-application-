#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include <fstream> // Include the header for file operations

int clientSock; // Global variable to hold the client socket

// Function to encrypt a message using Caesar cipher
std::string caesarEncrypt(const std::string& message, int shift) {
    std::string encryptedMessage = "";
    for (char c : message) {
        // Encrypt uppercase letters
        if (isupper(c)) {
            encryptedMessage += char(int(c + shift - 65) % 26 + 65);
        }
        // Encrypt lowercase letters
        else if (islower(c)) {
            encryptedMessage += char(int(c + shift - 97) % 26 + 97);
        }
        // Ignore non-alphabetic characters
        else {
            encryptedMessage += c;
        }
    }
    return encryptedMessage;
}

// Function to decrypt a message using Caesar cipher
std::string caesarDecrypt(const std::string& encryptedMessage, int shift) {
    return caesarEncrypt(encryptedMessage, 26 - shift); // Decrypting is just encrypting with the inverse shift
}

// Function to send message to the client
void sendMessageToClient(const std::string& message) {
    std::string encrypted = caesarEncrypt(message, 7);
    if (send(clientSock, encrypted.c_str(), encrypted.length(), 0) < 0) {
        perror("Send failed");
        close(clientSock);
        exit(EXIT_FAILURE);
    } else {
        printf("Message sent to client: %s\n", message.c_str());
    }
}

// Function to handle receiving messages from the client
void *receiveMessages(void *arg) {
    char recvData[1024];
    while (1) {
        int recvSize = recv(clientSock, recvData, sizeof(recvData), 0);
        if (recvSize < 0) {
            perror("Receive failed");
            close(clientSock);
            exit(EXIT_FAILURE);
        } else if (recvSize == 0) {
            printf("Connection closed by client\n");
            close(clientSock);
            exit(EXIT_SUCCESS);
        }
        recvData[recvSize] = '\0';
        std::string decrypted = caesarDecrypt(recvData, 7);
        printf("Received message from client: %s\n", decrypted.c_str());
    }
}

// Function to handle user signup
void signup() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    // Encrypt password using Caesar cipher
    std::string encryptedPassword = caesarEncrypt(password, 7);

    // Check if username already exists
    std::ifstream file("usersinfo.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(username) != std::string::npos) {
            std::cout << "Username already exists. Please choose another one.\n";
            return;
        }
    }
    file.close();

    // Add user to the file
    std::ofstream outfile("usersinfo.txt", std::ios_base::app);
    if (!outfile) {
        std::cout << "Failed to write user info to file.\n";
        return;
    }
    outfile << username << ":" << encryptedPassword << std::endl;
    outfile.close();
    std::cout << "Signup successful. You can now login.\n";

    // Send welcome message to client
    sendMessageToClient("Welcome! Signup successful. You can now login.");
}

// Function to handle user login
void login() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    // Encrypt password using Caesar cipher
    std::string encryptedPassword = caesarEncrypt(password, 7);

    // Check if username and password match
    std::ifstream file("usersinfo.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line == username + ":" + encryptedPassword) {
            std::cout << "Login successful. Welcome!\n";
            file.close();

            // Send welcome message to client
            sendMessageToClient("Login successful. Welcome!");
            return;
        }
    }
    file.close();
    std::cout << "Invalid username or password. Please try again.\n";
}

int main() {
    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    } else {
        printf("Socket created successfully\n");
    }

    // Bind a local address to the socket
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(1765);
    if (bind(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(sock);
        return 1;
    } else {
        printf("Successful Binding Local Address to Socket\n");
    }

    // Listen for incoming connections
    if (listen(sock, SOMAXCONN) < 0) {
        perror("Listen failed");
        close(sock);
        return 1;
    } else {
        printf("Listening...\n");
    }

    // Accept a connection
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    clientSock = accept(sock, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSock < 0) {
        perror("Accept failed");
        close(sock);
        return 1;
    } else {
        printf("Accepted Connection\n");
    }

    // Create a thread to handle receiving messages from the client
    pthread_t receiveThread;
    if (pthread_create(&receiveThread, NULL, receiveMessages, NULL) != 0) {
        perror("Thread creation failed");
        close(clientSock);
        close(sock);
        return 1;
    }

    // Main loop to handle user interaction
    while (1) {
        int choice;
        std::cout << "1. Signup\n2. Login\nEnter choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                login();
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    // Close the client socket
    close(clientSock);

    // Close the server socket
    close(sock);

    return 0;
}
