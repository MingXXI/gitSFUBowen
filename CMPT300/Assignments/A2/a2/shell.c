// Shell starter file
// You may make any changes to any part of this file.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

#define COMMAND_LENGTH 1024
#define NUM_TOKENS (COMMAND_LENGTH / 2 + 1)
#define maxhistory 10

char history[maxhistory][COMMAND_LENGTH];
int history_indices[maxhistory] = {-1};
int command_count = 0;
int ctrlC = 0;

int overwrite_command(char cur_history[maxhistory][COMMAND_LENGTH], int cur_history_indices[maxhistory],int index){
	int i = 0;
	if(command_count > maxhistory){
		for (i = 0; i < maxhistory; i++){
			if(cur_history_indices[i] == (index)){
				memcpy(cur_history[(maxhistory-1)], cur_history[i], strlen(cur_history[i]));
				break;
			}
		}
	}
	else {
		memcpy(cur_history[(command_count-1)], cur_history[index - 1], strlen(cur_history[index - 1]));
		i = command_count-1;
	}
	return i;
}




void add_command(char cur_history[maxhistory][COMMAND_LENGTH], char *buff, int cur_history_indices[maxhistory]){
	int k = 0;
	while(buff[k] != '\n'){
		k++;
	}
	buff[k] = '\0';
	if(command_count >= maxhistory){
		for(int y = 0; y < maxhistory; y++){
			cur_history_indices[y] = cur_history_indices[y+1];
		}
		memcpy(cur_history[(maxhistory-1)], buff, strlen(buff));
		cur_history_indices[(maxhistory-1)] = command_count+1;
	}
	else {
		memcpy(cur_history[command_count], buff, strlen(buff));
		cur_history_indices[command_count] = command_count+1;
	}
}

void print_history(char cur_history[maxhistory][COMMAND_LENGTH], int cur_history_indices[maxhistory]){
	int end_index = maxhistory;
	for(int i = 0; i < maxhistory; i++){
		if(cur_history_indices[i] == 0){
			end_index = i;
			break;
		}
	}
	char output_str[256];
	for(int j = 0; j < end_index; j++){
		sprintf(output_str, "%d",cur_history_indices[end_index-j-1]-1);
		write(STDOUT_FILENO, output_str, strlen(output_str));
		write(STDOUT_FILENO, "\t", strlen("\t"));
		write(STDOUT_FILENO, cur_history[(end_index-j-1)], strlen(cur_history[(end_index-j-1)]));
		write(STDOUT_FILENO, "\n", strlen("\n"));
	}
}


/**
 * Command Input and Processing
 */

/*
 * Tokenize the string in 'buff' into 'tokens'.
 * buff: Character array containing string to tokenize.
 *       Will be modified: all whitespace replaced with '\0'
 * tokens: array of pointers of size at least COMMAND_LENGTH/2 + 1.
 *       Will be modified so tokens[i] points to the i'th token
 *       in the string buff. All returned tokens will be non-empty.
 *       NOTE: pointers in tokens[] will all point into buff!
 *       Ends with a null pointer.
 * returns: number of tokens.
 */
int tokenize_command(char *buff, char *tokens[])
{
	int token_count = 0;
	_Bool in_token = false;
	int num_chars = strnlen(buff, COMMAND_LENGTH);
	for (int i = 0; i < num_chars; i++) {
		switch (buff[i]) {
		// Handle token delimiter	s (ends):
		case ' ':
		case '\t':
		case '\n':
			buff[i] = '\0';
			in_token = false;
			break;

		// Handle other characters (may be start)
		default:
			if (!in_token) {
				tokens[token_count] = &buff[i];
				token_count++;
				in_token = true;
			}
		}
	}
	tokens[token_count] = NULL;
	return token_count;
}

