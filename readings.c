#include <stdio.h>
#include <string.h>
#include "readings.h"

/*
	takes in a min and max value
	and a name for the device
	set values of the device
*/

int init_device(struct Device *device, char *name, float max, float min) {
	//Using strcpy because name is a char array and using -> instead of .
	strcpy(device-> name, name);
	device->max = max;
	device->min = min;
	
    return ERR_OK;
}

/*
	populate the output parameter reading and return the proper error code
*/
int init_reading(struct Reading *reading, struct Device *device, float value, char const* room) {
	//check if the device is null, then it would an invalid value
	if (device == NULL) {
        return ERR_INVALID_VALUE;
    }
    
    if (valid_device_reading(device, value) != ERR_OK) {
        return ERR_INVALID_VALUE;
    }
    
    //populating readings
	reading->device = device;
	reading->value = value;
	strncpy(reading->room, room, MAX_STR - 1); //-1 because of /0 
	reading->room[MAX_STR - 1] = '\0';
	
    return ERR_OK;
}


/*
	returns ERR_INVALID_VALUE if the device value is not working
	work with any device passed in
*/

int valid_device_reading(struct Device *device, float value) {
	//checking if the values are valid
    if (value > device->max || value < device->min){
    	return ERR_INVALID_VALUE;
    }else{
    	return ERR_OK;
    }
}


/*
	make the array size
*/
int init_reading_collection(struct ReadingCollection *readings) {
	int size;
    readings->size = 0;
    
    return ERR_OK;
}


/*
	Uses C string compare functions to add each of the arrays
*/
int add_reading(struct ReadingCollection *readings, struct Reading reading) {
	
	//checks if the list is full
	if(readings->size >= MAX_STR){
		return ERR_MAX_CAPACITY;
	}
	
	//if the collection is empty, there is nothing to compare
	
	
	if (readings->size == 0){
		readings->elements[0] = reading;
		readings->size += 1;
	}else{
		int i = 0;
		//compare it to the string
		for (i = 0; i <readings->size; i++){
			if (strncmp(reading.room, readings->elements[i].room, MAX_STR) < 0){
				break;
		}
		
		for (int j = readings->size; j > i; j--) {
        	readings->elements[j] = readings->elements[j - 1];
    	}
    	
		readings->elements[i + 1] = reading; 
		readings->size += 1;
		return ERR_OK;
		
	}
	
    return ERR_OK;
	}
}

/*
	prints the room name, reading, device name and value
*/
int print_reading(const struct Reading *reading) {
	printf("%16s| %16s| %.2f \n", reading->room, reading->device->name, reading->value);
    return ERR_OK;
}

/*
	prints off the sorted array
*/
int print_reading_collection(struct ReadingCollection *readings) {
	for (int i = 0; i < readings->size; i++) {
        print_reading(&readings->elements[i]); 
    }
    return ERR_OK;

}
