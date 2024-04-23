  $$\ $$\          $$$$$$\                                                           $$$$$$\  $$\                  $$\            $$$$$$\                      $$\ $$\                     $$\     $$\                     
  $$ \$$ \        $$  __$$\                                                         $$  __$$\ $$ |                 $$ |          $$  __$$\                     $$ |\__|                    $$ |    \__|                    
$$$$$$$$$$\       $$ /  \__| $$$$$$\   $$$$$$$\ $$\   $$\  $$$$$$\   $$$$$$\        $$ /  \__|$$$$$$$\   $$$$$$\ $$$$$$\         $$ /  $$ | $$$$$$\   $$$$$$\  $$ |$$\  $$$$$$$\ $$$$$$\ $$$$$$\   $$\  $$$$$$\  $$$$$$$\  
\_$$  $$   |      \$$$$$$\  $$  __$$\ $$  _____|$$ |  $$ |$$  __$$\ $$  __$$\       $$ |      $$  __$$\  \____$$\\_$$  _|        $$$$$$$$ |$$  __$$\ $$  __$$\ $$ |$$ |$$  _____|\____$$\\_$$  _|  $$ |$$  __$$\ $$  __$$\ 
$$$$$$$$$$\        \____$$\ $$$$$$$$ |$$ /      $$ |  $$ |$$ |  \__|$$$$$$$$ |      $$ |      $$ |  $$ | $$$$$$$ | $$ |          $$  __$$ |$$ /  $$ |$$ /  $$ |$$ |$$ |$$ /      $$$$$$$ | $$ |    $$ |$$ /  $$ |$$ |  $$ |
\_$$  $$  _|      $$\   $$ |$$   ____|$$ |      $$ |  $$ |$$ |      $$   ____|      $$ |  $$\ $$ |  $$ |$$  __$$ | $$ |$$\       $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |$$ |$$ |     $$  __$$ | $$ |$$\ $$ |$$ |  $$ |$$ |  $$ |
  $$ |$$ |        \$$$$$$  |\$$$$$$$\ \$$$$$$$\ \$$$$$$  |$$ |      \$$$$$$$\       \$$$$$$  |$$ |  $$ |\$$$$$$$ | \$$$$  |      $$ |  $$ |$$$$$$$  |$$$$$$$  |$$ |$$ |\$$$$$$$\\$$$$$$$ | \$$$$  |$$ |\$$$$$$  |$$ |  $$ |
  \__|\__|         \______/  \_______| \_______| \______/ \__|       \_______|       \______/ \__|  \__| \_______|  \____/       \__|  \__|$$  ____/ $$  ____/ \__|\__| \_______|\_______|  \____/ \__| \______/ \__|  \__|
                                                                                                                                           $$ |      $$ |                                                                  
                                                                                                                                           $$ |      $$ |                                                                  
                                                                                                                                           \__|      \__|                                                                  

This is a secure chat application developed to provide confidentiality and integrity of user communications. The application employs encryption techniques, secure user authentication, and end-to-end encryption to ensure that messages are securely transmitted and can only be decrypted by the intended recipient. Additionally, the application provides a user-friendly interface for seamless communication.


## Features

- User signup and login functionality
- End-to-end encryption of messages using the Caesar cipher
- Secure communication over TCP/IP sockets
- User-friendly interface for sending and receiving messages
- Multi-threaded server for handling multiple clients

1. Compile the source code:
g++ serverneww.cpp -o server
g++ clientneww.cpp -o client 

2. Run the server:
./server 

3. Run the client:
   ./client


   ## Usage
   
1. Upon running the client, you will be prompted to signup or login.
2. If you're a new user, choose signup and follow the prompts to create an account.
3. If you're an existing user, choose login and enter your credentials.
4. Once logged in, you can send messages to other users who are logged in.
