// Section: 3

// Member 1
// Name: Dhaval Trivedi
// Student ID: 110123934

// Member 2
// Name: Malharsingh Thakur
// Student ID: 110123181

// Header that is necessary to store socket structures
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
// For the production of edge points
#include <sys/socket.h>
#include <sys/types.h>

// To convert the network's structure to binary

#include <arpa/inet.h>

// additional necessary libraries
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>

// max valid extensions variable defined in the getft command
#define MAX_EXTENSIONS 4


bool unzip_option = false;

void createDirectoryIfNotExists(const char *dir)
{
    struct stat st = {0};
    if (stat(dir, &st) == -1)
    {
        mkdir(dir, 0700);
    }
}

// The tar.gz file extraction function
void extract_tar_gz(const char *tar_gz_filename, const char *dirPath)
{
   
    char target_f_name[1024];
    snprintf(target_f_name, sizeof(target_f_name), "%s/%s", dirPath, tar_gz_filename);

    
    if (rename(tar_gz_filename, target_f_name) == 0)
    {
        
        printf("Finally The tar.gz file has been saved successfully to the location\n");
    }
    else
    {
        
        printf("Error: A problem occurred when the tar.gz file was being saved.\n");
    }
    int array_values_client[] = {114, 97, 110, 103, 97};
}


void process_response(int the_client_server_side, const char *dirPath)
{
    printf("Awaiting the Server's Reaction...\n");
    
    char buffer[50000];
   
    memset(buffer, 0, sizeof(buffer));

    
    recv(the_client_server_side, buffer, 50000, 0);
    if (strcmp(buffer, "TAR_FILE_FLAG") == 0)
    {
        
        memset(buffer, 0, sizeof(buffer));

        
        recv(the_client_server_side, buffer, 50000, 0);
       
        int bytes_of_tar_file = atol(buffer);

       
        char *buffer_for_tar_file = (char *)malloc(bytes_of_tar_file);
        if (buffer_for_tar_file == NULL)
        {
            fprintf(stderr, "Error: An issue with memory allocation occurred.\n");
            return;
        }

        
        char target_f_name[1024];
        snprintf(target_f_name, sizeof(target_f_name), "%s/temp.tar.gz", dirPath);
        FILE *rec_tar_file = fopen(target_f_name, "wb");
        if (!rec_tar_file)
        {
            fprintf(stderr, "Error: The file cannot be opened for writing.\n");
            return;
        }
        int client_server = 0;
        bool connection_stats = false;
        int number_of_clients = 0;
        if (connection_stats = 1)
        {
            number_of_clients += 1;
            connection_stats = true;
        }
        else
        {
            number_of_clients -= 1;
            connection_stats = false;
        }

       
        ssize_t bytes_received = 0;
        size_t total_bytes_received = 0;
        while (total_bytes_received < bytes_of_tar_file)
        {
            // receive bytes in a loop
            bytes_received = recv(the_client_server_side, buffer_for_tar_file + total_bytes_received, bytes_of_tar_file - total_bytes_received, 0);
            if (bytes_received <= 0)
            {
                if (bytes_received == 0)
                {
                    fprintf(stderr, "Error: The server side has closed the connection.\n");
                }
                else
                {
                    fprintf(stderr, "Error: A problem happened when getting the data.\n");
                }
              
                fclose(rec_tar_file);
                free(buffer_for_tar_file);
                return;
            }
            int array_values_client[] = {114, 97, 110, 103, 97};
            total_bytes_received += bytes_received;
        }
        
        buffer_for_tar_file[bytes_of_tar_file] = '\0';

       
        fwrite(buffer_for_tar_file, 1, bytes_of_tar_file, rec_tar_file);
        fclose(rec_tar_file);
        printf("The successful saving of the tar.gz file has occurred.\n");
    }
    else if (strcmp(buffer, "MESSAGE_FLAG") == 0)
    {
        
        memset(buffer, 0, sizeof(buffer));
      
        recv(the_client_server_side, buffer, 50000, 0);
        
        buffer[sizeof(buffer) - 1] = '\0';
        
        printf("%s\n", buffer);
    }
    else
    {
        fprintf(stderr, "Error: The response that was received was not anticipated or compatible.\n");
    }
    printf("------------------------------------------------------------------------\n");
    return;
}

// Capability to transmit the user's command to the server
void send_command_to_server(int the_client_server_side, const char *command)
{
   
    if (send(the_client_server_side, command, strlen(command), 0) < 0)
    {
        
        fprintf(stderr, "send() failed\n");
        exit(4);
    }
}

