#include "main.h"
#include <stdio.h>

/**
<<<<<<< HEAD
* error_file - Checks if files can be opened and handles errors.
* @file_from: File descriptor of the source file.
* @file_to: File descriptor of the destination file.
* @argv: Command-line arguments vector.
*
* Description: This function checks if the specified files can be opened.
* If not, it prints an error message and exits with the corresponding error code.
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
* main - Entry point of the program.
* @argc: Number of command-line arguments.
* @argv: Command-line arguments vector.
*
* Return: Always returns 0.
*
* Description: This program copies the contents of one file to another file.
* It takes two command-line arguments: the source file and the destination file.
* If the number of arguments is incorrect, it prints a usage message and exits.
*/
int main(int argc, char *argv[])
{
int file_from, file_to, err_close;
ssize_t nchars, nwr;
char buf[1024];

// Check the number of command-line arguments
if (argc != 3)
{
dprintf(STDERR_FILENO, "%s\n", "Usage: cp file_from file_to");
exit(97);
}

// Open the source file for reading and the destination file for writing
file_from = open(argv[1], O_RDONLY);
file_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0664);

// Check if file openings were successful
error_file(file_from, file_to, argv);

// Initialize the character count to read
nchars = 1024;

// Loop to read and write file contents
while (nchars == 1024)
{
nchars = read(file_from, buf, 1024);
if (nchars == -1)
error_file(-1, 0, argv);
nwr = write(file_to, buf, nchars);
if (nwr == -1)
error_file(0, -1, argv);
}

// Close both files and check for errors
err_close = close(file_from);
if (err_close == -1)
{
dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", file_from);
exit(100);
}

err_close = close(file_to);
if (err_close == -1)
{
dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", file_to);
exit(100);
}

return( 0);
=======
* check_file_open - checks if files can be opened.
* @file_from: file_from.
* @file_to: file_to.
* @argv: arguments vector.
* Return: no return.
*/
void check_file_open(int file_from, int file_to, char *argv[])
{
	if (file_from == -1)
	{
		printf("Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}
	if (file_to == -1)
	{
		printf("Error: Can't write to %s\n", argv[2]);
		exit(99);
	}
}

/**
* main - check the code for Holberton School students.
* @argc: number of arguments.
* @argv: arguments vector.
* Return: Always 0.
*/
int main(int argc, char *argv[])
{
	int file_from, file_to, err_close;
	ssize_t nchars, nwr;
	char buf[1024];

	if (argc != 3)
	{
		printf("Usage: cp file_from file_to\n");
		exit(97);
	}

	file_from = open(argv[1], O_RDONLY);
	file_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0664);
	check_file_open(file_from, file_to, argv);

	nchars = 1024;
	while (nchars == 1024)
	{
		nchars = read(file_from, buf, 1024);
		if (nchars == -1)
			check_file_open(-1, 0, argv);
		nwr = write(file_to, buf, nchars);
		if (nwr == -1)
			check_file_open(0, -1, argv);
	}

	err_close = close(file_from);
	if (err_close == -1)
	{
		printf("Error: Can't close fd %d\n", file_from);
		exit(100);
	}

	err_close = close(file_to);
	if (err_close == -1)
	{
		printf("Error: Can't close fd %d\n", file_from);
		exit(100);
	}
	return (0);
>>>>>>> fac715dfcd7a1e732e4598321a7c4d529c0d83d7
}
