/*GitHub Devs: Algorithm designed by @qwainaina, python by @henchhing-limbu, cpp & c by @ajazayeri72*/
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <unistd.h>
#endif

/* GitHub Devs: Algorthim designed by @qwainaina, python by @henchhing-limbu, cpp & c by @ajazayeri72*/
#include <stdio.h>
#include <time.h>

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <math.h>

#include <errno.h>
#include <time.h>

#include "./curl/curl.h"
#include "./curl/easy.h"

//Define Time Zones
#define EARLIEST_AFRICAN_TIMEZONE -1
#define LATEST_AFRICAN_TIMEZONE 4
#define EARLIEST_ASIAN_TIMEZONE 5
#define EARLIEST_EUROPEAN_TIMEZONE 0


//Define Regional Rewards
#define CARRIBEAN_REGION_REWARD 25
#define SOUTH_AMERICAN_REGION_REWARD 10
#define AFRICAN_REGION_REWARD 45
#define ASIAN_REGION_REWARD 15
#define OTHER_REGION_REWARD 5

//Define TOTAL_YESPOWER_REWARD 103.125 - NOT NEEDED ANY MORE

//Define Machine Processor
#define OS_ARM 0
#define OS_WINDOWS 0
#define OS_X86 0


struct coordinate
{
  int top_left_x;
	int top_left_y;
	int bottom_right_x;
	int bottom_right_y;
};

struct coordinate RegionCoordiantes(int x1, int x2, int x3, int x4) {
	struct coordinate result;
	result.top_left_x = x1;
	result.top_left_y = x2;
	result.bottom_right_x = x3;
	result.bottom_right_y = x4;
	return result;
}

struct coordinate CARRIBEAN_REGION;
struct coordinate SOUTH_AMERICAN_REGION;
struct coordinate AFRICAN_REGION;
struct coordinate ASIAN_REGION;

//Locator started here

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

//function for locator.c returns optimization score @qwainaina

int optimizer(); //call locator function @qwainaina

int randomizer();//call randomizer function @qwainaina

int optimizer_score_ex; //call locator function @qwainaina

int randomNumber_ex;//call randomizer function @qwainaina
