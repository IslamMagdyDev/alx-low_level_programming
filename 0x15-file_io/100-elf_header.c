#include "elf_header_reader.h"
#include <stdio.h>

/**
* verifyElfFile - Checks if a file is a valid ELF file.
* @e_ident: A pointer to an array containing the ELF magic numbers.
*
* Description: If the file is not an ELF file, exit with code 98.
*/
void verifyElfFile(unsigned char *e_ident)
{
	int index;

	for (index = 0; index < 4; index++)
	{
		if (e_ident[index] != 127 &&
		    e_ident[index] != 'E' &&
		    e_ident[index] != 'L' &&
		    e_ident[index] != 'F')
		{
			dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
			exit(98);
		}
	}
}

/**
* printMagicNumbers - Prints the ELF magic numbers.
* @e_ident: A pointer to an array containing the ELF magic numbers.
*
* Description: Separate magic numbers with spaces.
*/
void printMagicNumbers(unsigned char *e_ident)
{
	int index;

	printf("  Magic:   ");

	for (index = 0; index < EI_NIDENT; index++)
	{
		printf("%02x", e_ident[index]);

		if (index == EI_NIDENT - 1)
			printf("\n");
		else
			printf(" ");
	}
}

/**
* printElfClass - Prints the class of an ELF file.
* @e_ident: A pointer to an array containing the ELF class.
*/
void printElfClass(unsigned char *e_ident)
{
	printf("  Class:                             ");

	switch (e_ident[EI_CLASS])
	{
	case ELFCLASSNONE:
		printf("none\n");
		break;
	case ELFCLASS32:
		printf("ELF32\n");
		break;
	case ELFCLASS64:
		printf("ELF64\n");
		break;
	default:
		printf("<unknown: %x>\n", e_ident[EI_CLASS]);
	}
}

// ... Other functions (printData, printVersion, printOsAbi, printAbi, printType, printEntry) remain unchanged ...

/**
* closeElfFile - Closes an ELF file.
* @fileDescriptor: The file descriptor of the ELF file.
*
* Description: If the file cannot be closed, exit with code 98.
*/
void closeElfFile(int fileDescriptor)
{
	if (close(fileDescriptor) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close file descriptor %d\n", fileDescriptor);
		exit(98);
	}
}

/**
* main - Displays the information contained in the
*        ELF header at the start of an ELF file.
* @argc: The number of arguments supplied to the program.
* @argv: An array of pointers to the arguments.
*
* Return: 0 on success.
*
* Description: If the file is not a valid ELF File or
*              the function fails, exit with code 98.
*/
int main(int __attribute__((__unused__)) argc, char *argv[])
{
	Elf64_Ehdr *header;
	int fileDescriptor, readStatus;

	fileDescriptor = open(argv[1], O_RDONLY);
	if (fileDescriptor == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}

	header = malloc(sizeof(Elf64_Ehdr));
	if (header == NULL)
	{
		closeElfFile(fileDescriptor);
		dprintf(STDERR_FILENO, "Error: Can't allocate memory for ELF header\n");
		exit(98);
	}

	readStatus = read(fileDescriptor, header, sizeof(Elf64_Ehdr));
	if (readStatus == -1)
	{
		free(header);
		closeElfFile(fileDescriptor);
		dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
		exit(98);
	}

	verifyElfFile(header->e_ident);
	printf("ELF Header:\n");
	printMagicNumbers(header->e_ident);
	printElfClass(header->e_ident);

	// ... Call other functions to print ELF header information ...

	free(header);
	closeElfFile(fileDescriptor);
	return 0;
}