/**
 * Read a command from the keyboard into the buffer 'buff' and tokenize it
 * such that 'tokens[i]' points into 'buff' to the i'th token in the command.
 * buff: Buffer allocated by the calling code. Must be at least
 *       COMMAND_LENGTH bytes long.
 * tokens[]: Array of character pointers which point into 'buff'. Must be at
 *       least NUM_TOKENS long. Will strip out up to one final '&' token.
 *       tokens will be NULL terminated (a NULL pointer indicates end of tokens).
 * in_background: pointer to a boolean variable. Set to true if user entered
 *       an & as their last token; otherwise set to false.
 */






void read_command(char *buff, char *tokens[], _Bool *in_background)
{
	*in_background = false;

	// Read input
	int length = read(STDIN_FILENO, buff, COMMAND_LENGTH-1);
	
	add_command(history, buff, history_indices);
	command_count ++;


	if ( (length < 0) && (errno !=EINTR) ){
  		perror("Unable to read command. Terminating.\n");
    	exit(-1);  /* terminate with error */
	}

	// Null terminate and strip \n.
	buff[length] = '\0';
	if (buff[strlen(buff) - 1] == '\n') {
		buff[strlen(buff) - 1] = '\0';
	}

	// Tokenize (saving original command string)
	int token_count = tokenize_command(buff, tokens);
	if (token_count == 0) {
		return;
	}

	// Extract if running in background:
	if (token_count > 0 && strcmp(tokens[(token_count-1)], "&") == 0) {
		*in_background = true;
		tokens[token_count - 1] = 0;
	}
}

void handle_SIGINT(){
	write(STDIN_FILENO, "\n", strlen("\n"));
	ctrlC = 1;
}

/**
 * Main and Execute Commands
 */