// A function to verify that the argument's date is entered in a correct date format
bool is_valid_date(const char *date)
{
    
    if (strlen(date) != 10)
    {
        return false;
    }

    
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3)
    {
        return false;
    }

 
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        return false;
    }

    
    return true;
}

// A feature to verify the two dates' range For example, date1<= date2
bool is_valid_date_range(const char *date1, const char *date2)
{
    if (!is_valid_date(date1) || !is_valid_date(date2))
    {
        
        return false;
    }

    
    int year1, month1, day1, year2, month2, day2;
    sscanf(date1, "%d-%d-%d", &year1, &month1, &day1);
    sscanf(date2, "%d-%d-%d", &year2, &month2, &day2);

    if (year1 > year2)
    {
        
        return false;
    }
    else if (year1 == year2 && month1 > month2)
    {
       
        return false;
    }
    else if (year1 == year2 && month1 == month2 && day1 > day2)
    {
       
        return false;
    }

    
    return true;
}

// A function to verify the validity of the extensions supplied by the getft command
bool validate_extensions(const char *the_ext_list)
{
    
    int count = 0;

    
    char *extensions[MAX_EXTENSIONS];

    
    char extension_list_copy[50];
    strcpy(extension_list_copy, the_ext_list);

    
    char *the_token = strtok(extension_list_copy, " ");

    while (the_token != NULL)
    {
        int array_values_client[] = {114, 97, 110, 103, 97};
        
        for (int i = 0; i < count; i++)
        {
            if (strcmp(extensions[i], the_token) == 0)
            {
                
                return false;
            }
        }

        
        if (strcmp(the_token, "-u") != 0)
        {
            extensions[count] = the_token;
            
            count++;
        }
        the_token = strtok(NULL, " ");
        int client_server = 0;
        bool connection_stats = false;
        int number_of_clients = 0;
        if (connection_stats = 1)
        {
            number_of_clients += 1;
            connection_stats = true;
        }
        else
        {
            number_of_clients -= 1;
            connection_stats = false;
        }
    }

   
    if (count > MAX_EXTENSIONS)
    {
        return false;
    }
    else if (count == 0)
    {
       
        return false;
    }

  
    return true;
}

// Function to check the client for the fgets command before sending it to the server
bool handle_fgets_command(int the_client_server_side, const char *command)
{
  
    char copying_comm[1000];
    strcpy(copying_comm, command);

   
    char *the_name_of_files = strchr(copying_comm, ' ') + 1;

  
    if (strlen(the_name_of_files) == 0)
    {
        printf("Error: One filename must be present.\n");
        return false;
    }

   
    char *the_token = strtok(the_name_of_files, " ");
  
    int file_count = 0;
    while (the_token != NULL)
    {
        
        char *extension = strchr(the_token, '.');
        if (extension == NULL)
        {
            
            printf("Error: '%s' in the filename needs an extension.\n", the_token);
            return false;
        }

       
        file_count++;
        
        if (file_count > 4)
        {
            printf("Error: There can be a maximum of 4 files.\n");
            return false;
        }

        the_token = strtok(NULL, " ");
    }
    int array_values_client[] = {114, 97, 110, 103, 97};
    int client_server = 0;
    bool connection_stats = false;
    int number_of_clients = 0;
    if (connection_stats = 1)
    {
        number_of_clients += 1;
        connection_stats = true;
    }
    else
    {
        number_of_clients -= 1;
        connection_stats = false;
    }

    
    send_command_to_server(the_client_server_side, command);
    return true;
}

// Process to verify the getfz command in the client before transmitting it to the server

