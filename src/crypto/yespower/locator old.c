#include "locator.h"
#include "define.c"

int main()
{
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
	url.latitude = -82.8628;
	url.longitude = 135.0000;

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
		int location_reward=0;
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
		fprintf(stderr, "Failed request from server: %s\n", url.address);
		fprintf(stderr, "Retried status: %s\n", csv_field);
		//exit(1);
		int location_reward=0;
	}

	/* Get the latitude value & convert to double */
	fetch(8, curl_data.buffer, csv_field);
	url.latitude = strtod(csv_field, NULL);

	/* Get the longitude value & convert to double */
	fetch(9, curl_data.buffer, csv_field);
	url.longitude = strtod(csv_field, NULL);

//Error Handling Making Sure no 0.000000 scores ever
	if ((url.latitude == 0.000000) && (url.latitude == 0.000000))
	{
		url.latitude = -82.8628;
		url.longitude = 135.0000;
	}

	printf("LatitudeX: %lf\n", url.latitude);
	printf("LongitudeX: %lf\n", url.longitude);

	printf("\nPress Any Key to Continue...\n");
	getchar();

	return(0);
}
