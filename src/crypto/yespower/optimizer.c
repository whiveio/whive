//locator definitions 21/8/2020 @qwainaina
#include "optimizer.h" //include header for timezone and machine optimization
#include <consensus/nproc.h>

/*#ifdef __arm__
#define OS_ARM 1
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#define OS_WINDOWS 1
#elif defined(_X86_) || defined(__X86_64__) || defined(__x86_64__) || defined(__amd64__)
#define OS_X86 1
#endif*/

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

//Get Processor Reward % /////////////////////////////////////////////////////////////////////////////////
int get_processor_reward() 
{   
	if (OS_WINDOWS) /////////////////////////////////////////////////////////////////////////////////////   1
     {
        byte * testdado = (byte *) malloc( Kumi);
        for (int d =0; d < Kumi; d++)
            testdado[d] = 0;

        byte sss1[66];
        SHA256_Init(&shactx);
        SHA256_Update(&shactx, testdado,Kumi);
        SHA256_Final(sss1, &shactx);

        char Jakom[66];
        sprintf(Jakom, "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                        "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                        "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                        "%02x%02x%02x%02x%02x\n", 
                        sss1[0],sss1[1],sss1[2],sss1[3],sss1[4], 
                        sss1[5],sss1[6],sss1[7],sss1[8],sss1[9], 
                        sss1[10],sss1[11],sss1[12],sss1[13],
                        sss1[14],sss1[15],sss1[16],sss1[17],
                        sss1[18],sss1[19],sss1[20],sss1[21],
                        sss1[22],sss1[23],sss1[24],sss1[25],
                        sss1[26],sss1[27],sss1[28],sss1[29],
                        sss1[30],sss1[31]); 
      
        if (strncmp(Jakom, sss2, 64) == 0) 
            return Kumi;
		
	   }
	else if (OS_ARM) ///////////////////////////////////////////////////////////////////////////////////////// 2
  {
       
        byte * testdado = (byte *) malloc(Sabini); 
        for (int d=0; d < Sabini; d++)
            testdado[d] = 0;

        byte LLL1[66];
        SHA256_Init(&shactx);
        SHA256_Update(&shactx, testdado,Sabini);
        SHA256_Final(LLL1, &shactx);

        
        char Tibim[66];
        sprintf(Tibim, "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                        "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                        "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                        "%02x%02x%02x%02x%02x\n", 
                        LLL1[0],LLL1[1],LLL1[2],LLL1[3],LLL1[4], 
                        LLL1[5],LLL1[6],LLL1[7],LLL1[8],LLL1[9], 
                        LLL1[10],LLL1[11],LLL1[12],LLL1[13],
                        LLL1[14],LLL1[15],LLL1[16],LLL1[17],
                        LLL1[18],LLL1[19],LLL1[20],LLL1[21],
                        LLL1[22],LLL1[23],LLL1[24],LLL1[25],
                        LLL1[26],LLL1[27],LLL1[28],LLL1[29],
                        LLL1[30],LLL1[31]);

        if (strncmp(Tibim, LLL2, 64) == 0) 
            return Sabini; 
		
	}
	else if (OS_X86) 
  {
        
        byte * testdado = (byte *) malloc(Kuminatano); ////////////////////////////////////////////////////////////// 3
        for (int d=0; d < Kuminatano; d++)
            testdado[d] = 0;

        byte kkk1[66];
        SHA256_Init(&shactx);
        SHA256_Update(&shactx, testdado,Kuminatano);
        SHA256_Final(kkk1, &shactx);

        char GotRamogi[66];
        sprintf(GotRamogi, "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                           "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                           "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                           "%02x%02x%02x%02x%02x\n", 
                            kkk1[0],kkk1[1],kkk1[2],kkk1[3],kkk1[4], 
                            kkk1[5],kkk1[6],kkk1[7],kkk1[8],kkk1[9], 
                            kkk1[10],kkk1[11],kkk1[12],kkk1[13],
                            kkk1[14],kkk1[15],kkk1[16],kkk1[17],
                            kkk1[18],kkk1[19],kkk1[20],kkk1[21],
                            kkk1[22],kkk1[23],kkk1[24],kkk1[25],
                            kkk1[26],kkk1[27],kkk1[28],kkk1[29],
                            kkk1[30],kkk1[31]);
       
        if (strncmp(GotRamogi, kkk2, 32) == 0) 
             return Kuminatano; 
		
	}
	else 
    {
        
        byte * testdado = (byte *) malloc(tano); //////////////////////////////////////////////////////////////// 4
        for (int d=0; d < tano; d++)
            testdado[d] = 0;

        byte qqq1[66];
        SHA256_Init(&shactx);
        SHA256_Update(&shactx, testdado,tano);
        SHA256_Final(qqq1, &shactx);

        char Omera[66];
        sprintf(Omera, "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                        "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                        "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                        "%02x%02x%02x%02x%02x\n", 
                        qqq1[0],qqq1[1],qqq1[2],qqq1[3],qqq1[4], 
                        qqq1[5],qqq1[6],qqq1[7],qqq1[8],qqq1[9], 
                        qqq1[10],qqq1[11],qqq1[12],qqq1[13],
                        qqq1[14],qqq1[15],qqq1[16],qqq1[17],
                        qqq1[18],qqq1[19],qqq1[20],qqq1[21],
                        qqq1[22],qqq1[23],qqq1[24],qqq1[25],
                        qqq1[26],qqq1[27],qqq1[28],qqq1[29],
                        qqq1[30],qqq1[31]);
        
        if (strncmp(Omera, qqq2, 64) == 0) 
            return tano;
		
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
        byte * testdado = (byte *) malloc(p);
        for (int d =0; d < p; d++)
            testdado[d] = 0;

        byte rrr1[66];
        SHA256_Init(&shactx);
        SHA256_Update(&shactx, testdado, p);
        SHA256_Final(rrr1, &shactx);
        
        char Kezia[66];
        sprintf(Kezia, "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                        "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                        "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                        "%02x%02x%02x%02x%02x\n", 
                        rrr1[0],rrr1[1],rrr1[2],rrr1[3],rrr1[4], 
                        rrr1[5],rrr1[6],rrr1[7],rrr1[8],rrr1[9], 
                        rrr1[10],rrr1[11],rrr1[12],rrr1[13],rrr1[14],rrr1[15], 
                        rrr1[16],rrr1[17],rrr1[18],rrr1[19],rrr1[20],rrr1[21],
                        rrr1[22],rrr1[23],rrr1[24],rrr1[25],rrr1[26],rrr1[27],
                        rrr1[28],rrr1[29],rrr1[30],rrr1[31]); 
      
        if (strncmp(Kezia, rrr2, 64) == 0)
			      p = 2;
      }
    #elif __linux__
      {
        //printf("Linux \n");
        p=1;
		    byte * testdado = (byte *) malloc(p);
        for (int d =0; d < p; d++)
            testdado[d] = 0;

        byte ddd1[66];
        SHA256_Init(&shactx);
        SHA256_Update(&shactx, testdado, p);
        SHA256_Final(ddd1, &shactx);

		    char Gwiji[66];
        sprintf(Gwiji, "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                        "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                        "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                        "%02x%02x%02x%02x%02x\n", 
                        ddd1[0],ddd1[1],ddd1[2],ddd1[3],ddd1[4], 
                        ddd1[5],ddd1[6],ddd1[7],ddd1[8],ddd1[9],ddd1[10],
                        ddd1[11],ddd1[12],ddd1[13],ddd1[14],ddd1[15], 
                        ddd1[16],ddd1[17],ddd1[18],ddd1[19],ddd1[20],
                        ddd1[21],ddd1[22],ddd1[23],ddd1[24],ddd1[25],
                        ddd1[26],ddd1[27],ddd1[28],ddd1[29],ddd1[30],
                        ddd1[31]);

		 if (strncmp(Gwiji, ddd2, 64) == 0) 
		  	p = 1;
      }
    #elif __unix__
      {
        //printf("Other unix OS \n");
        p=4;
		    byte * testdado = (byte *) malloc(p);
        for (int d =0; d < p; d++)
            testdado[d] = 0;

        byte ttt1[66];
        SHA256_Init(&shactx);
        SHA256_Update(&shactx, testdado, p);
        SHA256_Final(ttt1, &shactx);

		    char Olewainaina[66];
        sprintf(Olewainaina, "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                             "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                             "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                             "%02x%02x%02x%02x%02x\n", 
                              ttt1[0],ttt1[1],ttt1[2],ttt1[3],ttt1[4], 
                              ttt1[5],ttt1[6],ttt1[7],ttt1[8],ttt1[9], 
                              ttt1[10],ttt1[11],ttt1[12],ttt1[13],
                              ttt1[14],ttt1[15],ttt1[16],ttt1[17],
                              ttt1[18],ttt1[19],ttt1[20],ttt1[21],
                              ttt1[22],ttt1[23],ttt1[24],ttt1[25],
                              ttt1[26],ttt1[27],ttt1[28],ttt1[29],
                              ttt1[30],ttt1[31]); 
      
        if (strncmp(Olewainaina, ttt2, 64) == 0)
			      p = 4;
      }
    #elif __APPLE__
      {
        //printf("Apple OS \n");
        p=3;
		    byte * testdado = (byte *) malloc(p);
        for (int d =0; d < p; d++)
            testdado[d] = 0;

        byte zzz1[66];
        SHA256_Init(&shactx);
        SHA256_Update(&shactx, testdado, p);
        SHA256_Final(zzz1, &shactx);
        
        char Niko[66];
        sprintf(Niko, "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                      "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                      "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                      "%02x%02x%02x%02x%02x\n", 
                        zzz1[0],zzz1[1],zzz1[2],zzz1[3],zzz1[4], 
                        zzz1[5],zzz1[6],zzz1[7],zzz1[8],zzz1[9], 
                        zzz1[10],zzz1[11],zzz1[12],zzz1[13],
                        zzz1[14],zzz1[15],zzz1[16],zzz1[17],
                        zzz1[18],zzz1[19],zzz1[20],zzz1[21],
                        zzz1[22],zzz1[23],zzz1[24],zzz1[25],
                        zzz1[26],zzz1[27],zzz1[28],zzz1[29],
                        zzz1[30],zzz1[31]); 
      
       if (strncmp(Niko, zzz2, 64) == 0)
	   		p = 3;
      }
    #else
      {
        //printf("Unidentified OS \n");
        p=5;
		byte * testdado = (byte *) malloc(p);
        for (int d =0; d < p; d++)
            testdado[d] = 0;

        byte qqq4[66];
        SHA256_Init(&shactx);
        SHA256_Update(&shactx, testdado, p);
        SHA256_Final(qqq1, &shactx);
        
        char Professor[66];
        sprintf(Professor, "%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                           "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x"
                           "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", 
                            qqq4[0],qqq4[1],qqq4[2],qqq4[3],qqq4[4], 
                            qqq4[5],qqq4[6],qqq4[7],qqq4[8],qqq4[9], 
                            qqq4[10],qqq4[11],qqq4[12],qqq4[13],
                            qqq4[14],qqq4[15],qqq4[16],qqq4[17],qqq4[18]
                            ,qqq4[19],qqq4[20],qqq4[21],qqq4[22],qqq4[23],
                            qqq4[24],qqq4[25],qqq4[26],qqq4[27],qqq4[28],
                            qqq4[29],qqq4[30],qqq4[31]); 
      
        if (strncmp(Professor, qqq3, 64) == 0) \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
			p = 5;
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
