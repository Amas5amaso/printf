#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/**
 * _printf - Custom printf function.
 * @format: The format string.
 *
 * Return: Number of characters printed.
 */
int _printf(const char *format, ...)
{
	int char_count = 0; /* To track the character count */

	va_list args;

	va_start(args, format);

	while (*format)
	{
		if (*format == '%')
		{
			format++; /* Move past '%' */
			if (*format == 'd' || *format == 'i')
			{
				int num = va_arg(args, int);
				char num_to_str[20];

				snprintf(num_to_str, sizeof(num_to_str), "%d", num);
				write(1, num_to_str, strlen(num_to_str));
				char_count += strlen(num_to_str);
			} else if (*format == 'u')
			{
				unsigned int num = va_arg(args, unsigned int);
				char num_to_str[20];

				snprintf(num_to_str, sizeof(num_to_str), "%u", num);
				write(1, num_to_str, strlen(num_to_str));
				char_count += strlen(num_to_str);

			} else if (*format == 'o')
			{
				unsigned int num = va_arg(args, unsigned int);
				char num_to_str[20];

				snprintf(num_to_str, sizeof(num_to_str), "%o", num);
				write(1, num_to_str, strlen(num_to_str));
				char_count += strlen(num_to_str);
			} else if (*format == 'x' || *format == 'X')
			{
				unsigned int num = va_arg(args, unsigned int);
				char num_to_str[20];

				snprintf(num_to_str, sizeof(num_to_str), (*format == 'x') ? "%x" : "%X", num);
				write(1, num_to_str, strlen(num_to_str));
				char_count += strlen(num_to_str);
			} else if (*format == 'p')
			{
				void *address = va_arg(args, void *);
				char address_to_str[20];

				snprintf(address_to_str, sizeof(address_to_str), "%p", address);
				write(1, address_to_str, strlen(address_to_str));
				char_count += strlen(address_to_str);
			} else if (*format == 'r')
			{
				write(1, "%r", 2);
				char_count += 2;
			} else if (*format == 's')
			{
				char *str = va_arg(args, char *);

				write(1, str, strlen(str));

				char_count += strlen(str);
			} else if (*format == 'c')
			{
				char character = (char)va_arg(args, int);

				write(1, &character, 1);

				char_count++;
			} else if (*format == '%')
			{
				write(1, format, 1); /* Handle a literal '%' character */
				char_count++;
			}
		} else if (*format == '\\')
		{
			format++;

			switch (*format)
			{
			case 'n':
				write(1, "\n", 1);
				break;
			case 'r':
				write(1, "\r", 1);
				break;
			case '\\':
				write(1, "\\", 1);
				break;
			default:
				write(1, "\\", 1);
				write(1, format, 1);
			}
		} else
		{
			write(1, format, 1);
			char_count++;
		}
		format++;
	}

	va_end(args);
	return (char_count);
}
