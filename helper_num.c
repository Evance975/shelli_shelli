#include "shell.h"

/**
 * long_to_string - converts number to string.
 * @number: number to be converted to string.
 * @string: buffer to save number as string.
 * @base: base for number conversion
 *
 * Return: Nothing.
 */
void long_to_string(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long cociente = number;
	char letters[] = {"0123456789abcdef"};

	if (cociente == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (cociente)
	{
		if (cociente < 0)
			string[index++] = letters[-(cociente % base)];
		else
			string[index++] = letters[cociente % base];
		cociente /= base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	str_reverse(string);
}


/**
 * _atoi - convert str to int.
 *
 * @k: pointer to string origin.
 * Return: int of string or 0.
 */
int _atoi(char *k)
{
	int sign = 1;
	unsigned int number = 0;
	/*1- analysis sign*/
	while (!('0' <= *k && *k <= '9') && *k != '\0')
	{
		if (*k == '-')
			sign *= -1;
		if (*k == '+')
			sign *= +1;
		k++;
	}

	/*2 - number extraction */
	while ('0' <= *k && *k <= '9' && *k != '\0')
	{

		number = (number * 10) + (*k - '0');
		k++;
	}
	return (number * sign);
}

/**
 * count_characters - count instances of chars in string.
 *
 * @string: pointer to str origin.
 * @character: string with the chars to be counted
 * Return: int of string or 0.
 */
int count_characters(char *string, char *character)
{
	int q = 0, counter = 0;

	for (; string[q]; q++)
	{
		if (string[q] == character[0])
			counter++;
	}
	return (counter);
}
