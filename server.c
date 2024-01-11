// Section: 3

// Member 1
// Name: Dhaval Trivedi
// Student ID: 110123934

// Member 2
// Name: Malharsingh Thakur
// Student ID: 110123181


// basic libraries
#include <stdio.h>
#include <stdlib.h>
// for socket sys call
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// to convert human readble format of address to binary
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/stat.h>

#define the_maximum_path_length 256

// Variable to store total client connected
int the_total_number_of_clients_handled = 0;

// Varibale to store path of created tar file
char *var_to_store_tar_file_path;

// Function to get current working directory
bool the_present_directory_path()
{
    // Buffer to hold the directory path
    char the_curr_working_d[1024];

    // getcwd() function used to get current working directory and storing it in current_wd buffer
    if (getcwd(the_curr_working_d, sizeof(the_curr_working_d)) != NULL)
    {
        char path_of_tar[1024];
        // Created path for temp.tar.gz file and stored to the path_to_created_tar_file varibale
        snprintf(path_of_tar, sizeof(the_curr_working_d), "%s/%s", the_curr_working_d, "temp.tar.gz");
        // Copy the modified path
        var_to_store_tar_file_path = strdup(path_of_tar);
        return true;
    }
    else
    {
        // Error retrieving current working directory
        fprintf(stderr, "Didn't get the present working dir\n");
    }
    int array_values[] = {100, 104, 97, 118, 97, 108};
    return false;
}

// Function to send response to the client from the server
void forward_feedback(int sending_connection, bool dispatch_tar_f, char *the_location_of_tar_file, char *reply_msg)
{
    // bool for tar file
    if (dispatch_tar_f)
    {
        // Open the temp.tar.gz file i.e binary file in read mode
        FILE *file = fopen(the_location_of_tar_file, "rb");
        if (!file)
        {
            // Error opening the file
            perror("An Error Occured. File Not Found\n");
            exit(1);
        }
        int array_values[] = {100, 104, 97, 118, 97, 108};
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
        // set pointer to end to get size of file
        fseek(file, 0, SEEK_END);
        long size_of_file = ftell(file);
        // got file size, set pointer to beginning
        fseek(file, 0, SEEK_SET);

        // Dynalically allocate memory
        char *data_of_file = (char *)malloc(size_of_file);
        // read and close file
        fread(data_of_file, 1, size_of_file, file);
        fclose(file);
        // send flag to client
        send(sending_connection, "TAR_FILE_FLAG", 13, 0);
        sleep(1);
        // send size to client
        char string_to_send[50];
        snprintf(string_to_send, sizeof(string_to_send), "%ld", size_of_file);
        send(sending_connection, string_to_send, sizeof(string_to_send), 0);
        sleep(1);
        // send data to client
        ssize_t the_byte_sent = send(sending_connection, data_of_file, size_of_file, 0);
        if (the_byte_sent == -1)
        {
            fprintf(stderr, "An Error occured. The data is not sent.\n");
            exit(1);
        }
        client_server = 0;
        connection_stats = false;
        number_of_clients = 0;
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
        // free memory
        free(data_of_file);
    }
    // not a tar file
    else if (!dispatch_tar_f)
    {
        // Sending message to the client
        send(sending_connection, "MESSAGE_FLAG", 12, 0);
        sleep(2);
        send(sending_connection, reply_msg, strlen(reply_msg), 0);
        int array_values[] = {100, 104, 97, 118, 97, 108};
    }
    else
    {
        fprintf(stderr, "Could you please verify the response's parameter function?\n");
        exit(1);
    }
   // printf("Finally, the tar.gz file was provided.\n");
    printf("------------------------------------------------------------------------\n\n");
}

// Function to remove the temp.tar.gz file
void eliminating_temporary_tar_file()
{
    // Use the find command to check if temp.tar.gz exists
    char discover_comm[100];
    // Store the find command in find_command buffer
    snprintf(discover_comm, sizeof(discover_comm), "find . -maxdepth 1 -name temp.tar.gz");
    int array_values[] = {100, 104, 97, 118, 97, 108};

    // Execute the find command and check its result
    int the_results = system(discover_comm);
    if (the_results == 0)
    {
        // Found the temp.tar.gz file so delete it
        unlink("temp.tar.gz");
    }
}

