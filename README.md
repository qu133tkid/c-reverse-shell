# Remote Access Tool Implementation:

This repository contains the source code for a basic Remote Access Tool (RAT) implemented in C. The RAT consists of two main components: a client-side program (socket.c) and a server-side program (server.c). It enables remote command execution on a target system over a network connection.

## Features:

  * Client-Server Architecture: Utilizes TCP sockets for communication between the client and server.
  * Command Execution: Allows the server to execute commands on the client system remotely.
  * Persistence: Implements a persistence mechanism to ensure the client program runs on system startup.
  * Keylogging: Provides basic keylogging functionality on the client system.

## Files:

* socket.c: Client-side program written in C for Windows platforms. It establishes a connection with the server, handles command execution, and implements persistence and keylogging functionalities.
* server.c: Server-side program written in C for Unix-like systems. It listens for incoming connections from clients, receives commands from the client, and executes them.
* keys.h: Header file containing the keylogging functionality used by the client program (socket.c). It captures keystrokes and stores them in a log file.

## Usage:

 - Compilation:
    * Compile socket.c for Windows using a suitable compiler (e.g., Visual Studio).
    * Compile server.c for Unix-like systems using GCC or another compatible compiler.

 - Execution:
    * Run the compiled socket executable on the client system.
    * Run the compiled server executable on the server system.

## Commands:

  - The server can send various commands to the client, including:
     * `cd <directory>`: Change directory on the client system.
     * `persist`: Establish persistence on the client system.
     * `keylog_start`: Start keylogging on the client system.

## Disclaimer:

This repository is for educational and research purposes only. The use of the code provided in this repository for any malicious or unauthorized activities is prohibited. I do not bear any responsibility for the misuse of the software.
