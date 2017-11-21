/* ======================================================================
	Socket Programming-1
   This progam is for creating a server socket. The server socket
       (a) is created with a socket() call
       (b) is bound with an IP address and Port
       (c) listens for connections with a listen() call 
       (d) accepts a connection with a accept() call
       (e) sends data with send() call and 
       (f) finshes its life with a close() call.
	---------------------------------------------------------------------- 
    *** htons(Port_No) is for converting HBO to NBO where
        ----> HBO: Host-Byte-Order
        ----> NBO: Network-Byte-Order
        Byte Order: Big Indian & Little Indian
	---------------------------------------------------------------------- 
    Necessary System Calls:
       1. socket(domain, type, protocol)
       2. bind()
       3. listen() 
       4. send()
       5. recv()
       6. close()         
   ---------------------------------------------------------------------- 
    Sangeeta Biswas
    Assistant Professor,
    Dept. of CSE, University of Rajshahi,
    Rajshahi-6205, Bangladesh
   ---------------------------------------------------------------------- 
    29/8/2017
	======================================================================
*/

#include <sys/socket.h> 	
#include <netinet/in.h>
#include <unistd.h> 
#include<stdio.h>		

int main() {
    // Create a socket
     int server_socket;
     int buf_size;
     int test = 1;
     server_socket = socket(AF_INET, SOCK_STREAM, 0);
     if(server_socket==-1)
     {
        perror("Failed to create server");
        return 1;
      }

    // Define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind the above socket to the specified IP and port
    int addr_len;
    struct sockaddr *sockaddr_ptr;
    addr_len = sizeof(server_address);
    sockaddr_ptr = (struct sockaddr *)&server_address;
    int bind_ = bind(server_socket, sockaddr_ptr, addr_len);
    if(bind_ == -1)
    {
       perror("Failed to bind server");
       return 1;
     }
        

   

    // Listen
    int listener_ = listen(server_socket, 5);
  

    // Accept
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);
    
   
     
      while(1){

        if(test)
          {
              char server_message[256] =  "Welcome, connection has been stablished\n";
              int msg_size_;
              msg_size_ = sizeof(server_message);
              int sent = send(client_socket, server_message, msg_size_, 0);

              char server_response[256];
              buf_size = sizeof(server_response);
              int msg_size;
              msg_size = sizeof(server_message);
              int rec = recv(client_socket, &server_response, buf_size, 0);
              printf("Client:%s",server_response);
              printf("\n");

              test = test -1; 
                  
           }else{

             char server_message[256] ;
             char message[256];
             printf("Server's turn: ");
             gets(message);
             int msg_size_;
             strcpy(server_message,message);
             msg_size_ = sizeof(server_message);
             int sent = send(client_socket, server_message, msg_size_, 0);
             

             char server_response[256];
             buf_size = sizeof(server_response);
             int msg_size;
             msg_size = sizeof(server_message);
             int rec = recv(client_socket, &server_response, buf_size, 0);

             printf("Message from the client:%s",server_response);
             printf("\n");
          }


    }
  close(server_socket);

}
