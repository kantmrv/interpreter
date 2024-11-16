#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int tokenize(const char *file_contents)
{
	int errors = 0;
	int line = 1;
	bool ignore = false;

	for (int i = 0; i < strlen(file_contents) + 1; ++i)
	{
		if (ignore && file_contents[i] != '\n' && file_contents[i] != '\0')
		{
			continue;
		}
		switch (file_contents[i])
		{
			case '\0':
			{
				fprintf(stdout, "EOF  null\n");
				break;
			}
			case '\t':
			{
				break;
			}
			case '\n':
			{
				++line;
				ignore = false;
				break;
			}
			case ' ':
			{
				break;
			}
			case '!':
			{
				if (file_contents[i + 1] == '=')
				{
					fprintf(stdout, "BANG_EQUAL != null\n");
					++i;
				}
				else
				{
					fprintf(stdout, "BANG ! null\n");
				}
				break;
			}
			case '\"':
			{
				int size = 0;
				for (int j = i + 1; j < strlen(file_contents); ++j)
				{
					if (file_contents[j] == '\"')
					{
						size = j - (i + 1);
						break;
					}
				}

				if (size == 0 || file_contents[i] != '\"')
				{
					fprintf(stderr, "[line %d] Error: Unterminated string.\n", line);
					errors += 1;
					for (int j = i + 1; j < strlen(file_contents) + 1; ++j)
					{
						if (file_contents[j] == ' ' || file_contents[j] == '\0')
						{
							i = j - 1;
							break;
						}
					}
				}
				else
				{
					char *string = malloc(size);
					memcpy(string, &file_contents[i + 1], size);
					fprintf(stdout, "STRING \"");
					for (int j = 0; j < size; ++j)
					{
						fprintf(stdout, "%c", string[j]);
					}
					fprintf(stdout, "\" ");
					for (int j = 0; j < size; ++j)
					{
						fprintf(stdout, "%c", string[j]);
					}
					fprintf(stdout, "\n");
					i += size + 1;
				}

				break;
			}
			case '(':
			{
				fprintf(stdout, "LEFT_PAREN ( null\n");
				break;
			}
			case ')':
			{
				fprintf(stdout, "RIGHT_PAREN ) null\n");
				break;
			}
			case '*':
			{
				fprintf(stdout, "STAR * null\n");
				break;
			}
			case '+':
			{
				fprintf(stdout, "PLUS + null\n");
				break;
			}
			case ',':
			{
				fprintf(stdout, "COMMA , null\n");
				break;
			}
			case '-':
			{
				fprintf(stdout, "MINUS - null\n");
				break;
			}
			case '.':
			{
				fprintf(stdout, "DOT . null\n");
				break;
			}
			case '/':
			{
				if (file_contents[i + 1] == '/')
				{
					ignore = true;
				}
				else
				{
					fprintf(stdout, "SLASH / null\n");
				}
				break;
			}
			case '0' ... '9':
			{
				int size = 1;
				bool demical = false;
				for (int j = i + 1; j < strlen(file_contents) + 1; ++j)
				{
					if (file_contents[j] == '.' && !demical)
					{
						demical = true;
					}
					else if (file_contents[j] < '0' || file_contents[j] > '9')
					{
						size = j - i;
						break;
					}
				}
				char *string = malloc(size);
				memcpy(string, &file_contents[i], size);
				if (demical)
				{
					fprintf(stdout, "NUMBER ");
					for (int j = 0; j < size; ++j)
					{
						fprintf(stdout, "%c", string[j]);
					}
					fprintf(stdout, " ");
					int end = size;
					for (int j = size - 1; j > 0; --j)
					{
						if (string[j] == '0' && string[j - 1] == '.')
						{
							end = j + 1;
							break;
						}
						else if (string[j] == '0')
						{
							end = j;
						}
						else
						{
							break;
						}
					}
					for (int j = 0; j < end; ++j)
					{
						fprintf(stdout, "%c", string[j]);
					}
					fprintf(stdout, "\n");
				}
				else
				{
					fprintf(stdout, "NUMBER ");
					for (int j = 0; j < size; ++j)
					{
						fprintf(stdout, "%c", string[j]);
					}
					fprintf(stdout, " ");
					for (int j = 0; j < size; ++j)
					{
						if (string[j] == '.')
						{
							break;
						}
						else
						{
							fprintf(stdout, "%c", string[j]);
						}
					}
					fprintf(stdout, ".0\n");
				}
				i += size - 1;
				break;
			}
			case ';':
			{
				fprintf(stdout, "SEMICOLON ; null\n");
				break;
			}
			case '<':
			{
				if (file_contents[i + 1] == '=')
				{
					fprintf(stdout, "LESS_EQUAL <= null\n");
					++i;
				}
				else
				{
					fprintf(stdout, "LESS < null\n");
				}
				break;
			}
			case '=':
			{
				if (file_contents[i + 1] == '=')
				{
					fprintf(stdout, "EQUAL_EQUAL == null\n");
					++i;
				}
				else
				{
					fprintf(stdout, "EQUAL = null\n");
				}
				break;
			}
			case '>':
			{
				if (file_contents[i + 1] == '=')
				{
					fprintf(stdout, "GREATER_EQUAL >= null\n");
					++i;
				}
				else
				{
					fprintf(stdout, "GREATER > null\n");
				}
				break;
			}
			case '_':
			case 'a' ... 'z':
			case 'A' ... 'Z':
			{
				int size = 1;
				for (int j = i + 1; j < strlen(file_contents) + 1; ++j)
				{
					if (file_contents[j] == '_' ||
						(file_contents[j] >= 'a' && file_contents[j] <= 'z') ||
						(file_contents[j] >= 'A' && file_contents[j] <= 'Z') ||
						(file_contents[j] >= '0' && file_contents[j] <= '9'))
					{
						continue;
					}
					else
					{
						size = j - i;
						break;
					}
				}
				char *string = malloc(size + 1);
				memcpy(string, &file_contents[i], size);
				string[size] = '\0';
				if (strcmp(string, "and") == 0)
				{
					fprintf(stdout, "AND and null\n");
				}
				else if (strcmp(string, "class") == 0)
				{
					fprintf(stdout, "CLASS class null\n");
				}
				else if (strcmp(string, "else") == 0)
				{
					fprintf(stdout, "ELSE else null\n");
				}
				else if (strcmp(string, "false") == 0)
				{
					fprintf(stdout, "FALSE false null\n");
				}
				else if (strcmp(string, "for") == 0)
				{
					fprintf(stdout, "FOR for null\n");
				}
				else if (strcmp(string, "fun") == 0)
				{
					fprintf(stdout, "FUN fun null\n");
				}
				else if (strcmp(string, "if") == 0)
				{
					fprintf(stdout, "IF if null\n");
				}
				else if (strcmp(string, "nil") == 0)
				{
					fprintf(stdout, "NIL nil null\n");
				}
				else if (strcmp(string, "or") == 0)
				{
					fprintf(stdout, "OR or null\n");
				}
				else if (strcmp(string, "print") == 0)
				{
					fprintf(stdout, "PRINT print null\n");
				}
				else if (strcmp(string, "return") == 0)
				{
					fprintf(stdout, "RETURN return null\n");
				}
				else if (strcmp(string, "super") == 0)
				{
					fprintf(stdout, "SUPER super null\n");
				}
				else if (strcmp(string, "this") == 0)
				{
					fprintf(stdout, "THIS this null\n");
				}
				else if (strcmp(string, "true") == 0)
				{
					fprintf(stdout, "TRUE true null\n");
				}
				else if (strcmp(string, "var") == 0)
				{
					fprintf(stdout, "VAR var null\n");
				}
				else if (strcmp(string, "while") == 0)
				{
					fprintf(stdout, "WHILE while null\n");
				}
				else
				{
					fprintf(stdout, "IDENTIFIER ");
					for (int j = 0; j < size; ++j)
					{
						fprintf(stdout, "%c", string[j]);
					}
					fprintf(stdout, " null\n");
				}
				i += size - 1;
				break;
			}
			case '{':
			{
				fprintf(stdout, "LEFT_BRACE { null\n");
				break;
			}
			case '}':
			{
				fprintf(stdout, "RIGHT_BRACE } null\n");
				break;
			}
			default:
			{
				fprintf(stderr, "[line %d] Error: Unexpected character: %c\n", line, file_contents[i]);
				errors += 1;
				break;
			}
		}
	}
	
	return errors;
}