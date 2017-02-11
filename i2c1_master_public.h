 /************************************************************************//**
 *@brief	i2c1_master.h for control of codec 
 *@version	V0.0
 *@date		15.04.2016
 *@author	cosinuss
 ****************************************************************************/

#ifndef I2C_MASTER_PUBLIC_H_
#define I2C_MASTER_PUBLIC_H_

/* Includes ----------------------------------------------------------------*/
#include "audiocodec_public.h"
#include <stdint.h>
#include <stdbool.h>
#include "app_error.h"
#include "sdk_errors.h"

/* Exported define ---------------------------------------------------------*/
 
/* Exported typedef --------------------------------------------------------*/
//for transmission to 
typedef enum {
	No_owner = 0,
	Audiocodec_reset,	//for reseting of codec to default state
	Audiocodec_repeat_write,	//to set the codec to repeat write state
	Audiocodec_init,	//for initialisation of codec
	Pll_srm_detect,		//to check if the codec PLL is set after initialization
	Audiocodec_enable,	//to enable codec for operation
	Audiocodec_i2s_start,	//to start codec operation
	Audiocodec_vol,		//for volume control
	Audiocodec_stand_by	//put the codec on standby mode
}Transmit_owner;
								
/* Exported variables ------------------------------------------------------*/

/* Exported functions ------------------------------------------------------*/

 /************************************************************************//**
 * configure i2c1 master.
 * @param[out] void  		  		
 * @param[in]  void    		
 * @retval     void 	
 ****************************************************************************/
void I2C1master_config(void);
							
  /***********************************************************************//**
 * Function to indicate all data has been sent	
 * @param[in]  id  - the owner of the call to the function      		
 * @retval     void	
 ****************************************************************************/
uint8_t audiocodec_pll_srm_lock(Transmit_owner owner_id);							
	
 /************************************************************************//**
 * Function to update the identity of the function using the i2c resource
 * @param[out] void  		
 * @param[in]  Owner_id  owner of the function which is using the i2c resource  		   		
 * @retval     void 	
 ****************************************************************************/														
void  Owner_Update (Transmit_owner Owner_id);

/*************************************************************************//**
 * Function to start I2C- it might be to start up device for codec configuration, i2s opertion or for volume control or for shut down purposes.
 * @param[out] void  		
 * @param[in]  ID 	accepts the id of the funtion that calls it 	  		
 * @param[in]  Number_of_Transfer	for more than one transfer    		
 * @retval     returns a true for a success and false for a faliure
 ****************************************************************************/
void  I2C1master_StartTX(Transmit_owner owner_id, bool Number_of_Transfer );

#endif	//I2C_MASTER_PUBLIC_H_

