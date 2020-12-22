#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./curl/curl.h"
#include "./curl/easy.h"

#define BUFSIZE 256

/* standard data-chunk-reading structure used by libcurl */
struct web_data {
	char* buffer;
	size_t size;
};
/* structure to store web page information */
struct location {
	char address[BUFSIZE];
	double latitude;
	double longitude;
};

/*
 * Rather than suffer through lots of bulky code to read JSON data
 * I kludged a routine to fetch key-value details. By no means should
 * this code be used to parse other JSON structures, though it came in
 * handy here for this specific purpose.
 */
void parse(char* json, char* key, char* val);

/*
 * Return a specific item from the csv string
 * v is the item number to read, from 1 up to whatever. The csv string
 * is referenced by *csv. *f is the buffer to contain the found data.
 * Data is created locally in buffer[], then copied to *f.
 * Modified so that the result value isn't returned and if the field
 * isn't available, the program quits within the function.
 */
void fetch(int v, char* csv, char* f);

/*
 * Libcurl function to copy bytes read from the web page to memory
 * This is the typical memory-writing function used in curl coding.
 * Information is read in chunks and appended to a buffer. This function
 * may be called repeatedly, which is why it's static, to retain the
 * web_data structure's buffer and size values.
 */
 size_t write_mem(void* ptr, size_t size, size_t nmemb, void* userdata);
