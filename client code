#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <fstream>
#include <iostream> // Added for user-friendly input/output

int clientSock; // Global variable to hold the client socket
bool loggedIn = false; // Flag to track if user is logged in

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

// Function to handle receiving messages from the server
void *receiveMessages(void *arg) {
    char recvData[1024];
    while (1) {
        int recvSize = recv(clientSock, recvData, sizeof(recvData), 0);
        if (recvSize < 0) {
            perror("Receive failed");
            close(clientSock);
            exit(EXIT_FAILURE);
        } else if (recvSize == 0) {
            printf("Connection closed by server\n");
            close(clientSock);
            exit(EXIT_SUCCESS);
        }
        recvData[recvSize] = '\0';
        std::string decrypted = caesarDecrypt(recvData, 7);
        printf("Received message from server: %s\n", decrypted.c_str());
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

    // Check for username duplication
    std::ifstream file("usersinfo.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(username + ":") != std::string::npos) {
            std::cout << "Username already exists. Please choose another one." << std::endl;
            file.close();
            return;
        }
    }
    file.close();

    // Add user to the file
    std::ofstream outfile("usersinfo.txt", std::ios_base::app);
    if (!outfile) {
        std::cerr << "Failed to write user info to file." << std::endl;
        return;
    }
    outfile << username << ":" << encryptedPassword << std::endl;
    outfile.close();
    std::cout << "Signup successful. You can now login." << std::endl;
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

    // Check credentials from the file
    std::ifstream file("usersinfo.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line == username + ":" + encryptedPassword) {
            std::cout << "Login successful. Welcome!" << std::endl;
            loggedIn = true; // Set the flag to indicate user is logged in
            file.close();
            return;
        }
    }
    file.close();
    std::cout << "Invalid username or password. Please try again." << std::endl;
}

int main() {
    // Create a socket
    clientSock = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSock < 0) {
        perror("Socket creation failed");
        return 1;
    } else {
        printf("Socket created successfully\n");
    }

    // Connect to server
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1765);
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return 1;
    }

    if (connect(clientSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        close(clientSock);
        return 1;
    } else {
        printf("Connected to server\n");
    }

    // Create a thread to handle receiving messages from the server
    pthread_t receiveThread;
    if (pthread_create(&receiveThread, NULL, receiveMessages, NULL) != 0) {
        perror("Thread creation failed");
        close(clientSock);
        return 1;
    }

    // Main loop to handle user interaction
    while (1) {
        if (!loggedIn) {
            // Perform login
            int choice;
            std::cout << "1. Signup\n2. Login\nEnter your choice: ";
            std::cin >> choice;
            std::cin.ignore(); // Clear the newline character from the input buffer
            switch (choice) {
                case 1:
                    signup();
                    break;
                case 2:
                    login();
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    break;
            }
        } else {
            // Send message to server
            printf("Enter text to send to the server: ");
            char sendData[1024];
            fgets(sendData, sizeof(sendData), stdin);

            // Remove newline character from the input
            size_t len = strlen(sendData);
            if (sendData[len - 1] == '\n') {
                sendData[len - 1] = '\0';
            }

            std::string encrypted = caesarEncrypt(sendData, 7);
            if (send(clientSock, encrypted.c_str(), encrypted.length(), 0) < 0) {
                perror("Send failed");
                close(clientSock);
                return 1;
            } else {
                printf("Data sent to server\n");
            }
        }
    }

    // Close the socket
    close(clientSock);

    return 0;
}
