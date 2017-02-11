 /************************************************************************//**
 *@brief	real_time_clock.h holds function defination for the real time clock
 *@version	V0.0
 *@date		17.02.2016
 *@author	cosinuss
 ****************************************************************************/
 
 /* the clock generates a tick of 10 millsecond and it also provide the capture of various time interval for the operation of the device*/
 
#ifndef REAL_TIME_CLOCK_H_
#define REAL_TIME_CLOCK_H_

/* Includes ----------------------------------------------------------------*/

/* Exported define ---------------------------------------------------------*/
 
/* Exported typedef --------------------------------------------------------*/

/* Exported variables ------------------------------------------------------*/

/* Exported functions ------------------------------------------------------*/
 
  /***********************************************************************//**
 * configure real time clock.
 * @param[out] void  		  		
 * @param[in]  void    		
 * @retval     void 	
 ****************************************************************************/
void rtc_config(void);

 /***********************************************************************//**
 * configure LFCLK XTAL oscillator for real time clock.
 * @param[out] void  		  		
 * @param[in]  void    		
 * @retval     void 	
 ****************************************************************************/
void rtc_lfclk_config(void);
 
 /************************************************************************//**
 * elapse time function for elaspe time sin an operation.
 * @param[out] void  		  		
 * @param[in]  void    		
 * @retval     elapse time 	
 ****************************************************************************/
uint32_t rtc_elapse_time(void);
 
 /************************************************************************//**
 * rtc_total_switch_counter - for total time switch was on
 * @param[out] void  		  		
 * @param[in]  void    		
 * @retval     elapse time 	
 ****************************************************************************/
void rtc_total_switch_counter(void);
 
  /***********************************************************************//**
 * rtc_switch_counter_value - switch time before start of swtich monitoring
 * @param[out] void  		  		
 * @param[in]  void    		
 * @retval     elapse time 	
 ****************************************************************************/
uint16_t rtc_switch_counter_value(void);
 
 /************************************************************************//**
 * rtc_switch_start_time - tick value at the start time of a timer monitoring event
 * @param[out] void  		  		
 * @param[in]  void    		
 * @retval     void 	
 ****************************************************************************/
void rtc_switch_start_time(void);
	
 /************************************************************************//**
 * rtc_reset_time - reset timer counters after an successful change of state
 * @param[out] void  		  		
 * @param[in]  void    		
 * @retval     void 	
 ****************************************************************************/
void rtc_reset_time(void);
 
 #endif //REAL_TIME_CLOCK_H_