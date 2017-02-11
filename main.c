 /************************************************************************//**
 *	@brief		main.c
 *	@brief		main function that holds the super loop
 *	@version 	V0.0
 *	@date	  	15.04.2016
 *	@author 	cosinuss
 ****************************************************************************/
 
 /* 
 code detailed discription
 The code performs the audio and volume control function of cosinuss one device update
 The code performs the audio function using an external I2S chip which is interfaced
 With the SoC via the I2S interface.
 The main function handles device state change and the test for change volume control

*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "app_error.h"
#include "nrf.h"
#include "nrf_gpio.h"
#include "audiocodec_public.h"
#include "i2s_master_public.h"
#include "i2c1_master_public.h"
#include "real_time_clock.h"
#include "switch.h"
#include "nrf.h"
#include "nrf52_bitfields.h"
#include "nrf52.h"
#include "general_defination.h"

 /************************************************************************//**
 *	@brief		config.c holds all configuration function of the device
 *	@version 	V0.0
 *	@date	  	15.04.2016
 *	@author 	cosinuss
 ****************************************************************************/
void Config(void);	

int main (void)
{
	Config( );
while (true)
{
if (device_state_change ())	//check if device state change has happened
	{
	if (device_state () == offstate)  //stop audio function
		{
			audiocodec_stop_i2s( );
		}
		if  (device_state () == onstate)   //start audio function
			{
				if (device_previous_state () != volume)
					{
						audiocodec_config();
						I2Smaster_startTransmit( );
					}
			}
			if  (device_state () == volume)  //start volume control function
				{
					rtc_switch_start_time();	//start function to capture ticks value at start of volume state
				}
	}
//loop to determine if to enter off state or volume control state
if ((device_state () == onstate) &(rtc_switch_counter_value( ) >= 1 ))	//two conditions, condition 1 for long press and condition 2 for pressand release
	{
	if (nrf_gpio_pin_read (switchpin) == 1 )	//end of long press on switch
		{
		if ( rtc_elapse_time() <= HALFSECOND)	//check to determine if it is long press or press and release  ???reduce by half again
			{
				device_new_state (offstate);
				rtc_reset_time ();
			}
			else //go to volume state
				{
					device_new_state (volume);
					rtc_reset_time ();
				}
		}
	}
				
//the main volume control loop
if (device_state () == volume)
	{
		if ((nrf_gpio_pin_read (switchpin) == 1) &( rtc_elapse_time() >= FIVESECONDS))	//no operation of switch, return back to on state
			{
				device_new_state(onstate);
				rtc_reset_time ();
			}
			else if ((nrf_gpio_pin_read (switchpin) == 0) & ( rtc_elapse_time() >= HALFSECOND) )	//volume control is in increase volume state  ???you need timer to make this more perfect for volume increase
				{
					audiocodec_volume_control(INCREASE_VOLUME);
					rtc_reset_time ();
					rtc_switch_start_time();
				}
				else if ((rtc_switch_counter_value( ) == 1 ) & (rtc_switch_counter_value( ) == 1 ))	//for volume decrease
					{
						audiocodec_volume_control(DECREASE_VOLUME);
						rtc_reset_time ();
						rtc_switch_start_time();
					}
	}
	//Send Event is a hint instruction
	__SEV();		
	//    Wait For Event is a hint instruction that permits the processor to enter
	//	a low-power state until one of a number of events occurs
	__WFE();
	}
}

void Config( )
{
	rtc_config( );		//configuration of rtc
	switch_config ( );	//configuration of swtich
	I2C1master_config();	//configuration of I2C1master
	audiocodec_config();	//configuration of audiocodec
	I2Smaster_config( );	//configuration of I2S master
};