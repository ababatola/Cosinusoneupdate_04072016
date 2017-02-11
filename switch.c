 /************************************************************************//**
 *	@brief		switch.c functions that works as the user interface of the device
 *	@version	V0.0
 *	@date		17.02.2016
 *	@author		cosinuss
 ****************************************************************************/
 /*  this class function handles all switch operation based on the device gpiote peripheral system*/
/* Includes ----------------------------------------------------------------*/
#include "nrf_gpio.h"
#include "nrf.h"
#include <stdint.h>
#include "app_error.h"
#include <stdbool.h>
#include "nrf_drv_gpiote.h"
#include "switch.h"
#include "real_time_clock.h"

/* define ------------------------------------------------------------------*/
//extern bool state_of_transision;

/* Private define ----------------------------------------------------------*/

/* Private function prototypes ---------------------------------------------*/

 /************************************************************************//**
 * switch_handler: Function to handle switch event based on chip gpiote peripheral
 * @param[out] void  		
 * @param[in]  nrf_drv_gpiote_pin_t pin  	- pin at which event occured
 * @param[in]  nrf_gpiote_polarity_t action	- polarity action  
 * @retval     void 	
 ****************************************************************************/
void switch_handler (nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action);
/* Private typedef ---------------------------------------------------------*/

/* Private variables -------------------------------------------------------*/

devicestate presentstate;	//holds device present state
devicestate paststate;		//holds device past state
devicestate newstate;		//holds device new state

/* Public functions --------------------------------------------------------*/	

void switch_config (void)
{
	presentstate = offstate;
	newstate = offstate;
	ret_code_t err_code;

	//initialise the gpiote module
	err_code = nrf_drv_gpiote_init();
	APP_ERROR_CHECK(err_code);

	//configure output pin, i guess not needed
	//nrf_drv_gpiote_out_config_t outputport_config = GPIOTE_CONFIG_OUT_SIMPLE(false);

	//err_code = nrf_drv_gpiote_out_init(outputport, &outputport_config);
	//APP_ERROR_CHECK(err_code);

	//configure input pin	to
	nrf_drv_gpiote_in_config_t configswitchport = GPIOTE_CONFIG_IN_SENSE_HITOLO(true);	//high accuracy at input read
	configswitchport.pull = NRF_GPIO_PIN_PULLUP;	//configure as pull up
	
	//to initialie GPIOTE of the selected pin
	err_code = nrf_drv_gpiote_in_init(switchpin, &configswitchport, switch_handler);
	APP_ERROR_CHECK(err_code);
	
	//enable a gpiote input event
	nrf_drv_gpiote_in_event_enable(switchpin, true);	
}

bool	device_state_change()
{
	if (newstate == presentstate)return false;
	else {
		paststate = presentstate;
		presentstate = newstate;
		return true;
	}				
}

devicestate device_state( )
{
	return presentstate;
}

devicestate device_previous_state( )
{
	return paststate;
}

void device_past_state_update( )
{
	paststate  = presentstate;
}

void device_new_state(devicestate state)
{
	newstate = state;	
}
void device_present_state_Update(devicestate state)
{
	presentstate  = state;
}

/* Private functions -------------------------------------------------------*/
void switch_handler (nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
	switch (presentstate)
		{
		case (offstate):
			newstate = onstate;				
		break;
		case (onstate):
			rtc_switch_start_time();
			rtc_total_switch_counter ();
		break;
		case (volume):
			rtc_switch_start_time();				
			rtc_total_switch_counter();
		break;
		case (activate_left_speaker):	
		break;	
		default:
		break;
	}
}