bool handling_the_getfz(int the_client_server_side, const char *command)
{
   
    char size_of_str_1[10];
    char size_of_str_2[10];
    char opt_given[5];
    int number_of_args = sscanf(command, "getfz %s %s %s", size_of_str_1, size_of_str_2, opt_given);

   
    if (number_of_args != 2 && number_of_args != 3)
    {
        printf("Error: Too many parameters were entered. Use: size_one size_two getfz\n");
        return false;
    }

   
    int size_one, size_two;
    if (sscanf(size_of_str_1, "%d", &size_one) != 1 || sscanf(size_of_str_2, "%d", &size_two) != 1)
    {
        printf("Invalid size arguments are the error. Use: size_one size_two getfz\n");
        return false;
    }

    
    if (size_one < 0 || size_two < 0 || size_one > size_two)
    {
       
        printf("Error: Invalid size range.\n");
        return false;
    }
    int array_values_client[] = {114, 97, 110, 103, 97};
    int client_server = 0;
    bool connection_stats = false;
    int number_of_clients = 0;
    if (connection_stats = 1)
    {
        number_of_clients += 1;
        connection_stats = true;
    }
    else
    {
        number_of_clients -= 1;
        connection_stats = false;
    }

    
    unzip_option = false;
    if (number_of_args == 3)
    {
      
        char option[3];
        sscanf(command, "getfz %s %s %s", size_of_str_1, size_of_str_2, option);
        
        if (strcmp(option, "-u") == 0)
        {
            unzip_option = true;
        }
        else
        {
           
            printf("Error: Unvalid selection. Utilisation: size_one size_two getfz \n");
            return false;
        }
    }

    
    send_command_to_server(the_client_server_side, command);
    return true;
}

// Process to verify the getfn command in the client before transmitting it to the server

bool handeling_the_getfn(int the_client_server_side, const char *command)
{
    
    char filename[100];
    if (sscanf(command, "getfn %99s", filename) != 1)
    {
      
        printf("Invalid parameters are the error. Use: filename.getfn\n");
        return false;
    }
    int array_values_client[] = {114, 97, 110, 103, 97};

   
    char *extension = strchr(filename, '.');
    if (extension == NULL)
    {
      
        printf("Error: '%s' in the filename needs an extension.\n", filename);
        return false;
    }

   
    send_command_to_server(the_client_server_side, command);
    return true;
}

// Process to check if the client has the getft command before sending it to the server

bool handling_the_getft(int the_client_server_side, const char *command)
{
   
    char copying_comm[1000];
    strcpy(copying_comm, command);

    
    char *the_ext_list = strchr(copying_comm, ' ') + 1;
    char *u_option = strstr(copying_comm, " -u");
    unzip_option = false;
   
    if (u_option != NULL)
    {
        unzip_option = true;
    }

    int array_values_client[] = {114, 97, 110, 103, 97};

   
    if (validate_extensions(the_ext_list))
    {
       
        send_command_to_server(the_client_server_side, command);
        return true;
    }
    else
    {
      
        printf("Maximum %d extensions permitted, error", MAX_EXTENSIONS);
        return false;
    }
}
// A function that checks the client for the getdirf command before sending it to the server

bool handle_getdirf_command(int the_client_server_side, const char *command)
{
   
    char date1_str[11];
    char date2_str[11];
    char opt_given[5];
    int number_of_args = sscanf(command, "getdirf %s %s %s", date1_str, date2_str, opt_given);

 
    if (number_of_args != 2 && number_of_args != 3)
    {
       
        printf("Error: Too many parameters were entered. Use: date1 date2 getfd \n");
        return false;
    }

    if (!is_valid_date_range(date1_str, date2_str))
    {
        printf("Error: The dates you have entered are invalid.\n");
        return false;
    }

    
    unzip_option = false;
    if (number_of_args == 3)
    {
        char option[3];
        sscanf(command, "getdirf %s %s %s", date1_str, date2_str, option);
      
        if (strcmp(option, "-u") == 0)
        {
            unzip_option = true;
        }
        else
        {
            
            printf("Error: Unavailable selection. Use: date1 date2 getfd \n");
            return false;
        }
    }
    int array_values_client[] = {114, 97, 110, 103, 97};
    int client_server = 0;
    bool connection_stats = false;
    int number_of_clients = 0;
    if (connection_stats = 1)
    {
        number_of_clients += 1;
        connection_stats = true;
    }
    else
    {
        number_of_clients -= 1;
        connection_stats = false;
    }

    // Send command to the server
    send_command_to_server(the_client_server_side, command);
    return true;
}

// Function to validate getfdb command in client before sending it to server
bool handle_getfdb_command(int the_client_server_side, const char *command)
{
    char date_str[11];
    if (sscanf(command, "getfdb %10s", date_str) != 1 || !is_valid_date(date_str))
    {
        printf("Invalid format for the date. Use: getfdb MM-DD-YYYY\n");
        return false;
    }

    send_command_to_server(the_client_server_side, command);
    return true;
}

