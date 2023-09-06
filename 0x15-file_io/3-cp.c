#include <stdio.h>

/**
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
}
