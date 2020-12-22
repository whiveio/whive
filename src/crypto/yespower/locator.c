#include "locator.h"
//#include "optimizer.h"
//Include Chainparams and Consensus @qwainaina 29/9/2020

#include <consensus/nproc.h>

int locator()
{
/**OPTIMIZER CODE (@qwainaina)**/
//Integrate optimizer to ensure people randomly to set hash from o score; Contributions by whive devs in optimizer.h
//Cores Code 26/03/2020
int nprocs = -1;
int nprocs_max = -1;

//NPROCS DEFINITIONS
#ifdef _WIN32
#ifndef _SC_NPROCESSORS_ONLN
SYSTEM_INFO info;
GetSystemInfo(&info);
#define sysconf(a) info.dwNumberOfProcessors
#define _SC_NPROCESSORS_ONLN
#endif
#endif
#ifdef _SC_NPROCESSORS_ONLN
//

nprocs = NPROCS;
nprocs_max = NPROCS_MAX;

//nprocs = sysconf(_SC_NPROCESSORS_ONLN);
if (nprocs < 1)
{
  printf(stderr, "Could not determine number of CPUs online:\n%s\n");
}

//nprocs_max = sysconf(_SC_NPROCESSORS_CONF);
if (nprocs_max < 1)
{
  printf(stderr, "Could not determine number of CPUs configured:\n%s\n");
}
printf("%ld of %ld processors online \n", nprocs, nprocs_max);

#else
printf(stderr, "Could not determine number of CPUs");
#endif
//End of Cores

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
int location_reward = get_machine_coordinates_reward(url.latitude,url.longitude); //forcing location reward 40% Africa, 20% Carribean, 20% SouthEastAsia, 10% Middle-east, 10% South America, 0% Europe, 0% Asia, 0% America
printf("Location Reward 1: %d \n", location_reward);
//dont call api again here...

/*
printf("Location Counter 2: %d \n", location_counter);
}
*/

//Location code used to be here...

//location_reward = 80; test with value...
int timezone_reward = get_time_zone_reward();
int process_reward = get_processor_reward();
printf("Original Process Reward: %d \n", process_reward);

int p=0;
    //Penalize OS on processor
    #ifdef _WIN32
      {
        printf("Windows \n");
        p=2;
      }
    #elif __linux__
      {
        printf("Linux \n");
        p=1;
      }
    #elif __unix__
      {
        printf("Other unix OS \n");
        p=4;
      }
    #elif __APPLE__
      {
        printf("Apple OS \n");
        p=3;
      }
    #else
      {
        printf("Unidentified OS \n");
        p=5;
      }
    #endif

if (nprocs > 4)
  {
    process_reward = (process_reward * nprocs_max / (nprocs * 2))/p; //this penalizes machines using more than 4 cores by twice the number of cores they are using.
  }
else
  {
    process_reward = (process_reward * nprocs_max / nprocs)/p;
  }

//by @lwandamagere
//extern const double Lwanda;

//Add Stake Reward for Nodes holding balance
int node_balance = 1555555;
//(node_balance/10000000)* 100; //10 Million is chosen as no nodes that are likely to reach number for a long time. Chnage to a %
int stake_reward = (int) (node_balance / BALANCE_DIVISOR * 100);

//printf("Lwanda: %d \n", Lwanda);

printf("Node Balance: %lf \n", node_balance);

printf("Process Reward: %d \n", process_reward);
printf("Stake Reward: %d \n", stake_reward);
printf("Location Reward: %d \n", location_reward);
printf("Timezone Reward: %d \n", timezone_reward);

printf("Processor Weight: %d \n", PROCESSOR_WEIGHT);
printf("Stake Weight: %d \n", STAKE_WEIGHT);
printf("Location Weight: %d \n", LOCATION_WEIGHT);
printf("Timezone Weight: %d \n", TIMEZONE_WEIGHT);
printf("Default LAT: %lf \n", DEFAULT_LAT);
printf("Default LON: %lf \n", DEFAULT_LON);
printf("Balance Divisor: %d \n", BALANCE_DIVISOR);
printf("Upper Limit: %d \n", UPPER_LIMIT);

float total_percentage_reward = ((process_reward * PROCESSOR_WEIGHT / DIVISOR) + (stake_reward * STAKE_WEIGHT / DIVISOR) + (location_reward * LOCATION_WEIGHT / DIVISOR) + (timezone_reward * TIMEZONE_WEIGHT / DIVISOR)); //Add when Coordinates data is available

int optimizer_score = (int)total_percentage_reward; //Generating optimization score o as an integer

return optimizer_score;
//Integrate optimizer to ensure people randomly to set hash from opt score
//Get randomizer score and compare to opt score
//int randomNumber;
}

int randomizer()
{
	int randomNumber;
	srand((unsigned) time(NULL)); //Make number random each time
	randomNumber = (rand() % UPPER_LIMIT) + 1; //Made the max 75 instead of 100 % more forgiving

	return randomNumber;
}
