#include <stdio.h>
#include <wiringPi.h>
#include <signal.h> //Signal 사용 헤더파일
#include <unistd.h>
#include <string.h> 
#include <errno.h>
#include <stdlib.h> //exit() 사용 헤더파일
#define trigPin 1       //gpio 21
#define echoPin 29 //gpio 18
#define PUMP	21 // BCM_GPIO 5

int main(void)
{
        int distance=0;
        int pulse = 0;

        long startTime;
        long travelTime;
        if(wiringPiSetup () == -1)
        {
	        printf("Unable GPIO Setup"); 
                return 1;
        }

        pinMode (trigPin, OUTPUT);
        pinMode (echoPin, INPUT);
        pinMode (PUMP, OUTPUT) ;

        while(1)
        {
                digitalWrite (trigPin, LOW);
     	        usleep(2);
                digitalWrite (trigPin, HIGH);
                usleep(20);
                digitalWrite (trigPin, LOW);

                while(digitalRead(echoPin) == LOW);

                startTime = micros();

                while(digitalRead(echoPin) == HIGH);
	      travelTime = micros() - startTime;

                int distance = travelTime / 58;

                printf( "Distance: %dcm\n", distance);
                delay(200);
	    if(distance < 4 )
		{
                //printf("here - PUMP on\n");
                digitalWrite (PUMP, 1) ; // On
		}
	else if(distance > 4)
		 {
		digitalWrite (PUMP, 0) ; // On
		}

	}
}

