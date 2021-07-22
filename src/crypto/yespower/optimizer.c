//locator definitions 21/8/2020 @qwainaina
#include "optimizer.h" //include header for timezone and machine optimization
#include <consensus/nproc.h>

#ifdef __arm__
#define OS_ARM 1
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#define OS_WINDOWS 1
#elif defined(_X86_) || defined(__X86_64__) || defined(__x86_64__) || defined(__amd64__)
#define OS_X86 1
#endif

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

int randomizer()
{
	int randomNumber;
	srand((unsigned) time(NULL)); //Make number random each time
	randomNumber = (rand() % UPPER_LIMIT) + 1; //Made the max 75 instead of 100 % more forgiving

   return randomNumber;
}


//Optimizer function
int optimizer()
{
     /**OPTIMIZER CODE (@qwainaina)**/
     //Integrate optimizer to ensure people randomly to set hash from o score; 
     //Contributions by whive devs in optimizer.h
     //Cores Code 26/03/2020
     
     //NPROCS DEFINITIONS
     #ifdef _WIN32
     #ifndef _SC_NPROCESSORS_ONLN
      SYSTEM_INFO info;
      GetSystemInfo(&info);
      #define sysconf(a) info.dwNumberOfProcessors
      #define _SC_NPROCESSORS_ONLN
     #endif
      #define NPROCS  sysconf(_SC_NPROCESSORS_ONLN)
      #define NPROCS_MAX  sysconf(_SC_NPROCESSORS_CONF)
     #else
      #define NPROCS nl  
      #define NPROCS_MAX  nc 
     #endif	
	
     int nprocs = -1;
     int nprocs_max = -1;

     nprocs = NPROCS;
     nprocs_max = NPROCS_MAX;

     //nprocs = sysconf(_SC_NPROCESSORS_ONLN);
     if (nprocs < 1)
     {
       fprintf(stderr, "Could not determine number of CPUs online\n");
     }

     //nprocs_max = sysconf(_SC_NPROCESSORS_CONF);
     if (nprocs_max < 1)
     {
        fprintf(stderr, "Could not determine number of CPUs configured\n");
     }
     else{
      //printf(stderr, "Could not determine number of CPUs");
     //End of Cores
     } 
     //printf("TESTING COUNTER REPETION \n");
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

     /* initialize curl */
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

     /* complete within 20 seconds */
     curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

     /* make the call */
     res = curl_easy_perform(curl);

     /* confirm that the call was successful, bail if not */
     if (res != CURLE_OK)
     {
        fprintf(stderr, "Curl read failed: %s\n", curl_easy_strerror(res));
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


     CARRIBEAN_REGION = RegionCoordiantes(-90, 30, -45, 15);
     SOUTH_AMERICAN_REGION = RegionCoordiantes(-90, 15, -30, -60);
     AFRICAN_REGION = RegionCoordiantes(-20, 30, 50, -45);
     ASIAN_REGION = RegionCoordiantes(50, 30, 90, -30);

     //Integrate optimizer to ensure people randomly to set hash from o score; Contributions by whive devs in optimizer.h
     //Get Machine Coordinates 21/08/2020
     //forcing location reward 40% Africa, 20% Carribean, 20% SouthEastAsia, 10% Middle-east, 10% South America, 0% Europe, 0% Asia, 0% America
     int location_reward = get_machine_coordinates_reward(url.latitude,url.longitude); 

     //Location code used to be here...

    //location_reward = 80; test with value...
    int timezone_reward = get_time_zone_reward();
    int process_reward = get_processor_reward();

    int p=0;
    //Penalize OS on processor
    #ifdef _WIN32
      {
        //printf("Windows \n");
        p=2;
      }
    #elif __linux__
      {
        //printf("Linux \n");
        p=1;
      }
    #elif __unix__
      {
        //printf("Other unix OS \n");
        p=4;
      }
    #elif __APPLE__
      {
        //printf("Apple OS \n");
        p=3;
      }
    #else
      {
        //printf("Unidentified OS \n");
        p=5;
      }
    #endif

      if (NPROCS  > 4)
      {
	  //this penalizes machines using more than 4 cores by twice the number of cores they are using.
          process_reward = (process_reward * nprocs_max / (nprocs * 2))/p; 
      }
      else
      {
         process_reward = (process_reward * nprocs_max / nprocs)/p;
      }


      //Add Stake Reward for Nodes holding balance
      int node_balance = 1555555;
      int stake_reward = (int) (node_balance / BALANCE_DIVISOR * 100);

      //Add when Coordinates data is available
      float total_percentage_reward = ((process_reward * PROCESSOR_WEIGHT / DIVISOR) + (stake_reward * STAKE_WEIGHT / DIVISOR) 
		                       + (location_reward * LOCATION_WEIGHT / DIVISOR) + (timezone_reward * TIMEZONE_WEIGHT / DIVISOR)); 

      int optimizer_score = (int)total_percentage_reward; //Generating optimization score o as an integer

  return optimizer_score;
}
