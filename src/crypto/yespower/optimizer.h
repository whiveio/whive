/*GitHub Devs: Algorithm designed by @qwainaina, python by @henchhing-limbu, cpp & c by @ajazayeri72*/
#include <stdio.h>
#include <time.h>


//Define Time Zones
#define EARLIEST_AFRICAN_TIMEZONE -1
#define LATEST_AFRICAN_TIMEZONE 4
#define EARLIEST_ASIAN_TIMEZONE 5
#define EARLIEST_EUROPEAN_TIMEZONE 0

//Define Regional Rewards
#define CARRIBEAN_REGION_REWARD 15
#define SOUTH_AMERICAN_REGION_REWARD 15
#define AFRICAN_REGION_REWARD 50
#define ASIAN_REGION_REWARD 15
#define OTHER_REGION_REWARD 5

//Define TOTAL_YESPOWER_REWARD 103.125 - NOT NEEDED ANY MORE

//Define Machine Processor
#define OS_ARM 1
#define OS_WINDOWS 0

struct coordinate
{
  int top_left_x;
	int top_left_y;
	int bottom_right_x;
	int bottom_right_y;
};

struct coordinate RegionCoordiantes(int x1, int x2, int x3, int x4);
int get_processor_reward();
int get_timezone();
int get_time_zone_reward();
int get_machine_coordinates_reward(double latitude, double longitude);
void define_coordinates();
