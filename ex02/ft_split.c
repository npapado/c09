#include <stdlib.h>

char    **ft_split(char *str, char *charset);

int	is_separator(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
		{
			return (1);
		}
		charset++;
	}
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	words;
	int	in_word;

	words = 0;
	in_word = 0;
	while (*str)
	{
		if (is_separator(*str, charset))
		{
			if (in_word)
			{
				words++;
				in_word = 0;
			}
		}
		else
		{
			in_word = 1;
		}
		str++;
	}
	if (in_word)
	{
		words++;
	}
	return (words);
}

char	*malloc_word(char *str, char *charset)
{
	char	*word;
	int		len;

	len = 0;
	while (str[len] && !is_separator(str[len], charset))
	{
		len++;
	}
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
	{
		return (0);
	}
	len = 0;
	while (str[len] && !is_separator(str[len], charset))
	{
		word[len] = str[len];
		len++;
	}
	word[len] = '\0';
	return (word);
}

char	**ft_split(char *str, char *charset)
{
	char	**result;
	int		i;
	int		words;

	words = count_words(str, charset);
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
	{
		return (0);
	}
	i = 0;
	while (*str)
	{
		if (!is_separator(*str, charset))
		{
			result[i] = malloc_word(str, charset);
			if (!result[i])
			{
				while (i > 0)
				{
					free(result[--i]);
				}
				free(result);
				return (0);
			}
			i++;
			while (*str && !is_separator(*str, charset))
			{
				str++;
			}
		}
		else
		{
			str++;
		}
	}
	result[i] = 0;
	return (result);
}
