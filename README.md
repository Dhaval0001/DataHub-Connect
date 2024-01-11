# DataHub-Connect
C-based academic project for Unix. Robust Client-Server-Mirror Architecture for seamless file transfer. Smart load balancing for optimal performance. Server as hub and balancer routes requests intelligently for efficient handling.

Description: 
This project implements a client-server model where a client can request a file or a set of files from the server. The server searches for the files in its directory rooted at ~ and returns the files or a message if they are not found. The project involves a server, a mirror server, and multiple clients, all communicating through sockets.

Setup
Requirements
Three separate machines/terminals for the server, mirror, and client processes.
Running the Project
Start the Server and Mirror:

Run the server and its identical copy, the mirror, on two different machines. They must both be running before any client is started.
Connect the Clients:

Multiple clients can connect to the server from different machines.
The first 4 client connections are handled by the server.
The next 4 connections are handled by the mirror.
Subsequent connections are handled in an alternating manner between the server and the mirror.
Usage
Client Commands
Request File by Name (getfn):

getfn filename - The server returns details of the file if found.
Example: Client$ getfs sample.txt
Request Files by Size Range (getfz):

getfz size1 size2 - The server returns a compressed file containing all files within the specified size range.
Example: Client$ getfz 1240 12450
Request Files by File Type (getft):

getft <extension list> - The server returns a compressed file containing all files of the specified types (up to 3 types).
Example: Client$ getft c txt
Request Files by Creation Date Before a Certain Date (getfdb):

getfdb date - The server returns a compressed file containing all files created on or before the specified date.
Example: Client$ getfdb 2023-01-01
Request Files by Creation Date After a Certain Date (getfda):

getfda date - The server returns a compressed file containing all files created on or after the specified date.
Example: Client$ getfda 2023-03-31
Terminate Client Connection (quitc):

quitc - This command is sent to the server, and the client process is terminated.
Notes
All files returned from the server must be stored in a folder named f23project in the home directory of the client.
