#include "shell.h"

/**
 * _strcmp - compare two strings
 * @first: first string to be compared
 * @second: second string to be compared
 *
 * Return: difference of the two strings
 */
int _strcmp(char *first,  char *second)
{
	int i = 0;

	while (first[i] != '\0')
	{
		if (first[i] != second[i])
			break;
		i++;
	}

	return (first[i] - second[i]);
}

/**
 * _strcat - concatenates two strings
 * @destination: string to be concatenated to
 * @source: string to concatenate
 *
 * Return: address of the new string
 */
char *_strcat(char *destination,  char *source)
{
	size_t dest_len = _strlen(destination);
	size_t i;

	for (i = 0; source[i] != '\0'; i++)
		destination[dest_len + i] = source[i];

	destination[dest_len + i] = '\0';

	return (destination);
}

/**
 * _strspn - gets the length of a prefix substring
 * @str1: string to be searched
 * @str2: string to be used
 *
 * Return: number of bytes in initial segment of str1 which are part of str2
 */
size_t _strspn(char *str1,  char *str2)
{
	size_t i = 0;

	while (str1[i] != '\0' && _strchr(str2, str1[i]) != NULL)
		i++;

	return (i);
}

/**
 * _strcspn - computes segment of str1 which consists of characters not in str2
 * @str1: string to be searched
 * @str2: string to be used
 *
 * Return: index at which a char in str1 exists in str2
 */
size_t _strcspn(char *str1,  char *str2)
{
	size_t i = 0;

	while (str1[i] != '\0' && _strchr(str2, str1[i]) == NULL)
		i++;

	return (i);
}

/**
 * _strchr - locates a char in a string
 * @s: string to be searched
 * @c: char to be checked
 *
 * Return: pointer to the first occurrence of c in s
 */
char *_strchr(char *s, int c)
{
	while (*s != '\0' && *s != c)
		s++;

	if (*s == c)
		return ((char *)s);
	else
		return (NULL);
}

