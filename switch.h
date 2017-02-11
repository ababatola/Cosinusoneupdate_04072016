 /************************************************************************//**
 *	@brief		switch.h holds the various parameters and values for the user switch
 *	@version	V0.0
 *	@date		17.05.2016
 *	@author		cosinuss
 ****************************************************************************/
 
#ifndef SWITCH_H_
#define SWITCH_H_
 
 /* Includes ---------------------------------------------------------------*/
#include <stdint.h>

#define switchpin	13	//switch button
#define outputport 18	// PWM output port

/* typedef -----------------------------------------------------------------*/
//enumeration to define device various states
typedef enum {
	offstate = 0,	//device is in off state
	onstate,	//device is in on state and I2S is transferring data
	volume,		//Volume control operation is taking place
	activate_left_speaker
}devicestate;

/* typedef -----------------------------------------------------------------*/
//not used in the code
typedef struct
{
	int64_t starttime_delay;
	int8_t ontime_delay;
	int8_t training_delay;
	int8_t increase_volume_delay;
	int8_t decreace_volume_delay;
	int8_t activate_left_speaker_delay;
}state_time_delay;


 /************************************************************************//**
 * Function initialization and configuration the swtich
 * @param[out] void  		
 * @param[in]  void  		    		
 * @retval     void 	
 ****************************************************************************/
void switch_config(void);

 /************************************************************************//**
 * Function initialization and configuration the swtich
 * @param[out] void  		
 * @param[in]  void  		    		
 * @retval     void 	
 ****************************************************************************/
bool device_state_change(void);

 /************************************************************************//**
 * Function call device state
 * @param[out] void  		
 * @param[in]  void  		    		
 * @retval     devicestate	- returns device state 	
 ****************************************************************************/
devicestate device_state(void);

 /************************************************************************//**
 * Function call device previous state
 * @param[out] void  		
 * @param[in]  void  		    		
 * @retval     devicestate	- returns device previous state 	
 ****************************************************************************/
devicestate device_previous_state(void);

 /************************************************************************//**
 * Function to update past device state
 * @param[out] void  		
 * @param[in]  void  		    		
 * @retval     void 	
 ****************************************************************************/
void device_past_state_update(void);

 /************************************************************************//**
 * Function to update past device state
 * @param[out] void  	
 * @param[in]  devicestate	- previous state
 * @param[in]  devicestate	- new state
 * @retval     void 	
 ****************************************************************************/
void device_new_state(devicestate);

 /************************************************************************//**
 * Function to update present device state
 * @param[out] void  		
 * @param[in]  devicestate	- previous state
 * @param[in]  devicestate	- new state
 * @retval     void 	
 ****************************************************************************/
void device_present_state_Update(devicestate);

#endif //SWITCH_H_