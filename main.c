/*
 * project2.c
 *
 *  Created on: Dec 22, 2021
 *      Author: Hager
 */

#include <stdio.h>
#include <string.h>
#define g "green"
#define o "Orange"
#define r "Red"
#define WITH_ENGINE_TEMP_CONTROLLER 1
struct variables{
	char input1;
	char input2;
	char color;
	int room_temp;
	int engine_temp;
	int speed;
	char *AC_state;
	char *engine_state;
}V1;

// function declaration
void start();
void sensors_set_menu();
void controller_temp_sensor(int *CT);
void room_temp_sensor(int *RT);
void speed_of_vehicle(int *n);
void display();
void control_system();
void test();

int main() {
	setvbuf( stdout, NULL, _IONBF, 0 );
	//Initialization
	V1.speed=60;
	V1.room_temp=23;
	V1.engine_temp=120;
	V1.AC_state="OFF";
	V1.engine_state="OFF";

	control_system();  //the main control vehicle system

	//test();           // remove the double slash to test the function of #define
	                   // also double slash the control_system() function :D
	return 0;
}

void control_system(){
	start();
	scanf(" %c",&V1.input1);
	while(1){
	if(V1.input1=='c'){
		printf("Quit the system\n");
	break;
	}
	else if(V1.input1=='b'){
		printf("Turn off the vehicle\n\n");
		start();
		scanf(" %c",&V1.input1);
	}
	else{
	    sensors_set_menu();
	    scanf(" %c",&V1.input2);
	    if(V1.input2=='a'){
	    	start();
	    	scanf(" %c",&V1.input1);

	    }
	    else if (V1.input2=='b'){
	    	printf("Enter the traffic color:\n");
	    	scanf("%s", &V1.color);
	    	speed_of_vehicle(&V1.speed);
	        display();
	    	}
	    else if (V1.input2=='c'){
	    	printf("Enter value of room temperature:\n");
	    	scanf("%d",&V1.room_temp);
	    	room_temp_sensor(&V1.room_temp);
	    	display();
	    }
	    else{
	    	printf("Enter value of engine temperature:\n");
	    	    	scanf("%d",&V1.engine_temp);
	    	    	controller_temp_sensor(&V1.engine_temp);
	    	    	display();
	    }
	    }
	}
}
// start menu will always be displayed to run vehicle
void start(){
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
}
// set menu will always be displayed when the engine is turned on
void sensors_set_menu(){
	printf("a.Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
}

// display speed of vehicle according to traffic light color
void speed_of_vehicle(int *n) { //pass by address function
	if(V1.color=='g'){
		*n=100;  //set speed=100
	}
	else if (V1.color=='o'){
		*n=30;  //set speed=30
			 // AC state
		        V1.AC_state="ON";
			    // calculating room temperature
				(V1.room_temp) = (V1.room_temp) * (5/4) + 1;

				V1.engine_state="ON";
			    // calculating engine controller temperature
				(V1.engine_temp)= (V1.engine_temp) * (5/4) + 1;
			}

	else {
		*n=0;  //set speed =0
       }
	}

void room_temp_sensor(int *RT){ // RT= room temperature
		if((*RT > 30)||(*RT < 10)){
			*RT=20;  //set room temp =20
			// AC state
			V1.AC_state="ON";
		}
		else{
			V1.AC_state="OFF";
		}
}

void controller_temp_sensor(int *CT){  //CT =controller temperature
		if((*CT<100)||(*CT>150)){
			*CT=125;  //set engine temp =125
			//engine controller state
			V1.engine_state="ON";
			}
	    else{
			V1.engine_state="OFF";
		}
}

// display the current vehicle states
void display (){

	//print engine state (on or off)
if(V1.input1=='a'){
	printf("Engine state:%s\n","ON");
}
else {
	printf("Engine state:%s\n","OFF");
}
	printf("AC:%s\n",V1.AC_state);

    //speed_of_vehicle(&V1.speed);
	printf("Vehicle Speed is:%d Km/hr\n",V1.speed);

	//room_temp_sensor(&V1.room_temp);
	printf("Room Temperature is:%d C\n",V1.room_temp);

	//print controller state
	printf("Engine Temperature Controller state is %s\n",V1.engine_state );

	//controller_temp_sensor(&V1.engine_temp);
	printf("Engine Temperature is:%d C\n\n",V1.engine_temp);
}
//function to test the e #define WITH_ENGINE_TEMP_CONTROLLER
void test(){
// if with engine temperature controller is defined then execute this (defif)
#if (WITH_ENGINE_TEMP_CONTROLLER==1)
printf("enter speed of vehicle");
scanf("%d",&V1.speed);
if(V1.speed==30){
	printf("Enter value of engine temperature:\n");
    scanf("%d",&V1.engine_temp);
    controller_temp_sensor(&V1.engine_temp);
    if (!strcmp( V1.engine_state, "OFF")){
 				V1.engine_state="ON";
 			    // calculating engine controller temperature
 				(V1.engine_temp)= (V1.engine_temp) * (5/4) + 1;
    }

	//print controller state
	printf("Engine Temperature Controller state is %s\n",V1.engine_state );

	//controller_temp_sensor(&V1.engine_temp);
	printf("Engine Temperature is:%d C\n\n",V1.engine_temp);
}
else{
printf("Enter value of engine temperature:\n");
    scanf("%d",&V1.engine_temp);
    controller_temp_sensor(&V1.engine_temp);
    //print controller state
    	printf("Engine Temperature Controller state is %s\n",V1.engine_state );

    	//controller_temp_sensor(&V1.engine_temp);
    	printf("Engine Temperature is:%d C\n\n",V1.engine_temp);
}
#endif
}
