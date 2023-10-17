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
                        } else if (*format == 'b') 
                        {
                                unsigned int num = va_arg(args, unsigned int);
                                char binary_str[33]; /* Binary representation can be up to 32 bits, plus null-terminator */
                                int i, j = 0;

                                /* Convert the number to binary representation */
                                for (i = 31; i >= 0; i--) {

                                        binary_str[j++] = ((num >> i) & 1) + '0';
                                }
                                binary_str[j] = '\0';

                                /* Write the binary string to the output */
                                write(1, binary_str, strlen(binary_str));
                                char_count += strlen(binary_str);
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
                        } else if (*format == 'l') 
                        {
                                format++; /* Move past 'l' */
                                if (*format == 'd')
                                {
                                    long num = va_arg(args, long);
                                    char num_to_str[20];

                                    snprintf(num_to_str, sizeof(num_to_str), "%ld", num);
                                    write(1, num_to_str, strlen(num_to_str));
                                    char_count += strlen(num_to_str);

                                } else if (*format == 'u')
                                {
                                    unsigned long num = va_arg(args, unsigned long);
                                    char num_to_str[20];

                                    snprintf(num_to_str, sizeof(num_to_str), "%lu", num);
                                    write(1, num_to_str, strlen(num_to_str));
                                    char_count += strlen(num_to_str);
                                }

                        } else if (*format == 'h')
                        {
                                format++; /* Move past 'h' */
                                if (*format == 'd')
                                {
                                    short num = va_arg(args, int); /* Interpret as short */
                                    char num_to_str[20];

                                    snprintf(num_to_str, sizeof(num_to_str), "%hd", num);
                                    write(1, num_to_str, strlen(num_to_str));
                                    char_count += strlen(num_to_str);

                                } else if (*format == 'u')
                                {
                                    unsigned short num = va_arg(args, unsigned int); /* Interpret as unsigned short */
                                    char num_to_str[20];

                                    snprintf(num_to_str, sizeof(num_to_str), "%hu", num);
                                    write(1, num_to_str, strlen(num_to_str));
                                    char_count += strlen(num_to_str);
                                }
                        } else if (*format == 'c')
                        {
                                char character = (char)va_arg(args, int);

                                write(1, &character, 1);

                                char_count++;
                        } else if (*format == 's')
                        {
                                char *str = va_arg(args, char *);

                                write(1, str, strlen(str));

                                char_count += strlen(str);
                        } else if (*format == 'S')
                        {
                                char *str = va_arg(args, char *);
                                int str_length = strlen(str);
                                int i;

                                for (i = 0; i < str_length; i++)
                                {
                                        if (str[i] < 32 || str[i] >= 127)
                                        {
                                                /* Print non-printable characters as \x followed by ASCII code in uppercase hexadecimal (always 2 characters) */
                                                /* Assuming 8-bit ASCII encoding */
                                                char non_printable[5];
                                                snprintf(non_printable, 5, "\\x%02X", (unsigned char)str[i]);
                                                write(1, non_printable, 4);
                                                char_count += 4;
                                        }
                                        else
                                        {
                                                /* Print printable characters directly */
                                                write(1, str + i, 1);
                                                char_count++;
                                        }
                                }
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
