 /************************************************************************//**
 *	@brief		real_time_clock.c holds functions that performs the real time clock and generation of ticks for the device
 *	@version	V0.0
 *	@date		17.02.2016
 *	@author		cosinuss
 ****************************************************************************/
 
 /* Includes ---------------------------------------------------------------*/
#include "nrf_gpio.h"
#include "nrf.h"
#include "nrf_drv_config.h"
#include "nrf_drv_rtc.h"
#include "nrf_drv_clock.h"
#include "app_util_platform.h"
#include "app_error.h"
#include <stdint.h>
#include <stdbool.h>
#include "nrf52_bitfields.h"
#include "nrf52.h"
#include "real_time_clock.h"

/* Private define ----------------------------------------------------------*/


/* Private function prototypes ---------------------------------------------*/

/* Private typedef ---------------------------------------------------------*/

/* Private variables -------------------------------------------------------*/
//bool state_of_transision;
uint64_t tickcounter;	//holds the value of elaspe time in ticks
uint64_t switch_start_tick_value;	//holds the value of elapse time of an event in tick
uint16_t switch_counter_value;		//captures the amount of time the switch operated repeatedly during the duration of a particular event
uint32_t err_code;

/* Public functions --------------------------------------------------------*/	
static void rtc_handler(nrf_drv_rtc_int_type_t int_type)
{
   if (int_type == NRF_DRV_RTC_INT_TICK) tickcounter++;
	
	//main timer to keep track of switch function and know when it is ideal and act
	if (1)
	{

	}	
}

void rtc_lfclk_config(void)
{
	ret_code_t err_code = nrf_drv_clock_init();
	APP_ERROR_CHECK(err_code);
	nrf_drv_clock_lfclk_request(NULL);
}

void rtc_config(void)
{
	rtc_lfclk_config( );
	const nrf_drv_rtc_t rtc_instance = NRF_DRV_RTC_INSTANCE(0); /**< Declaring an instance of nrf_drv_rtc for RTC0. */

	//declaration of a struct type to hold configuration parameters
	nrf_drv_rtc_config_t RTC_configuration = NRF_DRV_RTC_DEFAULT_CONFIG(0);
	RTC_configuration.prescaler	= 327;
	
/** @brief Function initialization and configuration of RTC driver instance.
 */
	//Initialize RTC instance
	err_code = nrf_drv_rtc_init(&rtc_instance, &RTC_configuration, rtc_handler);
	APP_ERROR_CHECK(err_code);

	//Enable tick event & interrupt
	nrf_drv_rtc_tick_enable(&rtc_instance,true);

	//Power on RTC instance
	nrf_drv_rtc_enable(&rtc_instance);
}	

uint32_t rtc_elapse_time(void)
{
	return (tickcounter - switch_start_tick_value);
}

void rtc_total_switch_counter (void)	//not sure of this
{
	switch_counter_value++;	
}

uint16_t rtc_switch_counter_value (void)
{
	return (switch_counter_value);	
}

void rtc_switch_start_time(void)
{
	switch_start_tick_value = tickcounter;
}

void rtc_reset_time(void)
{
	switch_start_tick_value =0;
	switch_counter_value = 0;	
}
 /* Private functions ------------------------------------------------------*/