int main(int argc, char* argv[])
{
	char input_buffer[COMMAND_LENGTH];
	char *tokens[NUM_TOKENS];
	int status;
	struct sigaction handler;
	handler.sa_handler = handle_SIGINT;
	handler.sa_flags = 0;
	sigaction(SIGINT, &handler, NULL);
	char cwd[256];
	char homecwd[256];
	getcwd(homecwd,sizeof(homecwd));
	char temphomecwd[256];
	getcwd(temphomecwd,sizeof(temphomecwd));
	char prevcwd[256];
	getcwd(prevcwd,sizeof(prevcwd));
	char curcwd[256];
	while (true) {

		while (waitpid(-1, NULL, WNOHANG) > 0)	//clean up zombie process exited in background
			;
		// Get command
		// Use write because we need to use read() to work with
		// signals, and read() is incompatible with printf().
		getcwd(curcwd, sizeof(curcwd));
		write(STDOUT_FILENO, curcwd, strlen(curcwd));		
		write(STDOUT_FILENO, "$ ", strlen("$ "));
		_Bool in_background = false;
		read_command(input_buffer, tokens, &in_background);

		if (ctrlC == 1){
			tokens[0] = "help";
			tokens[1] = NULL;
			ctrlC = 0;
		}
		restartLoop: 
			if (tokens[0] == NULL){
				chdir(homecwd);
				chdir("..");
				continue;
			}
			else if (strcmp(tokens[0],"!!") == 0){
				int line_num;
				line_num = command_count - 1;
				if(line_num <= 0){
					write(STDIN_FILENO, "SHELL: Unknown history command.\n", strlen("SHELL: Unknown history command.\n"));
					continue;
				}
				else{
					int next_index = overwrite_command(history, history_indices, line_num);
					write(STDIN_FILENO, history[next_index%10],strlen(history[next_index%10]));
					write(STDIN_FILENO, "\n", strlen("\n"));
					tokenize_command(history[next_index % 10], tokens);
					goto restartLoop;
				}
			}
			else if (strchr(tokens[0],'!')){
				int line_num;
				sscanf(tokens[0], "!%d", &line_num);
				line_num += 1;
				if(line_num <= 0 || line_num <command_count - 9 || line_num>command_count){
					write(STDIN_FILENO, "SHELL: Unknown history command.\n", strlen("SHELL: Unknown history command.\n"));
					continue;
				}
				else{
					int next_index = overwrite_command(history, history_indices, line_num);
					write(STDIN_FILENO, history[next_index%10],strlen(history[next_index%10]));
					write(STDIN_FILENO, "\n", strlen("\n"));
					tokenize_command(history[next_index % 10], tokens);
					goto restartLoop;
				}
			}

			else if(strcmp(tokens[0], "exit") == 0){
				if(tokens[1] != NULL){
					write(STDOUT_FILENO, "Error: Could not Exit as unexpected argument occured.\n", strlen("Error: Could not Exit as unexpected argument occured.\n"));
				}
				else{
					return 0;
				}
			}
			else if(strcmp(tokens[0], "pwd") == 0){
				getcwd(cwd, sizeof(cwd));
			}
			else if(strcmp(tokens[0], "cd") == 0){
				if(strcmp(tokens[1], "-") == 0){
					chdir(prevcwd);
				}
				else{
					getcwd(prevcwd,sizeof(prevcwd));
					if (tokens[1][0] == '~') {
						chdir(homecwd);
						chdir("..");
						chdir(tokens[1]+2);
					}
					else if (chdir(tokens[1])<0){
						write(STDOUT_FILENO, "Error: Could not change directory.\n", strlen("Error: Could not change directory.\n"));
					}
				}
			}
			else if (strcmp(tokens[0], "history") == 0){
				if(tokens[1] != NULL){
					write(STDOUT_FILENO, "Error: Unexpected Argument Occured.\n", strlen("Error: Unexpected Argument Occured.\n"));
				}
				else{
					print_history(history, history_indices);
				}
			}
			else if (strcmp(tokens[0], "help") == 0){
				if (tokens[1] == NULL){
					write(STDOUT_FILENO, "'exit' is a builtin command for exiting the shell program.\n", strlen("'exit' is a builtin command for exiting the shell program.\n"));
					write(STDOUT_FILENO, "'pwd' is a builtin command for displaying the current working directory.\n", strlen("'pwd' is a builtin command for displaying the current working directory.\n"));
					write(STDOUT_FILENO, "'cd' is a builtin command for changing the current working directory.\n", strlen("'cd' is a builtin command for changing the current working directory.\n"));
					write(STDOUT_FILENO, "'help' is a builtin command for displaying the help information on internal commands.\n", strlen("'help' is a builtin command for displaying the help information on internal commands.\n"));
				}
				else if ( tokens[2] == NULL){
					if(strcmp(tokens[1], "cd") == 0){
						write(STDOUT_FILENO, "'cd' is a builtin command for changing the current working directory.\n", strlen("'cd' is a builtin command for changing the current working directory.\n"));
					}
					else if(strcmp(tokens[1], "pwd") == 0){
						write(STDOUT_FILENO, "'pwd' is a builtin command for displaying the current working directory.\n", strlen("'pwd' is a builtin command for displaying the current working directory.\n"));
					}
					else {
						write(STDOUT_FILENO, "'", strlen("'"));
						write(STDOUT_FILENO, tokens[1], strlen(tokens[1]));
						write(STDOUT_FILENO, "' is an external command or application.\n", strlen("' is an external command or application.\n"));
					}

				}
				else{
					write(STDOUT_FILENO, "Error: more than one argument detacted\n", strlen("Error: more than one argument detacted\n"));
				}
			}
		


		pid_t pid;
		pid = fork();
		if (pid <0){
			write(STDOUT_FILENO, "Fork Failed\n", strlen("Fork Failed\n"));
			exit(-1);
		}
		else if (pid == 0){ 
			execvp(tokens[0], tokens);		//child process excute the command in token[0] with parameter follows up
			exit(-1);
		}
		else {
			if (in_background == false){
					while(waitpid(pid, &status, 0)>0){
						;
					}
			}
		}

		

		if (in_background) {
			write(STDOUT_FILENO, "Run in background.", strlen("Run in background."));
		}

		/**
		 * Steps For Basic Shell:
		 * 1. Fork a child process
		 * 2. Child process invokes execvp() using results in token array.
		 * 3. If in_background is false, parent waits for
		 *    child to finish. Otherwise, parent loops back to
		 *    read_command() again immediately.
		 */

	}
	return 0;
}
