 /************************************************************************//**
 *	@brief		audiocodec.h holds data variables and function name for the audio codec
 *	@version	V0.0
 *	@date		11.04.2016
 *	@author	cosinuss
 ****************************************************************************/

#ifndef AUDIOCODEC_PUBLIC_H_
#define AUDIOCODEC_PUBLIC_H_

/* Includes ----------------------------------------------------------------*/
#include <stdint.h>
#include "nrf52_bitfields.h"
#include "nrf52.h"
#include "nrf_drv_twi.h"
#include "nrf_twi.h"
#include "i2c1_master_public.h"

/* Exported define ---------------------------------------------------------*/
//defination of register address for the da7212 codec
#define	CODEC_I2C_ADDRESS 0x1a
#define INCREASE_VOLUME 0x1
#define DECREASE_VOLUME 0x0

/* Exported typedef --------------------------------------------------------*/

/* Exported variables ------------------------------------------------------*/

/* Exported functions ------------------------------------------------------*/

 /************************************************************************//**
 * Function initialization and configuration of codec.
 * @param[out] void  			
 * @param[in]  void    		
 * @retval     void	
 ****************************************************************************/
void audiocodec_config(void);

 /************************************************************************//**
 * Function to update the transmit buffer of the i2c master.
 * @param[out] transmit_buffer_I2C  - transmit buffer address of the 12c
 * @param[in]  id  - the owner of the call to the function  
 * @retval     datasize  - is the size of data to be sent to via the i2c interface to the codec 	
 ****************************************************************************/
uint8_t audiocodec_transmit_data_i2c1(Transmit_owner owner_id, uint8_t *transmit_buffer_I2C);

 /************************************************************************//**
 * Function to update the transmit buffer of the i2S master.
 * @param[out] transmit_buffer_I2S  - transmit buffer address of the 12c
 * @param[out] number_of_words  		- data size to be transmitted
 * @param[out] *buffer_size				  - to update the buffer size
 * @param[in]  data_number
 * @retval     datasize  - is the size of data to be sent to via the i2c interface to the codec 	
 ****************************************************************************/
void audiocodec_transmitdata_update_i2s(uint32_t * p_buffer, uint16_t number_of_words);  //, uint16_t	*buffer_zise

 /************************************************************************//**
 * Function to start a typical i2s audio session		
 * @param[in]  void    		
 * @retval     void	
 ****************************************************************************/
void audiocodec_i2s_data_prep(void);

 /************************************************************************//**
 * Function to stop a typical i2s audio session		
 * @param[in]  void    		
 * @retval     void	
 ****************************************************************************/
 //i might not need this
void audiocodec_stop_i2s(void);

 /************************************************************************//**
 * Function to indicate all data has been sent	
 * @param[in]  void    		
 * @retval     void	
 ****************************************************************************/
void audiocodec_i2s_end(void); 
  /***********************************************************************//**
 * Function to set first set of data to be transmitted by the i2c master
 * @param[in]  void  
 * @param[in]  void  
 * @retval     void	
 ****************************************************************************/
void audiocodec_i2s_start_transmit_data(uint32_t *i2s_data_transmit, uint16_t *i2s_data_size);

  /***********************************************************************//**
 * Function to increase or decrease volume of the devie
 * @param[in]  void  
 * @param[in]  uint8_t	- 1 for increase volume and 0 to reduce volume  
 * @retval     void	
 ****************************************************************************/
void audiocodec_volume_control(uint8_t);
#endif //AUDIOCODEC_PUBLIC_H_
