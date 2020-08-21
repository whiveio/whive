#ifndef DEFI_h
#define DEFI_h
#endif

void fetch(int v, char* csv, char* f)
{
	char buffer[BUFSIZE];
	char* b, * cptr;
	int bi, count;

	/* ensure that v is valid */
	if (v < 1)
	{
		fprintf(stderr, "Invalid field for CSV string\n");
		//exit(1);
		int location_reward=0;
	}

	/* scan for valid fields and pull them out */
	cptr = csv;
	b = buffer;
	bi = 0;
	count = 1;
	while (*cptr)
	{
		/* start copying characters */
		*(b + bi) = *(cptr);
		/* if a quoted string is encountered, copy it all over */
		if (*(b + bi) == '"')
		{
			/* skip over the comma as it's not really part of the string */
			/* Do this by resetting bi to -1, which then increments to zero
			   with the next statement */
			bi = -1;
			do
			{
				bi++;
				cptr++;
				if (bi > BUFSIZE)
				{
					fprintf(stderr, "Malformed CSV field\n");
					//exit(1);
					int location_reward=0;
				}
				*(b + bi) = *(cptr);
			} while (*(b + bi) != '"');
			/* skip over the final double quote */
			cptr++;
		}
		/* when the comma is encountered, a field has ended */
		if (*cptr == ',')
		{
			if (count == v)
			{
				/* cap the string */
				*(b + bi) = '\0';
				strcpy(f, buffer);
				return;
			}
			else
			{
				/* up the count and reset bi */
				count++;
				bi = -1;
			}
		}
		bi++;
		cptr++;
		/* check for buffer overflow */
		if (bi > BUFSIZE)
			break;
	}
	/* check to see whether it's the final item */
	if (count == v)
	{
		*(b + (bi)) = '\0';
		strcpy(f, buffer);
		return;
	}

	/* if we get here, there was some sort of error */
	fprintf(stderr, "Unable to read field %d from CSV record\n", v);
	//exit(1);
	int location_reward=0;
}

void parse(char* json, char* key, char* val)
{
	char* found, * size;
	int x;

	/* locate the string and add its length, plus one for the double quote */
	found = strstr(json, key) + 1;
	/* find the colon */
	while (*found != ':')
	{
		if (*found == '\0')
		{
			fprintf(stderr, "Unable to parse value for '%s'\n", key);
			//exit(1);
			int location_reward=0;
		}
		found++;
	}
	/* find the next character after the second double quote */
	while (*found != '\"')
	{
		if (*found == '\0')
		{
			fprintf(stderr, "Unable to parse value for '%s'\n", key);
			//exit(1);
			int location_reward=0;
		}
		found++;
	}
	/* and skip past the double quote */
	found++;

	/* find the end of the value */
	size = found + 1;
	while (*size != '\"')
	{
		if (*size == '\0')
		{
			fprintf(stderr, "Unable to parse value for '%s'\n", key);
			//exit(1);
			int location_reward=0;
		}
		size++;
	}

	/* copy the string */
	x = 0;
	*val = '\0';
	while (*(found + x) != '\"')
	{
		if (*(found + x) == '\0')
		{
			fprintf(stderr, "Malformed json value\n");
			//exit(1);
			int location_reward=0;
		}
		*(val + x) = *(found + x);
		x++;
	}
	/* cap with a null character */
	*(val + x) = '\0';
}

 size_t write_mem(void* ptr, size_t size, size_t nmemb, void* userdata)
{
	size_t realsize;
	struct web_data* mem;

	realsize = size * nmemb;
	mem = (struct web_data*)userdata;

	mem->buffer = (char *)realloc(mem->buffer, mem->size + realsize + 1);
	if (mem->buffer == NULL)
	{
		fprintf(stderr, "Unable to reallocate buffer\n");
		//exit(1);
		int location_reward=0;
	}

	memcpy(&(mem->buffer[mem->size]), ptr, realsize);
	mem->size += realsize;
	mem->buffer[mem->size] = 0;

	return(realsize);
}