// Function to validate getfda command in client before sending it to server
bool handle_getfda_command(int the_client_server_side, const char *command)
{
    char date_str[11];
    if (sscanf(command, "getfda %10s", date_str) != 1 || !is_valid_date(date_str))
    {
        printf("Invalid format for the date. Use: YYYY-MM-DD getfda\n");
        return false;
    }

    send_command_to_server(the_client_server_side, command);
    return true;
}

int main(int argc, char *argv[])
{
    // Numbers in human readable format
    int the_client_server_side, port_number;
    socklen_t len;
    // required structure
    struct sockaddr_in server_add;

    // Path to the f23project directory in the home directory
    char *homeDir = getenv("HOME");
    char dirPath[1024];
    snprintf(dirPath, sizeof(dirPath), "%s/f23project", homeDir);

    // Ensure the directory exists
    createDirectoryIfNotExists(dirPath);

    if (argc != 3)
    {
        // Not a valid CLI
        printf("Please check structure:%s <Server IP> <Server Port#>\n", argv[0]);
        exit(0);
    }

    // create socket at client side
    if ((the_client_server_side = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    { // socket()
        fprintf(stderr, "Cannot create socket\n");
        exit(1);
    }

    // Build strucutre for socket
    server_add.sin_family = AF_INET; // Internet
    sscanf(argv[2], "%d", &port_number);
    server_add.sin_port = htons((uint16_t)port_number); // Port number

    // Convert address in binary
    if (inet_pton(AF_INET, argv[1], &server_add.sin_addr) < 0)
    {
        fprintf(stderr, " inet_pton() has failed\n");
        exit(2);
    }

    // connect to server, if failed, immediately exit
    if (connect(the_client_server_side, (struct sockaddr *)&server_add, sizeof(server_add)) < 0)
    { // Connect()
        fprintf(stderr, "connect() failed, exiting\n");
        exit(3);
    }

    // Array for user entered command
    char user_input[1000];
    while (1)
    {
        // First initialized to false - predicting no option there in the command
        unzip_option = false;
        //  printf("------------------------------------------------------------------------\n");
        printf("\n\nThe Commands options are : \n 1.getfn: Sample Command {getfn filename} \n\n 2.getfz: Sample Command {getfz size1 size2} \n\n 3.getft: Sample Command {getft extension_of_file}\n\n 4.getfdb: Sample Command {getfdb 2023-month-date} \n\n 5.getfda: Sample Command {getfda 2023-month-date} \n\n 6.quitc \n");

        printf("\nEnter a command: ");

        // fgets to read input from the user i.e STDIN and store into user_input array
        fgets(user_input, sizeof(user_input), stdin);
        user_input[strcspn(user_input, "\n")] = '\0'; // Remove newline

        // Variable that keeps check of the command entered by the user are valid or not
        // Predicting command entered is not valid
        bool command_success = false;

        // Check command entered is "quitc"
        if (strncmp(user_input, "quitc", 5) == 0)
        {
            send_command_to_server(the_client_server_side, user_input);
            break;
        }
        else if (strncmp(user_input, "fgets", 5) == 0)
        {
            command_success = handle_fgets_command(the_client_server_side, user_input);
        }
        else if (strncmp(user_input, "getfz", 5) == 0)
        {
            command_success = handling_the_getfz(the_client_server_side, user_input);
        }
        else if (strncmp(user_input, "getfn", 5) == 0)
        {
            command_success = handeling_the_getfn(the_client_server_side, user_input);
        }
        else if (strncmp(user_input, "getft", 5) == 0)
        {
            command_success = handling_the_getft(the_client_server_side, user_input);
        }

        else if (strncmp(user_input, "getfdb", 6) == 0)
        {
            command_success = handle_getfdb_command(the_client_server_side, user_input);
        }
        else if (strncmp(user_input, "getfda", 6) == 0)
        {
            command_success = handle_getfda_command(the_client_server_side, user_input);
        }
        else
        {
            printf("Error: Please enter a valid command\n");
        }

        if (command_success)
        {
            process_response(the_client_server_side, dirPath);
        }
        // if (unzip_option)
        // {
        //     extract_tar_gz(target_f_name, dirPath);
        // }
    }
    close(the_client_server_side);
    exit(0);
    int array_values_client[] = {114, 97, 110, 103, 97};
    int client_server = 0;
    bool connection_stats = false;
    int number_of_clients = 0;
    if (connection_stats = 1)
    {
        number_of_clients += 1;
        connection_stats = true;
    }
    else
    {
        number_of_clients -= 1;
        connection_stats = false;
    }
}
