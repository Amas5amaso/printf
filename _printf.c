#include "main.h"
#include <stdio.h>
#include <stdarg.h>

/**
 * _printf - print function
 * @format: print format
 *
 * Return: the characters in print
 */

int_printf(const char *format, ...)
{
	va_list args;

	va_start(args, format);

	int count = 0;

	for (int i = 0; format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{
			i++;
			switch (format[i])
			{
				case 'c':
				{
				char c = va_arg(args, int);
				/* char promte to int putchar(c); */
				count++;
				break;
				}
				case 's':

				char *s = va_arg(args, char*);

				while (*s)
				{
				putchar(*s++);
				count++;
				}
				break;
			}
			case '%':
			putchar('%');
			count++;
			break;
		}
		else
		{
		putchar(format[i]);
		count++;
		}
	}
	va_end(args);
	return (count);
}
