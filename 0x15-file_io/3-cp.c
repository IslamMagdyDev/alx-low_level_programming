#include "main.h"
#include <stdio.h>

/**
* error_file __ This function checks if files can be successfull opened.
*
* @file_from: file descriptor for source file.
* @file_to: file descriptor for destination file.
* @argv: arguments vector which contains command-line arguments.
*
* this function is responsible for verifying whether specified source
* destination files can be opened for reading & writing, respectively
* either file cannot be opened it prints an error message to standard
* error stream [stderr] indicating problem & exits program
* appropriate exit the code
*
* @file_from: the file descriptor for source file if it is -1 an error
* message is printed stating that reading from source file
* argv[1] is not possible & program exits with exit the code (98)
*
* @file_to: the file descriptor for destination file if it is -1, an error
* message is printed stating that writing to destination file
* argv[2] is not possible & program exits with exit the code (99)
*
* return: this function does not return value
*/
void error_file(int file_from, int file_to, char *argv[])
{
	if (file_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}
	if (file_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
		exit(99);
	}
}

/**
 * main __ the main entry point of file copying program
 *
 * @argc: number of command line arguments
 * @argv: an array of strings containing command line arguments
 *
 * this is main function of program designed to copy contents of one
 * file to another it takes 2 command line arguments
 * copied from & destination file to which content will be written
 * function performs following steps
 *
 * Step 1. checks if correct number of arguments (3) have been provided if not
 *    it prints an error message to stderr indicating correct usage
 *    exits with exit the code (97)
 *
 * Step 2. opens source file specified in argv[1] for reading
 *    destination file specified in argv[2] for writing creating the
 *    creating destination file if it does not exist if either file cannot be opened
 *    the "error_file" function is called to handle error
 *
 *Step 3. reads source file in chunks of (1024) bytes 
 *    rites them to destination file until entire file is copied
 *
 * Step 4. closes both source & destination files if either close operation
 *    fails it prints an error message to (stderr) indicating the specific file
 *    descriptor that couldn't be closed & exits with exit code (100)
 *
 * return: this function returns (0) to indicate successful execution
 */
int main(int argc, char *argv[])
{
	int file_from, file_to, err_close;
	ssize_t nchars, nwr;
	char buf[1024];

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "%s\n", "Usage: cp file_from file_to");
		exit(97);
	}

	file_from = open(argv[1], O_RDONLY);
	file_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0664);
	error_file(file_from, file_to, argv);

	nchars = 1024;
	while (nchars == 1024)
	{
		nchars = read(file_from, buf, 1024);
		if (nchars == -1)
			error_file(-1, 0, argv);
		nwr = write(file_to, buf, nchars);
		if (nwr == -1)
			error_file(0, -1, argv);
	}

	err_close = close(file_from);
	if (err_close == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", file_from);
		exit(100);
	}

	err_close = close(file_to);
	if (err_close == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", file_from);
		exit(100);
	}
	return (0);
}
