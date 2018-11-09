char *_strstr(const char *str,
	const char *substr)
{
	if (str == NULL || substr == NULL)
	{
		return NULL;
	}

	if (*substr == '\0')
	{
		return (char *)str;
	}

	char *s = (char *)str;
	while (*s != '\0')
	{
		char *s1 = s;
		char *s2 = (char *)substr;
		while (*s1&&*s2&&*s1 == *s2)
		{
			s1++;
			s2++;
		}
		if (*s2 == '\0')
		{
			return s;
		}
		s++;
	}
	return NULL;
}