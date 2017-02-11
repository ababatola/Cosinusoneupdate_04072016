 /************************************************************************//**
 *@brief	i2c_master.c holds all I2C1 master functions that controls the codec
 *@brief	configured for only transmit function and master mode
 *@version	V0.0
 *@date		15.04.2016
 *@author	cosinuss
 ****************************************************************************/
 
/* Includes ----------------------------------------------------------------*/

#include "general_defination.h"
#include "audiocodec_public.h"
#include "i2c1_master_public.h"
#include "nrf52_bitfields.h"
#include "nrf52.h"
#include "nrf_drv_config.h"
#include <stdbool.h>
#include <stdint.h>
#include "nrf_drv_twi.h"
#include "app_error.h"
#include "nrf_twi.h"
#include "app_util_platform.h"

/* Private define ----------------------------------------------------------*/
#define	PIN3_I2C1_DATA	3	
#define	PIN4_I2C1CLOCK	4
#define MASTER1_INST	1	//I2C1 instance 1
#define BUFFER_SIZE_I2C	60
#define DEBUG_I2C_READ_BACK

/* Private function prototypes ---------------------------------------------*/
 /************************************************************************//**
 * handles a i2c1 master event. it is called at an interrupt event of the I2C1 operation
 * @param[out] void  		  		
 * @param[in]  void    		
 * @retval     void 	
 ****************************************************************************/
void event_handler_i2c1(nrf_drv_twi_evt_t const * p_event, void * p_context);


 /************************************************************************//**
 * p context of the transfer driver
 * @param[out] void  		  		
 * @param[in]  void    		
 * @retval     void 	
 ****************************************************************************/
void p_context(void);

/* Private typedef ---------------------------------------------------------*/

/* Private variables -------------------------------------------------------*/
uint8_t transmit_buffer[BUFFER_SIZE_I2C];	//I2C1 transmit buffer

//creation of an instance of the twi master
const nrf_drv_twi_t i2c1_master_instance = NRF_DRV_TWI_INSTANCE(MASTER1_INST);

//holds size of data to be transmitted
uint8_t data_size;
//variable that indicates the owner of an i2c transmit operation
static Transmit_owner owner;

//holds 1 for complete transfer and 0 for transfers no complete
static volatile bool data_transfer_complete;


/* Public functions --------------------------------------------------------*/
//??number of transfer is not been used in this case
void I2C1master_StartTX(Transmit_owner Owner_id, bool Number_of_transfer)
{
	ret_code_t ret =0;	//for error code
	data_transfer_complete = false;

	//update the new owner to the calling function
	Owner_Update(Owner_id);
	data_size = (audiocodec_transmit_data_i2c1(Owner_id, transmit_buffer));
	
	ret = nrf_drv_twi_tx(&i2c1_master_instance, CODEC_I2C_ADDRESS, &transmit_buffer[0],  data_size, true);	//false  true transmit_buffer,  data_size,
	APP_ERROR_CHECK(ret);
	while (data_transfer_complete == false);

	#ifdef DEBUG_I2C_READ_BACK
	//code below for read operation and for testing purposes
	data_transfer_complete = false;
	ret = 0;
	uint8_t rx_buffer [2]	= {0};	//buffer that contains byte received
	uint8_t	address_to_read[1] = {0x3};
	data_transfer_complete = 0;
	ret = 0;
	ret = nrf_drv_twi_tx(&i2c1_master_instance, CODEC_I2C_ADDRESS, &address_to_read[0],  1, false);	//false  true transmit_buffer,  data_size,
	APP_ERROR_CHECK(ret);
	while (data_transfer_complete == false);
	
	//actual read operation
	data_transfer_complete = false;
	ret = 0;
	ret = nrf_drv_twi_rx(&i2c1_master_instance, CODEC_I2C_ADDRESS, &rx_buffer[0],  1);	//false  true transmit_buffer,  data_size,
	APP_ERROR_CHECK(ret);
	while (data_transfer_complete == false);
	#endif 
	
	if (ret != NRF_SUCCESS)
	{
		data_transfer_complete = false;
		//add erroe codes here
	}		
}

uint8_t audiocodec_pll_srm_lock(Transmit_owner owner_id)
{
	ret_code_t ret = 0;
	data_transfer_complete = false;

	//update the new owner to the calling function
	Owner_Update(owner_id);
	data_size = (audiocodec_transmit_data_i2c1(owner_id, transmit_buffer));

	//wrtie to try to set SRM on lock state
	ret = nrf_drv_twi_tx(&i2c1_master_instance, CODEC_I2C_ADDRESS, &transmit_buffer[0],  data_size, true);	//false  true transmit_buffer,  data_size,
	APP_ERROR_CHECK(ret);
	while (data_transfer_complete == false);
	
	//commence read operation
	data_transfer_complete = false;
	ret = 0;
	uint8_t rx_buffer[1]	= {0};	//buffer that contains byte received
	uint8_t	address_to_read[1] = {0x3};
	
	//read operation, starts with write access, the register address
	data_transfer_complete = 0;
	ret = 0;
	ret = nrf_drv_twi_tx(&i2c1_master_instance, CODEC_I2C_ADDRESS, &address_to_read[0],  1, false);
	APP_ERROR_CHECK(ret);
	while (data_transfer_complete == false);
	
	//actual read operation
	data_transfer_complete = false;
	ret = 0;
	ret = nrf_drv_twi_rx(&i2c1_master_instance, CODEC_I2C_ADDRESS, &rx_buffer[0],  1);	//false  true transmit_buffer,  data_size,
	APP_ERROR_CHECK(ret);
	while (data_transfer_complete == false);
	return (rx_buffer[0]);
}
 void I2C1master_config(void )
{
	ret_code_t error_code;
	const nrf_drv_twi_config_t i2c1_config =	//configure I2C driver
    {
			.scl = PIN4_I2C1CLOCK,
			.sda = PIN3_I2C1_DATA,
			.frequency = NRF_TWI_FREQ_400K,
			.interrupt_priority = APP_IRQ_PRIORITY_MID
		};
		error_code = nrf_drv_twi_init(&i2c1_master_instance, &i2c1_config, event_handler_i2c1, NULL);
		APP_ERROR_CHECK(error_code);
		nrf_drv_twi_enable(&i2c1_master_instance);
}

void Owner_Update (Transmit_owner Owner_id)
{
	owner = Owner_id;
}
/* Private functions --------------------------------------------------------*/
void event_handler_i2c1(nrf_drv_twi_evt_t const  * p_event, void * p_context)	//handles interrupt event of the I2C1
{
	switch (p_event->type)
	{
		case (NRF_DRV_TWI_EVT_DONE):
		{
			data_transfer_complete = true;
			if (owner == Audiocodec_vol)
			{
				
			}										
		}
		break;
		case (NRF_DRV_TWI_EVT_ADDRESS_NACK):
		{
			
		}
		break;
		case(NRF_DRV_TWI_EVT_DATA_NACK):
		{
			//if (i2c_master_event->error_src = )
		}
		break;			
	}
	Owner_Update (No_owner);	//reconcile with fault condition 
}

void p_context()
{
	
}