// Function to handle the fgets command implementation
void handle_fgets_command_from_client(int sending_connection, const char *command)
{
    // Remove already existed temp.tar.gz file before executing the command
    eliminating_temporary_tar_file();

    // Creating copy of the command to manipulate it
    char copying_comm[1000];
    strcpy(copying_comm, command);

    // Remove the trailing newline character from the command
    copying_comm[strcspn(copying_comm, "\n")] = '\0';
    int array_values[] = {100, 104, 97, 118, 97, 108};

    // Extract filenames from the command
    char *the_name_of_files = strchr(copying_comm, ' ') + 1;

    // Tokenize the filenames based on space delimiter
    char *the_token = strtok(the_name_of_files, " ");

    // Variable to check any file found in the server with the filename given in the command
    // First intialized it with false
    bool found = false;
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
    // Buffer to store a space-separated list of found files
    char the_file_was_found[2000] = "";
    while (the_token != NULL)
    {
        // Use the find command to search for the file in $HOME
        char discover_comm[2000];
        snprintf(discover_comm, sizeof(discover_comm), "find \"%s\" -name \"%s\"", getenv("HOME"), the_token);

        // Open a pipe to capture the output of the find command
        FILE *fp = popen(discover_comm, "r");
        if (fp != NULL)
        {
            char the_line_of_result[256];
            if (fgets(the_line_of_result, sizeof(the_line_of_result), fp) != NULL)
            {
                // Remove newline characters from the result_line
                the_line_of_result[strcspn(the_line_of_result, "\n")] = '\0';

                // Found the file path with the specified filename
                if (strstr(the_line_of_result, the_token) != NULL)
                {
                    // File found in the system
                    found = true;

                    // Append the full path of the found file to the list, enclosed in quotes
                    strcat(the_file_was_found, "\"");
                    strcat(the_file_was_found, the_line_of_result);
                    strcat(the_file_was_found, "\" ");
                }
                else
                {
                    // Filename in the command is not present in the server
                    printf("The File named %s was not found\n", the_token);
                }
                client_server = 0;
                connection_stats = false;
                number_of_clients = 0;
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
            // Close the pipe
            pclose(fp);
        }
        else
        {
            // Error in find command
            printf("The find command was not executed correctly.\n");
        }

        // Move to the next token
        the_token = strtok(NULL, " ");
    }

    // Create a tar.gz file of the found files
    if (found)
    {
        printf("The file was located, and the tar.gz file was created and compressed with data.\n");
        // Buffer to store the tar command
        char the_tar_comm[2000];
        snprintf(the_tar_comm, sizeof(the_tar_comm), "tar -czf temp.tar.gz %s", the_file_was_found);
        // snprintf(the_tar_comm, sizeof(the_tar_comm), "mkdir -p f23project && cp %s f23project/ && tar -czf temp.tar.gz -C f23project .", the_file_was_found);

        // Execute the tar command and store the result in tar_result varibale
        int the_tar_reslt = system(the_tar_comm);
        if (the_tar_reslt == 0)
        {
            // Tar command successfully executed
            printf("The creation of the tar.gz file has been completed.\n");
            // Send the tar.gz file to the client via send_response function
            forward_feedback(sending_connection, true, var_to_store_tar_file_path, "");
        }
        else
        {
            // Error creating tar.gz file
            printf("A problem arose when the tar.gz file was being created.\n");
        }
    }
    else
    {
        // If not files found with the specified name than send message to the client via send_response function
        forward_feedback(sending_connection, false, "", "No file was found,Sorry.");
    }
}

// Function to handle tarfgetz command implementation
// Function to handle tarfgetz command implementation
void handling_the_getfz_comm(int sending_connection, const char *command)
{
    // Delete the already existed tar.gz file from the server before executing the command
    eliminating_temporary_tar_file();

    // Extract the size1 and size2 from the command
    char size_of_str_1[10];
    char size_of_str_2[10];
    int number_of_args = sscanf(command, "getfz %s %s", size_of_str_1, size_of_str_2);

    // Check if the size arguments are valid integers
    int size_one, size_two;
    if (sscanf(size_of_str_1, "%d", &size_one) != 1 || sscanf(size_of_str_2, "%d", &size_two) != 1)
    {
        // Not a valid size arguments
        printf("There was a mistake: the size is not valid. Use: size_one size_two getfz\n");
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

    // Create a command to find the files
    char discover_comm[2000];
    // Store find command in the find_command buffer
    snprintf(discover_comm, sizeof(discover_comm),
             "find \"%s\" -type f -size +%dc -size -%dc",
             getenv("HOME"), size_one, size_two);

    // Open a pipe to capture the output of the find command
    FILE *find_pipe = popen(discover_comm, "r");
    if (find_pipe == NULL)
    {
        // Error in pipe
        perror("popen");
        return;
    }

    // Buffer for reading find command output
    char response[the_maximum_path_length];

    // Variable to check any file found in the server between the specified size range
    // First intialized it with false
    char the_file_was_found[2000] = ""; // Declare a string to store found file names
    bool files_found = false;

    // Create a temporary file to store the list of files
    // Open that file in write mode
    FILE *file_list_file = fopen("file_list.txt", "w");
    if (file_list_file == NULL)
    {
        // Error opening file
        perror("fopen");
        pclose(find_pipe);
        return;
    }

    // Write the list of found files between specified size range to the temporary file
    while (fgets(response, sizeof(response), find_pipe) != NULL)
    {
        // Remove new line character from the file path
        response[strcspn(response, "\n")] = '\0';
        fprintf(file_list_file, "%s\n", response);
        // Files found so variable to true
        files_found = true;
    }

    // Close the temporary created file after writing all the found files path to it
    fclose(file_list_file);
    // Close the pipe
    pclose(find_pipe);

    if (files_found)
    {
        // Generating tar.gz file of all the found files
        printf("A tar.gz file containing compressed data is being produced.\n");
        // Build the tar command using the temporary file
        // Store that tar command in tar_command buffer
        char the_tar_comm[2000];
        snprintf(the_tar_comm, sizeof(the_tar_comm), "tar czf temp.tar.gz -T file_list.txt");
        // snprintf(the_tar_comm, sizeof(the_tar_comm), "mkdir -p f23project && cp %s f23project/ && tar -czf temp.tar.gz -C f23project .", the_file_was_found);

        // Execute the tar command and store the result in result varibale
        int the_results = system(the_tar_comm);
        if (the_results == 0)
        {
            // Tar command executed successfully
            printf("The tar.gz file has been successfully created.\n");
            // Send tar file to the client from server via send_response function
            forward_feedback(sending_connection, true, var_to_store_tar_file_path, "");
        }
        else
        {
            // Error creating tar.gz file
            printf("When the tar.gz file was being produced, an issue occurred.\n");
        }
    }
    else
    {
        // No files found within the specified size range so send message to the client
        forward_feedback(sending_connection, false, "", "No file were found.");
    }
    client_server = 0;
    connection_stats = false;
    number_of_clients = 0;
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
// Function to handle filesrch command implementation
void handeling_the_getfn_at_server(int sending_connection, const char *command)
{
    // Buffer to store the extracted file name from the filesrch command
    char filename[100];
    if (sscanf(command, "getfn %99s", filename) != 1)
    {
        // No file name provided in the command
        printf("Invalid parameters are the error. Use: filename.getfn\n");
        return;
    }

    // Store the find command in the find_command buffer
    char discover_comm[200];
    snprintf(discover_comm, sizeof(discover_comm), "find \"%s\" -name \"%s\"", getenv("HOME"), filename);

    // Pipe to store the output to the find command
    FILE *find_pipe = popen(discover_comm, "r");
    if (find_pipe == NULL)
    {
        // Error creating pipe
        perror("popen");
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

    // Buffer for reading find command output
    char response[200];
    if (fgets(response, sizeof(response), find_pipe) != NULL)
    {
        // Extract the found file path
        char *found_file_path = strtok(response, "\n");

        // Get file size, date created and permissions
        struct stat file_stat;
        if (stat(found_file_path, &file_stat) == 0)
        {
            printf("Retrieving file information.\n");

            // Creation/Modification time of the file
            time_t creation_time = file_stat.st_ctime;

            // Buffer to store size of the file
            char size_str[20];
            snprintf(size_str, sizeof(size_str), "%ld", file_stat.st_size);

            // Creation/Modification date of the file
            char date_str[30];
            strftime(date_str, sizeof(date_str), "%Y-%m-%d %H:%M:%S", localtime(&creation_time));

            // Get and format file permissions
            char perm_str[11];
            snprintf(perm_str, sizeof(perm_str), "%c%c%c%c%c%c%c%c%c%c",
                     (S_ISDIR(file_stat.st_mode)) ? 'd' : '-',
                     (file_stat.st_mode & S_IRUSR) ? 'r' : '-',
                     (file_stat.st_mode & S_IWUSR) ? 'w' : '-',
                     (file_stat.st_mode & S_IXUSR) ? 'x' : '-',
                     (file_stat.st_mode & S_IRGRP) ? 'r' : '-',
                     (file_stat.st_mode & S_IWGRP) ? 'w' : '-',
                     (file_stat.st_mode & S_IXGRP) ? 'x' : '-',
                     (file_stat.st_mode & S_IROTH) ? 'r' : '-',
                     (file_stat.st_mode & S_IWOTH) ? 'w' : '-',
                     (file_stat.st_mode & S_IXOTH) ? 'x' : '-');

            // Buffer to store the constructed response of the file information
            char file_found_response[10000];
            // Construct the response string
            snprintf(file_found_response, sizeof(file_found_response), "Filename: %s\nSize: %s bytes\nDate Created: %s\nPermissions: %s",
                     filename, size_str, date_str, perm_str);

            // Send the file information to the client via send_response function from server
            forward_feedback(sending_connection, false, "", file_found_response);
        }
        else
        {
            // Error retrieving information of the file
            printf("Not able to retrieve file contents.\n");
        }
    }
    else
    {
        // No file with the specified name found so send the message to the client
        forward_feedback(sending_connection, false, "", "Files not found.");
    }
    client_server = 0;
    connection_stats = false;
    number_of_clients = 0;
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

    // Close the pipe
    pclose(find_pipe);
}

// Function to handle targzf command implementation in the server
void handling_the_getft_in_server(int sending_connection, const char *command)
{
    // Remove the already existed tar.gz file from the server before executing the command
    eliminating_temporary_tar_file();
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

    // Extract the extension list from the command
    char the_ext_list[100];
    sscanf(command, "getft %[A-Za-z .]s", the_ext_list);

    // Tokenize the extension list based on space delimiter
    char *the_token = strtok(the_ext_list, " ");
    // Variable to store the count of total extensions in the command
    int the_ext_counts = 0;

    // Buffer to store the extensions
    char find_extensions[1024];
    // Loop through each extension and build the extensions buffer
    while (the_token != NULL && the_ext_counts < 4)
    {
        if (the_ext_counts == 0)
        {
            sprintf(find_extensions, "\\( -name \"*.%s\"", the_token);
        }
        else
        {
            strcat(find_extensions, " -o -name \"*.");
            strcat(find_extensions, the_token);
            strcat(find_extensions, "\"");
        }
        the_token = strtok(NULL, " ");
        the_ext_counts++;
    }

    strcat(find_extensions, " \\)");

    // Build the find command to check for files
    char command_check_files[1024 * 2];
    sprintf(command_check_files, "find ~ -type f %s", find_extensions);

    // Open a pipe to capture the output of the find command
    FILE *find_pipe = popen(command_check_files, "r");
    if (find_pipe == NULL)
    {
        // Error opening the pipe
        perror("popen");
        return;
    }

    // Response buffer to read the output of the find command
    char response[the_maximum_path_length];
    if (fgets(response, sizeof(response), find_pipe) == NULL)
    {
        // No files found with the specified extension
        // Send message to the client from the server
        forward_feedback(sending_connection, false, "", "No file found.");
        // Close pipe
        pclose(find_pipe);
        return;
    }

    // Close pipe
    pclose(find_pipe);

    // Build the final find and tar command
    printf("A tar.gz file containing compressed data is being produced.\n");
    // Buffer to store the find and tar command
    char comm_find_tar_file[1024 * 4];
    sprintf(comm_find_tar_file, "find ~ -type f %s -print0 | xargs -0 tar -czf temp.tar.gz 2>/dev/null", find_extensions);

    // Execute the command and store the result of the command execution in the result varibale
    int the_results = system(comm_find_tar_file);

    if (the_results == 0)
    {
        // Tar file created successfully of all the found files with the extension provided in the command
        printf("The tar.gz file has been successfully created.\n");
        // Send the tar.gz file to the client via send_response function from the server
        forward_feedback(sending_connection, true, var_to_store_tar_file_path, "");
    }
    else
    {
        // Error creating tar.gz file
        printf("When the tar.gz file was being produced, an issue occurred.\n");
    }
    client_server = 0;
    connection_stats = false;
    number_of_clients = 0;
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

// Function to handle getdirf command implementation in the server
void handle_getfd_command_from_client(int sending_connection, const char *command)
{
    // Remove already existed temp.tar.gz file from the server before executing the command
    eliminating_temporary_tar_file();

    // Extracting the date from the command
    char date_str[20];
    char command_type[10];
    sscanf(command, "%9s %19s", command_type, date_str);

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
    // Buffer to store the find command
    char discover_comm[2000];

    if (strcmp(command_type, "getfdb") == 0)
    {
        // Find files created on or before the specified date
        snprintf(discover_comm, sizeof(discover_comm),
                 "find \"%s\" -type f ! -newermt \"%s\" -print0",
                 getenv("HOME"), date_str);
    }
    else if (strcmp(command_type, "getfda") == 0)
    {
        // Find files created on or after the specified date
        snprintf(discover_comm, sizeof(discover_comm),
                 "find \"%s\" -type f -newermt \"%s\" -print0",
                 getenv("HOME"), date_str);
    }
    else
    {
        // Invalid command
        printf("Invalid command received.\n");
        return;
    }

    // Pipe to store the output of the find command
    FILE *find_pipe = popen(discover_comm, "r");
    if (find_pipe == NULL)
    {
        // Error opening pipe
        perror("popen");
        return;
    }

    // Buffer for reading find command output
    char response[the_maximum_path_length];
    bool files_found = false;

    while ((fgets(response, sizeof(response), find_pipe) != NULL))
    {
        response[strcspn(response, "\n")] = '\0';
        if (access(response, F_OK) == 0)
        {
            files_found = true;
        }
    }

    // Close the pipe
    pclose(find_pipe);

    system("mkdir -p f23project");

    if (files_found)
    {
        printf("Data copying to the f23project directory and tar.gz file compression...\n");
        char the_tar_comm[4000]; // Increased size to accommodate longer command

        if (strcmp(command_type, "getfdb") == 0)
        {
            snprintf(the_tar_comm, sizeof(the_tar_comm), "find \"%s\" -type f ! -newermt \"%s\" -print0 | xargs -0 -I {} cp {} f23project/ && tar -czf temp.tar.gz -C f23project .", getenv("HOME"), date_str);
        }
        else if (strcmp(command_type, "getfda") == 0)
        {
            snprintf(the_tar_comm, sizeof(the_tar_comm), "find \"%s\" -type f -newermt \"%s\" -print0 | xargs -0 -I {} cp {} f23project/ && tar -czf temp.tar.gz -C f23project .", getenv("HOME"), date_str);
        }

        int the_results = system(the_tar_comm);
        if (the_results == 0)
        {
            printf("The creation of the tar.gz file has been completed.\n");
            forward_feedback(sending_connection, true, var_to_store_tar_file_path, "");
        }
        else
        {
            printf("A problem arose when the tar.gz file was being created.\n");
        }

        // Clean up: remove the f23project directory
        system("rm -rf f23project");
    }
    else
    {
        forward_feedback(sending_connection, false, "", "No file found.");
    }
    client_server = 0;
    connection_stats = false;
    number_of_clients = 0;
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

// Function to connect the client request to the mirror
int the_connection_to_mirror(char *argv[])
{
    // necessary variables
    int the_client_server_side, portNumber;
    socklen_t len;
    struct sockaddr_in servAdd;
    // create a socket
    if ((the_client_server_side = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    { // socket()
        fprintf(stderr, "Could not create a socket\n");
        exit(1);
    }
    // create structure
    servAdd.sin_family = AF_INET;
    sscanf(argv[3], "%d", &portNumber);
    servAdd.sin_port = htons((uint16_t)portNumber);

    // convert that structure to binary
    if (inet_pton(AF_INET, argv[2], &servAdd.sin_addr) < 0)
    {
        fprintf(stderr, " inet_pton() has failed\n");
        exit(2);
    }
    // connect to mirror
    if (connect(the_client_server_side, (struct sockaddr *)&servAdd, sizeof(servAdd)) < 0)
    { // Connect()
        fprintf(stderr, "connect() failed and was terminated.\n");
        exit(3);
    }
    // return socket descriptor
    return the_client_server_side;
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

// Function to check if the server is successfully connected to the mirror
void checking_connection_to_mirror(char *argv[])
{
    // call function to get socket descriptor
    int sending_connection = the_connection_to_mirror(argv);
    if (sending_connection == -1)
    {
        fprintf(stderr, "not being able to connect to the mirror. Please check IP/port and try again.\n");
        exit(0);
    }
    else
    {
        printf("Link to the mirror was verified.\n");
        close(sending_connection);
    }
}

void the_route_comm(char *argv[], int client_connection_sd)
{
    // connect to mirror and get socket descriptor
    int sending_connection = the_connection_to_mirror(argv);
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
    // printf("Wow..You are Sucessfully Connected to the mirror: %d\n", sending_connection);

    bool keeping_the_connection = true;
    while (keeping_the_connection)
    {
        // arr for receiving commands from client
        char command[1000];
        // get command from client
        ssize_t bytes_received = recv(client_connection_sd, command, sizeof(command) - 1, 0);
        if (bytes_received < 0)
        {
            fprintf(stderr, "recv() failed\n");
            exit(5);
        }
        // mirror response buffer
        char the_response_buffer[50000];
        // Null-terminate the received data
        command[bytes_received] = '\0';
        // send received command to mirror
        if (send(sending_connection, command, strlen(command), 0) < 0)
        {
            fprintf(stderr, "send() failed\n");
            exit(0);
        }
        printf("Command %s routed to Mirror\n\n", command);
        if (strcmp(command, "quitc") == 0 || strcmp(command, " ") == 0 || strcmp(command, "") == 0)
        {
            // client sent quit command
            printf("Exiting...\n");
            close(sending_connection);
            close(client_connection_sd);
            keeping_the_connection = false;
            break;
        }
        // client did not send quit, read response from mirror
        bytes_received = recv(sending_connection, the_response_buffer, 50000, 0);
        the_response_buffer[bytes_received] = '\0';
        if (bytes_received > 0)
        {
            if (strcmp(the_response_buffer, "TAR_FILE_FLAG") == 0)
            {
                // received tar file flag from mirror, forward it to client
                send(client_connection_sd, the_response_buffer, bytes_received, 0);

                memset(the_response_buffer, 0, sizeof(the_response_buffer));

                // read size of tar file
                bytes_received = recv(sending_connection, the_response_buffer, 50000, 0);
                the_response_buffer[bytes_received] = '\0';
                // send size to client
                send(client_connection_sd, the_response_buffer, bytes_received, 0);

                // create a buffer, large enough to receive data of tar file
                long bytes_of_tar_file = atol(the_response_buffer);
                char *buffer_for_tar_file = (char *)malloc(bytes_of_tar_file);
                if (buffer_for_tar_file == NULL)
                {
                    fprintf(stderr, "Error: An issue with memory allocation occurred.\n");
                    return;
                }
                ssize_t bytes_received = 0;
                size_t total_bytes_received = 0;
                // iteratively receive data of tar file
                while (total_bytes_received < bytes_of_tar_file)
                {
                    bytes_received = recv(sending_connection, buffer_for_tar_file + total_bytes_received, bytes_of_tar_file, 0);
                    if (bytes_received <= 0)
                    {
                        if (bytes_received == 0)
                        {
                            printf("Error: The connection has been closed by the server.\n");
                        }
                        else
                        {
                            fprintf(stderr, "Error: There was an issue obtaining the data.\n");
                        }
                        free(buffer_for_tar_file);
                        return;
                    }
                    total_bytes_received += bytes_received;
                }
                buffer_for_tar_file[sizeof(buffer_for_tar_file)] = '\0';
                sleep(2);
                // send data to client
                send(client_connection_sd, buffer_for_tar_file, total_bytes_received, 0);
                printf("The client received the response.\n");
            }
            else if (strcmp(the_response_buffer, "MESSAGE_FLAG") == 0)
            {
                // got message flag from mirror, send it to client
                send(client_connection_sd, the_response_buffer, bytes_received, 0);

                memset(the_response_buffer, 0, sizeof(the_response_buffer));
                bytes_received = recv(sending_connection, the_response_buffer, 50000, 0);
                the_response_buffer[bytes_received] = '\0';
                // receive and send message to client
                send(client_connection_sd, the_response_buffer, bytes_received, 0);
                printf("sent to the client via message.\n");
            }
            else
            {
                fprintf(stderr, "Received an unsuitable reply from the mirror.\n");
            }
        }
    }

    exit(0);
    client_server = 0;
    connection_stats = false;
    number_of_clients = 0;
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

void handeling_the_client_at_mirror(char *argv[], int sending_connection)
{

    printf("Connected to mirror\n");
    printf("--------------------------------\n");
    int pid = fork();
    if (pid == 0)
    {
        the_route_comm(argv, sending_connection);
    }
    else if (pid == -1)
    {
        fprintf(stderr, "While connecting to the client, an error happened.\n");
    }
}

// Function to process the client requested command implementation
void process_client(int sending_connection)
{
    bool continue_loop = true;
    char command[1000];
    while (continue_loop)
    {
        // Receive the command from the client
        ssize_t bytes_received = recv(sending_connection, command, sizeof(command) - 1, 0);
        if (strcmp(command, "") == 0 || strcmp(command, " ") == 0)
        {
            continue_loop = false;
            break;
        }

        // Null-terminate the received data
        command[bytes_received] = '\0';

        // Create the copy of the command to able to manipulate the command from the client
        char copying_comm[1000];
        strcpy(copying_comm, command);

        // Tokenize the command based on space delimiter
        char *command_type = strtok(copying_comm, " ");

        // Add cases for getfdb and getfda commands
        if (strcmp(command_type, "getfdb") == 0 || strcmp(command_type, "getfda") == 0)
        {
            // Handle getfdb and getfda commands
            handle_getfd_command_from_client(sending_connection, command);
        }
        else if (strcmp(command_type, "fgets") == 0)
        {
            // Fgets command implementation
            handle_fgets_command_from_client(sending_connection, command);
        }
        else if (strcmp(command_type, "getfz") == 0)
        {
            // Tarfgetz command implementation
            handling_the_getfz_comm(sending_connection, command);
        }
        else if (strcmp(command_type, "getfn") == 0)
        {
            // Filesrch command implementation
            handeling_the_getfn_at_server(sending_connection, command);
        }
        else if (strcmp(command_type, "getft") == 0)
        {
            // Targzf command implementation
            handling_the_getft_in_server(sending_connection, command);
        }
        else if (strcmp(command_type, "quitc") == 0)
        {
            // Quit command
            continue_loop = false;
            break;
        }
        memset(command, '\0', sizeof(command));
    }

    close(sending_connection);
    exit(0);
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

void handle_client_at_server(int sending_connection)
{
    printf("Connected to server\n");
    int pid = fork();
    if (pid == 0)
    {
        process_client(sending_connection);
    }
    else if (pid == -1)
    {
        fprintf(stderr, "An error occured while connecting to the client.\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Please check structure: %s <Server Port#> <Mirror IP Address> <Mirror Port#>\n", argv[0]);
        exit(0);
    }
    // verify mirror is running or not
    checking_connection_to_mirror(argv);
    the_present_directory_path();

    // variables required for socket connection
    int listen_sd, sending_connection, port_number;
    socklen_t len_of_socket;
    struct sockaddr_in server_add;

    // get socket descriptor
    if ((listen_sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "Could not create socket\n");
        exit(1);
    }

    // add IP/Port to a structure
    server_add.sin_family = AF_INET;
    server_add.sin_addr.s_addr = htonl(INADDR_ANY);
    sscanf(argv[1], "%d", &port_number);
    server_add.sin_port = htons((uint16_t)port_number);

    // bind received socket descriptor
    bind(listen_sd, (struct sockaddr *)&server_add, sizeof(server_add));

    // listen for connections
    listen(listen_sd, 20);

    while (1)
    {
        // Wait for someone to connect
        sending_connection = accept(listen_sd, (struct sockaddr *)NULL, NULL);
        if (sending_connection != -1)
        {
            // Received a request, increase count
            the_total_number_of_clients_handled++;

            if (the_total_number_of_clients_handled <= 4)
            {
                printf("Server: count is %d\n", the_total_number_of_clients_handled);
                handle_client_at_server(sending_connection);
            }
            else if (the_total_number_of_clients_handled > 4 && the_total_number_of_clients_handled <= 8)
            {
                printf("Mirror: count is %d\n", the_total_number_of_clients_handled);
                handeling_the_client_at_mirror(argv, sending_connection);
            }
            else
            {
                // Alternate between server and mirror starting from the 9th connection
                if ((the_total_number_of_clients_handled - 8) % 2 == 1)
                {
                    printf("Server: count is %d\n", the_total_number_of_clients_handled);
                    handle_client_at_server(sending_connection);
                }
                else
                {
                    printf("Mirror: count is %d\n", the_total_number_of_clients_handled);
                    handeling_the_client_at_mirror(argv, sending_connection);
                }
            }
            close(sending_connection);
        }
    }
    close(sending_connection);
}