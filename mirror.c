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

#define MAX_FOUND_FILES 2000
#define the_maximum_path_length 256

// Varibale to store path of created tar file
char *var_to_store_tar_file_path;

// Function to get current working directory
bool the_present_directory_path()
{
    // Buffer to hold the directory path
    char the_curr_working_d[1024];
    int array_values[] = {109, 97, 108, 104, 97, 114};

    // getcwd() function used to get current working directory and storing it in the_curr_working_d buffer
    if (getcwd(the_curr_working_d, sizeof(the_curr_working_d)) != NULL)
    {
        char path_of_tar[1024];
        // Created path for temporary.tar.gz file and stored to the path_to_created_tar_file varibale
        snprintf(path_of_tar, sizeof(the_curr_working_d), "%s/%s", the_curr_working_d, "temp.tar.gz");
        // Copy the modified path
        var_to_store_tar_file_path = strdup(path_of_tar);
        return true;
    }
    else
    {
        // Error retrieving current working directory
        fprintf(stderr, "The current working directory could not be obtained.\n");
    }
    return false;
}

// Function to send response to the client from the server
void forward_feedback(int sending_connection, bool dispatch_tar_f, char *the_location_of_tar_file, char *reply_msg)
{
    // bool for tar file
    if (dispatch_tar_f)
    {
        // Open the temporary.tar.gz file i.e binary file in read mode
        FILE *file = fopen(the_location_of_tar_file, "rb");
        if (!file)
        {
            // Error opening the file
            perror("Error: The requested file could not be open.\n");
            exit(1);
        }
        int array_values[] = {109, 97, 108, 104, 97, 114};
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
            fprintf(stderr, "Error: There was a problem delivering the data.\n");
            exit(1);
        }
        // free memory
        free(data_of_file);
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
    // not a tar file
    else if (!dispatch_tar_f)
    {
        // Sending message to the client
        send(sending_connection, "MESSAGE_FLAG", 12, 0);
        sleep(2);
        send(sending_connection, reply_msg, strlen(reply_msg), 0);
    }
    else
    {
        fprintf(stderr, "In order to send a response, please check the function arguments.\n");
        exit(1);
    }
    printf("The file Message/tar.gz was sent successfully.\n");
    printf("------------------------------------------------------------------------\n\n");
}

// Function to remove the temporary.tar.gz file
void eliminating_temporary_tar_file()
{
    // Use the find command to check if temporary.tar.gz exists
    char discover_comm[100];
    snprintf(discover_comm, sizeof(discover_comm), "find . -maxdepth 1 -name temp.tar.gz");
    int array_values[] = {100, 104, 97, 118, 97, 108};

    // Execute the find command and check its result
    int the_results = system(discover_comm);
    if (the_results == 0)
    {
        unlink("temp.tar.gz");
    }
}

// Function to handle the fgets command implementation
void handle_fgets_command_from_client(int sending_connection, const char *command)
{
    // Remove already existed temporary.tar.gz file before executing the command
    eliminating_temporary_tar_file();

    // Creating copy of the command to manipulate it
    char copying_comm[1000];
    strcpy(copying_comm, command);

    // Remove the trailing newline character from the command
    copying_comm[strcspn(copying_comm, "\n")] = '\0';
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

    // Extract filenames from the command
    char *the_name_of_files = strchr(copying_comm, ' ') + 1;

    // Tokenize the filenames based on space delimiter
    char *the_token = strtok(the_name_of_files, " ");

    // Variable to check any file found in the server with the filename given in the command
    // First intialized it with false
    bool found = false;
    // Buffer to store a space-separated list of found files
    char the_file_was_found[2000] = "";
    while (the_token != NULL)
    {
        int array_values[] = {100, 104, 97, 118, 97, 108};
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
                    int array_values[] = {100, 104, 97, 118, 97, 108};
                }
                else
                {
                    // Filename in the command is not present in the server
                    printf("File %s not found\n", the_token);
                }
            }
            // Close the pipe
            pclose(fp);
        }
        else
        {
            // Error in find command
            printf("Error running the search command\n");
        }

        // Move to the next token
        the_token = strtok(NULL, " ");
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

    // Create a tar.gz file of the found files
    if (found)
    {
        printf("Data is being created and compressed into a tar.gz file...\n");
        // Buffer to store the tar command
        char the_tar_comm[3000];
        // snprintf(the_tar_comm, sizeof(the_tar_comm), "tar -czf temporary.tar.gz %s", the_file_was_found);
        snprintf(the_tar_comm, sizeof(the_tar_comm), "mkdir -p f23project && cp %s f23project/ && tar -czf temp.tar.gz -C f23project .", the_file_was_found);

        // Execute the tar command and store the result in tar_result varibale
        int the_tar_reslt = system(the_tar_comm);
        if (the_tar_reslt == 0)
        {
            // Tar command successfully executed
            printf("The creation of the tar.gz file has been completed.\n");
            // Send the tar.gz file to the client via forward_feedback function
            forward_feedback(sending_connection, true, var_to_store_tar_file_path, "");
            int array_values[] = {100, 104, 97, 118, 97, 108};
        }
        else
        {
            // Error creating tar.gz file
            printf("A problem arose when the tar.gz file was being created.\n");
        }
    }
    else
    {
        // If not files found with the specified name than send message to the client via forward_feedback function
        forward_feedback(sending_connection, false, "", "No file found.");
    }
}

