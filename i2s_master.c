 /************************************************************************//**
 *	@brief		i2s.c holds data variables and function name for the i2s function of the soc
 *	@brief		master mode, 16bit mono channel, 16khz sample rate, left allignment and left channel
 *	@brief		used for sending of data to the codec chip
 * 	@version 	V0.0
 * 	@date	  	06.04.2016
 *	@author 	cosinuss
 ****************************************************************************/

/* Includes ----------------------------------------------------------------*/
#include "i2s_master_public.h"
#include "audiocodec_public.h"
#include "i2c1_master_public.h"
#include "general_defination.h"
#include "app_error.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "nrf52_bitfields.h"
#include "nrf52.h"
#include "nrf_drv_i2s.h"
#include "app_util_platform.h"

/* Private define ----------------------------------------------------------*/

#define	PRODUCT_DEVELOPMENT	//define for testing purposes
#define MAX_BUFFER_SIZE	2000	//size of the I2S buffer
#ifdef PRODUCT_DEVELOPMENT

	#define I2S_MCLK_PORT 8	//port for master clock of the i2s
	#define I2S_WCLK_PORT 6	//port for word clock of the i2s
	#define I2S_DATAOUT_PORT 7	//port for i2s master data out and slave data in
	#define I2S_DATAIN_PORT 9	//port for i2s master data in and slave data out
	#define I2S_BCLK_PORT 5	//port for serial clock for the i2s

#else
	#define I2S_MCLK_PORT 2	//port for master clock of the i2s
	#define I2S_WCLK_PORT 5	//port for word clock of the i2s
	#define I2S_DATAOUT_PORT 6	//port for i2s master data out and slave data in
	#define I2S_BCLK_PORT 7	//port for serial clock for the i2s
#endif

/* Private variables -------------------------------------------------------*/
static uint16_t data_amount;	//number of datas in the sample been transmitted by the i2s, always twice the size of the actual data
static uint32_t transmit_buffer[I2S_DATA_SIZE *2];	//transmit buffer must be always more than data amount
static uint8_t  pll_srm_lock_result;
/* Private function prototypes ---------------------------------------------*/
 
 /************************************************************************//**
 * Event handler - handles data event for the i2s data transfer		  		
 * @param[in]  void  
 * @param[in]  p_data_to_send 
 * @param[in]  number_of_data  
 * @retval     void 	
 ****************************************************************************/
 static void data_handler(uint32_t const * null,
                         uint32_t       * p_data_to_send,
                         uint16_t         number_of_data);

/* Private typedef ---------------------------------------------------------*/


/* Public functions --------------------------------------------------------*/

void I2Smaster_config( )
{
	bool result = 1;
	pll_srm_lock_result	= 	0;
	uint32_t err_code = NRF_SUCCESS;
	nrf_drv_i2s_config_t config = NRF_DRV_I2S_DEFAULT_CONFIG;
	// configured in i2s format
	config.sck_pin = I2S_BCLK_PORT;		//select SoC pin for bit clock
	config.lrck_pin = I2S_WCLK_PORT;	//select SoC pin for word clock
	config.mck_pin = I2S_MCLK_PORT;		//select SoC pin for master clock
	config.sdout_pin = I2S_DATAOUT_PORT;	//select SoC pin for data
	config.irq_priority = APP_IRQ_PRIORITY_MID;
	config.alignment = NRF_I2S_ALIGN_LEFT;	//select data aligment to left
	
	#ifdef MONO_MODE
	config.channels	= NRF_I2S_CHANNELS_LEFT;	//configure as left channel
	#else
	config.channels = NRF_I2S_CHANNELS_STEREO;	//configure as stereo
	#endif
	
	config.ratio = NRF_I2S_RATIO_512X;			//divide by 512 to have a sampling of 8KHz
	config.mck_setup = NRF_I2S_MCK_32MDIV8;	//set master clock to for 4MHz 
	err_code = nrf_drv_i2s_init(&config, data_handler);
	APP_ERROR_CHECK(err_code);
	
	if (err_code != NRF_SUCCESS)
		{
			result = 0;
			//inlcude codes for error purposes
		}
}

void  I2Smaster_startTransmit( )
{
	audiocodec_i2s_data_prep();	//modified cos below was removed from it
	I2C1master_StartTX(Audiocodec_i2s_start, false);			//enable codec
	audiocodec_i2s_start_transmit_data(transmit_buffer, &data_amount);	//call function to initialise the i2s data
	uint32_t err_code = NRF_SUCCESS;
	err_code = nrf_drv_i2s_start(NULL, transmit_buffer, data_amount, 0);	//transmit only mode
	APP_ERROR_CHECK(err_code);
	if ((err_code) != 0)
	{
		uint8_t abc;
	}

//check is there is pll srm lock
	while ((pll_srm_lock_result != 0x07))
	{
		pll_srm_lock_result = (audiocodec_pll_srm_lock (Pll_srm_detect));
	}	
}

/* Private functions -------------------------------------------------------*/
void data_handler(uint32_t const * null,
                  uint32_t       * p_data_to_send,
                  uint16_t         number_of_data)
{
	// Non-NULL value in 'p_data_received' indicates that a new portion of
	// data has been received and should be processed.
	//if (p_data_received != NULL)
	{
		
	}
    // Non-NULL value in 'p_data_to_send' indicates that the driver needs
    // a new portion of data to send.
	if (p_data_to_send != NULL)
		{
			audiocodec_transmitdata_update_i2s(p_data_to_send, number_of_data);
		//inlcude end code here
		}	
}