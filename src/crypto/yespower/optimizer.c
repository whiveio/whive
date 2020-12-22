/* GitHub Devs: Algorthim designed by @qwainaina, python by @henchhing-limbu, cpp & c by @ajazayeri72*/
#include <stdio.h>
#include <time.h>

//locator definitions 21/8/2020 @qwainaina
#include "locator.h"
#include "define.c"

#include "optimizer.h" //include header for timezone and machine optimization

#ifdef __arm__
#define OS_ARM 1
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#define OS_WINDOWS 1
#elif defined(_X86_) || defined(__X86_64__) || defined(__x86_64__) || defined(__amd64__)
#define OS_X86 1
#endif

//Get Processor Reward %
int get_processor_reward() {
	if (OS_WINDOWS) {
		return 10;
	}
	else if (OS_ARM) {
		return 70;
	}
	else if (OS_X86) {
		return 15;
	}
	else {
		return 5;
	}
}


//Get Machine Timezone
int get_timezone() {
	time_t now = time(NULL);
    time_t tmp = time(&tmp);
    struct tm *utc = gmtime(&tmp);
    int diff = (now - mktime(utc)) / 3600;
	return diff;
}

//Set timezone score
int get_time_zone_reward() {
	int timezone = get_timezone();
	if ((EARLIEST_AFRICAN_TIMEZONE < timezone) && (timezone <= EARLIEST_EUROPEAN_TIMEZONE)) {
		return 30;

	}
	else
	{
		if ((EARLIEST_EUROPEAN_TIMEZONE < timezone) && (timezone <= LATEST_AFRICAN_TIMEZONE)) {
			return 40;
		}
		else
		{
			if ((LATEST_AFRICAN_TIMEZONE < timezone) && (timezone <= EARLIEST_ASIAN_TIMEZONE)) {
				return 20;
			}
			else
			{
				return 10;
			}
		}
	}
}


//Get timezone score
int get_machine_coordinates_reward(double latitude, double longitude)
{
	if ((CARRIBEAN_REGION.top_left_x <= longitude) && (longitude < CARRIBEAN_REGION.bottom_right_x) && (CARRIBEAN_REGION.bottom_right_y <= latitude) && (latitude < CARRIBEAN_REGION.top_left_y)) {
		return CARRIBEAN_REGION_REWARD;
	}
	else if ((SOUTH_AMERICAN_REGION.top_left_x <= longitude) && (longitude < SOUTH_AMERICAN_REGION.bottom_right_x) && (SOUTH_AMERICAN_REGION.bottom_right_y <= latitude) && (latitude < SOUTH_AMERICAN_REGION.top_left_y)) {
		return SOUTH_AMERICAN_REGION_REWARD;
	}
	else if ((AFRICAN_REGION.top_left_x <= longitude) && (longitude < AFRICAN_REGION.bottom_right_x) && (AFRICAN_REGION.bottom_right_y <= latitude) && (latitude < AFRICAN_REGION.top_left_y)) {
		return AFRICAN_REGION_REWARD;
	}
	else if ((ASIAN_REGION.top_left_x <= longitude) && (longitude < ASIAN_REGION.bottom_right_x) && (ASIAN_REGION.bottom_right_y <= latitude) && (latitude < ASIAN_REGION.top_left_y)) {
		return ASIAN_REGION_REWARD;
	}
	else {
		return OTHER_REGION_REWARD;
	}
}

//Brought location code here.

/*
printf("Location Counter 1: %d \n", location_counter);

//This if avoids multiple api calls.
if (location_counter == 0)
{
*/

printf("TESTING COUNTER REPETION \n");
//locator Code
CURL* curl;
CURLcode res;
char csv_field[BUFSIZE];
struct location url;
struct web_data curl_data;

/* initialize structure */
/* curl_data and url structures must be kept separate or the
 call the curl makes to write_mem() screws up */

curl_data.buffer =  (char *) malloc(1);
curl_data.size = 0;
url.latitude = DEFAULT_LAT;
url.longitude = DEFAULT_LON;

/* initialize locations */
strcpy(url.address, "http://ip-api.com/csv/");

/* initialuze curl */
/* I use the same curl handle for all of the calls,
so only only statement is needed here */
curl = curl_easy_init();

/*---------------- FIRST READ ----------------*/
/* set options */
/* url to read */
curl_easy_setopt(curl, CURLOPT_URL, url.address);
/* The function to read in data chunks */
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_mem);
/* The structure to use for reading */
curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curl_data);
/* make the call */
res = curl_easy_perform(curl);

/* confirm that the call was successful, bail if not */
if (res != CURLE_OK)
  {
    fprintf(stderr, "Curl read failed: %s\n",
      curl_easy_strerror(res)
      );
    //exit(1);
   //int location_reward=0;
  }

/* At this point, the size of the data read is stored in curl_data.size
and the string read is in curl_data.buffer. The data is in CSV format,
which the fetch() function can read */
 /* was the call successful? Fetch the first CSV item from the buffer and
store it in buffer 'csv_field' */
fetch(1, curl_data.buffer, csv_field);
/* if the string csv_field isn't 'success' then the call failed */
if (strncmp(csv_field, "success", 7) != 0)
{
fprintf(stderr, "Failed request from server: %s \n", url.address);
fprintf(stderr, "Retried status: %s \n", csv_field);
//exit(1);
//int location_reward=0;
}

/* Get the latitude value & convert to double */
fetch(8, curl_data.buffer, csv_field);
url.latitude = strtod(csv_field, NULL);

/* Get the longitude value & convert to double */
fetch(9, curl_data.buffer, csv_field);
url.longitude = strtod(csv_field, NULL);


//Error Handling Making Sure no 0.000000 scores ever
if ((url.latitude == 0.000000) && (url.longitude == 0.000000)) //remember to fix the other files.
  {
    url.latitude = DEFAULT_LAT;  //-82.8628
    url.longitude = DEFAULT_LON; //135.0000
  }

printf("Latitude: %lf \n", url.latitude);
printf("Longitude: %lf \n", url.longitude);

CARRIBEAN_REGION = RegionCoordiantes(-90, 30, -45, 15);
SOUTH_AMERICAN_REGION = RegionCoordiantes(-90, 15, -30, -60);
AFRICAN_REGION = RegionCoordiantes(-20, 30, 50, -45);
ASIAN_REGION = RegionCoordiantes(50, 30, 90, -30);

//Integrate optimizer to ensure people randomly to set hash from o score; Contributions by whive devs in optimizer.h
//Get Machine Coordinates 21/08/2020
location_reward = get_machine_coordinates_reward(url.latitude,url.longitude); //forcing location reward 40% Africa, 20% Carribean, 20% SouthEastAsia, 10% Middle-east, 10% South America, 0% Europe, 0% Asia, 0% America
printf("Location Reward 1: %d \n", location_reward);
//dont call api again here...

/*
printf("Location Counter 2: %d \n", location_counter);
}
*/