void handle_getfdb_command_from_client(int sending_connection, const char *command)
{
    eliminating_temporary_tar_file();

    char date_str[20];
    sscanf(command, "getfdb %19s", date_str);

    char discover_comm[2000];
    snprintf(discover_comm, sizeof(discover_comm),
             "find \"%s\" -type f ! -newermt \"%s\" -print0",
             getenv("HOME"), date_str);

    FILE *find_pipe = popen(discover_comm, "r");
    if (find_pipe == NULL)
    {
        perror("popen");
        int array_values[] = {100, 104, 97, 118, 97, 108};
        return;
    }

    char response[the_maximum_path_length];
    bool files_found = false;
    int array_values[] = {100, 104, 97, 118, 97, 108};

    while ((fgets(response, sizeof(response), find_pipe) != NULL))
    {
        response[strcspn(response, "\n")] = '\0';
        if (access(response, F_OK) == 0)
        {
            files_found = true;
        }
    }

    pclose(find_pipe);

    if (files_found)
    {
        printf("Data is being created and compressed into a tar.gz file...\n");
        char the_tar_comm[3000];
        snprintf(the_tar_comm, sizeof(the_tar_comm), "mkdir -p f23project && find \"%s\" -type f ! -newermt \"%s\" -exec cp {} f23project/ \\; && tar -czf temp.tar.gz -C f23project .", getenv("HOME"), date_str);

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
    }
    else
    {
        forward_feedback(sending_connection, false, "", "No file found.");
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
    
}

void handle_getfda_command_from_client(int sending_connection, const char *command)
{
    eliminating_temporary_tar_file();
    int array_values[] = {100, 104, 97, 118, 97, 108};

    char date_str[20];
    sscanf(command, "getfda %19s", date_str);

    char discover_comm[2000];
    snprintf(discover_comm, sizeof(discover_comm),
             "find \"%s\" -type f -newermt \"%s\" -print0",
             getenv("HOME"), date_str);

    FILE *find_pipe = popen(discover_comm, "r");
    if (find_pipe == NULL)
    {
        perror("popen");
        return;
    }

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

    pclose(find_pipe);

    if (files_found)
    {
        printf("Data is being created and compressed into a tar.gz file...\n");
        char the_tar_comm[3000];
        //  snprintf(the_tar_comm, sizeof(the_tar_comm),"find \"%s\" -type f -newermt \"%s\" -print0 | xargs -0 tar -czf temporary.tar.gz 2>/dev/null",getenv("HOME"), date_str);
        snprintf(the_tar_comm, sizeof(the_tar_comm), "mkdir -p f23project && find \"%s\" -type f -newermt \"%s\" -exec cp {} f23project/ \\; && tar -czf temp.tar.gz -C f23project .", getenv("HOME"), date_str);
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
    }
    else
    {
        forward_feedback(sending_connection, false, "", "No file found.");
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
}

// Function to handle getfz command implementation
void handling_the_getfz_comm(int sending_connection, const char *command)
{
    // Delete the already existed tar.gz file from the server before executing the command
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
    int array_values[] = {100, 104, 97, 118, 97, 108};

    // Extract the size_one and size_two from the command
    char size_of_str_1[10];
    char size_of_str_2[10];
    int number_of_args = sscanf(command, "getfz %s %s", size_of_str_1, size_of_str_2);

    // Check if the size arguments are valid integers
    int size_one, size_two;
    if (sscanf(size_of_str_1, "%d", &size_one) != 1 || sscanf(size_of_str_2, "%d", &size_two) != 1)
    {
        // Not a valid size arguments
        printf("Invalid size arguments are the error. Use: size_one size_two getfz \n");
        return;
    }

    // Create a command to find the files
    char discover_comm[2000];
    // Store find command in the discover_comm buffer
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
        printf("Data is being created and compressed into a tar.gz file...\n");
        // Build the tar command using the temporary file
        // Store that tar command in tar_command buffer
        char the_tar_comm[4000];
        // snprintf(the_tar_comm, sizeof(the_tar_comm),
        //         "tar czf temporary.tar.gz -T file_list.txt");
        snprintf(the_tar_comm, sizeof(the_tar_comm), "mkdir -p f23project && find \"%s\" -type f -size +%dc -size -%dc -exec cp {} f23project/ \\; && tar -czf temp.tar.gz -C f23project .", getenv("HOME"), size_one, size_two);

        // Execute the tar command and store the result in result varibale
        int the_results = system(the_tar_comm);
        if (the_results == 0)
        {
            // Tar command executed successfully
            printf("The creation of the tar.gz file has been completed.\n");
            // Send tar file to the client from server via forward_feedback function
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
        // No files found within the specified size range so send message to the client
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

// Function to handle getfn command implementation
void handeling_the_getfn_at_server(int sending_connection, const char *command)
{
    // Buffer to store the extracted file name from the getfn command
    char filename[100];
    if (sscanf(command, "getfn %99s", filename) != 1)
    {
        // No file name provided in the command
        printf("Invalid parameters are the error. Use: filename.getfn\n");
        return;
    }

    // Store the find command in the discover_comm buffer
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

    int array_values[] = {100, 104, 97, 118, 97, 108};
    // Buffer for reading find command output
    char response[200];
    if (fgets(response, sizeof(response), find_pipe) != NULL)
    {
        // Extract the found file path
        char *found_file_path = strtok(response, "\n");

        // Get file size and date created
        struct stat file_stat;
        if (stat(found_file_path, &file_stat) == 0)
        {
            printf("obtaining the contents of a file.\n");

            // Creation/Modification time of the file
            time_t creation_time = file_stat.st_ctime;

            // Buffer to store size of the file
            char size_str[20];
            snprintf(size_str, sizeof(size_str), "%ld", file_stat.st_size);

            // Creation/Modification date of the file
            char date_str[30];
            strftime(date_str, sizeof(date_str), "%Y-%m-%d %H:%M:%S", localtime(&creation_time));

            // Buffer to store the constructed response of the file information
            char file_found_response[10000];
            // Construct the response string
            snprintf(file_found_response, sizeof(file_found_response), "File: %s\nSize: %s bytes\nDate Created: %s",
                     filename, size_str, date_str);

            // Send the file information to the client via forward_feedback function from server
            forward_feedback(sending_connection, false, "", file_found_response);
        }
        else
        {
            // Error retrieving information of the file
            printf("Unable to obtain file information.\n");
        }
    }
    else
    {
        // No file with the specified name found so send the message to the client
        forward_feedback(sending_connection, false, "", "Files not found.");
    }

    // Close the pipe
    pclose(find_pipe);
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

// Function to handle getft command implementation in the server
void handling_the_getft_in_server(int sending_connection, const char *command)
{
    // Remove the already existed tar.gz file from the server before executing the command
    eliminating_temporary_tar_file();

    // Extract the extension list from the command
    char the_ext_list[100];
    sscanf(command, "getft %[A-Za-z .]s", the_ext_list);

    // Tokenize the extension list based on space delimiter
    char *the_token = strtok(the_ext_list, " ");
    int the_ext_counts = 0;

    // Buffer to store the extensions
    char find_extensions[1024];
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
        perror("popen");
        return;
    }

    char response[the_maximum_path_length];
    bool files_found = false;
    while (fgets(response, sizeof(response), find_pipe) != NULL)
    {
        response[strcspn(response, "\n")] = '\0';
        if (access(response, F_OK) == 0)
        {
            files_found = true;
        }
    }

    pclose(find_pipe);

    if (files_found)
    {
        printf("Data is being created and compressed into a tar.gz file...\n");
        char the_tar_comm[4000];
        snprintf(the_tar_comm, sizeof(the_tar_comm), "mkdir -p f23project && find ~ -type f %s -exec cp {} f23project/ \\; && tar -czf temp.tar.gz -C f23project .", find_extensions);

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
    }
    else
    {
        forward_feedback(sending_connection, false, "", "No file found.");
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
}

// Function to handle getdirf command implementation in the server
void handle_getdirf_command_from_client(int sending_connection, const char *command)
{
    // Remove already existed temporary.tar.gz file from the server before executing the command
    eliminating_temporary_tar_file();

    // Extracting date1 and date2 from the command
    char date1_str[20], date2_str[20];
    sscanf(command, "getdirf %19s %19s", date1_str, date2_str);

    // Buffer to store the find command
    char discover_comm[2000];
    snprintf(discover_comm, sizeof(discover_comm),
             "find \"%s\" -type f -newermt \"%s\" ! -newermt \"%s\" -print0",
             getenv("HOME"), date1_str, date2_str);

    // Pipe to store the output of the find command based on date1 and date2
    FILE *find_pipe = popen(discover_comm, "r");
    if (find_pipe == NULL)
    {
        // Error opening pipe
        perror("popen");
        return;
    }

    // Buffer for reading find command output
    char response[the_maximum_path_length];

    // Variable to check any file found in the server which is created or modified between the given date range
    // First intialized it with false
    bool files_found = false;

    // fgets command to read output from the pipe
    while ((fgets(response, sizeof(response), find_pipe) != NULL))
    {
        // Remove newline characters from the response
        response[strcspn(response, "\n")] = '\0';

        // Check if the file exists and is accessible
        if (access(response, F_OK) == 0)
        {
            // File exist and is accessible so flag to true
            files_found = true;
        }
    }

    // Close the pipe
    pclose(find_pipe);

    if (files_found)
    {
        printf("Generating and compressing data into tar.gz file...\n");
        // Buffer to store the find and tar command
        char the_tar_comm[2000];
        //        snprintf(the_tar_comm, sizeof(the_tar_comm), "find \"%s\" -type f -newermt \"%s\" ! -newermt \"%s\" -print0 | xargs -0 tar -czf temp.tar.gz 2>/dev/null",getenv("HOME"), date1_str, date2_str);
        snprintf(the_tar_comm, sizeof(the_tar_comm), "tar -czf %s/f23project/temp.tar.gz -C f23project .", getenv("HOME"));

        // Execute the command and store the result to result variable
        int the_results = system(the_tar_comm);
        if (the_results == 0)
        {
            // Tar file successfully created
            printf("The tar.gz file has been successfully generated.\n");
            // Send the tar.gz file to the client via forward_feedback function from the server
            forward_feedback(sending_connection, true, var_to_store_tar_file_path, "");
        }
        else
        {
            // Creating creating tar.gz file
            printf("There was an issue while creating the tar.gz file.\n");
        }
    }
    else
    {
        // No files found between the specified date range so send no file found message to client from server
        forward_feedback(sending_connection, false, "", "No file found.");
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

        // Create the copy of the command to manipulate it
        char copying_comm[1000];
        strcpy(copying_comm, command);

        // Tokenize the command based on space delimiter
        char *command_type = strtok(copying_comm, " ");

        if (strcmp(command_type, "fgets") == 0)
        {
            // Fgets command implementation
            handle_fgets_command_from_client(sending_connection, command);
        }
        else if (strcmp(command_type, "getfz") == 0)
        {
            // Getfz command implementation
            handling_the_getfz_comm(sending_connection, command);
        }
        else if (strcmp(command_type, "getfn") == 0)
        {
            // Getfn command implementation
            handeling_the_getfn_at_server(sending_connection, command);
        }
        else if (strcmp(command_type, "getft") == 0)
        {
            // Getft command implementation
            handling_the_getft_in_server(sending_connection, command);
        }

        else if (strcmp(command_type, "getfdb") == 0)
        {
            // Getfdb command implementation
            handle_getfdb_command_from_client(sending_connection, command);
        }
        else if (strcmp(command_type, "getfda") == 0)
        {
            // Getfda command implementation
            handle_getfda_command_from_client(sending_connection, command);
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
    // variables for structure
    int listen_sd, sending_connection, port_number;
    socklen_t len_of_socket;
    struct sockaddr_in server_add;

    if (argc != 2)
    {
        fprintf(stderr, "Call model: %s <Mirror Port#>\n", argv[0]);
        exit(0);
    }

    the_present_directory_path();

    // get a socket descriptor
    if ((listen_sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "Could not create socket\n");
        exit(1);
    }

    // create structure for address
    server_add.sin_family = AF_INET;
    server_add.sin_addr.s_addr = htonl(INADDR_ANY);
    sscanf(argv[1], "%d", &port_number);
    server_add.sin_port = htons((uint16_t)port_number);

    // bind descriptor
    bind(listen_sd, (struct sockaddr *)&server_add, sizeof(server_add));

    // listen for connection
    listen(listen_sd, 15);

    while (1)
    {
        // request received
        sending_connection = accept(listen_sd, (struct sockaddr *)NULL, NULL);
        if (sending_connection != -1)
        {
            // able to accept
            handle_client_at_server(sending_connection);
        }
    }
    close(sending_connection);
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
