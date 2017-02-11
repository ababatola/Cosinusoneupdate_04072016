 /************************************************************************//**
 *	@brief		audiocodec_config.h holds defination for the audiocodec function of the soc
 *	@detailed 
 *	@version	V0.0
 *	@date		11.04.2016
 *	@author		cosinuss
 ****************************************************************************/
 
#ifndef AUDIOCODEC_CONFIG_H_
#define AUDIOCODEC_CONFIG_H_

/* Includes ----------------------------------------------------------------*/
#include "audiocodec_public.h"
#include "general_defination.h"
#include "nrf.h"
#include <stdlib.h>
#include <stdint.h>

/* define ------------------------------------------------------------------*/
//defination of the address of the various registers of the audio codec DA7212
#define	PLL_STATUS_ADD		0x03	//PLL status address
#define	MIXOUT_R_CTRL_ADD	0x6f	//Right mixer out control address
#define MIXOUT_L_CTRL_ADD	0x6e	//Left mixer out control address
//the next three registers are not listed in the listing of the device registers they are used for the set up of the PLL and clocking of the device
#define	DUMMY_CLOCK_CONFIG1_ADD	0xf0
#define	DUMMY_CLOCK_CONFIG2_ADD	0xf1
#define	DUMMY_CLOCK_CONFIG3_ADD	0xf0
#define	CP_VOL_THRESHOLD1_ADD	0x95	//Charge pump voltage threshold value
#define	CP_DELAY		0x96	//Charge pump delay
#define CIF_CTRL_ADD		0x1d	//Register Reset and I2C Write Mode
#define	DIG_ROUTING_DAI_ADD	0x21	//data select for DAI right output and dai data input
#define SR_ADD			0x22	//Sampling Rate
#define	SYSTEM_ACTIVE_ADD	0xFD	//System Active State
#define GAIN_RAMP_CTRL_ADD	0x92	//Mixer Gain Ramp
#define	LDO_CTRL_ADD		0x90	//LDO Control
#define CP_CTRL_ADD		0x47		//Charge Control
#define	HP_L_GAIN_ADD		0x48	//Left Headphone Amplifier Gain
#define	HP_R_GAIN_ADD		0x49	//Right Headphone Amplifier Gain
#define	LINE_GAIN_ADD		0x4a	//Line Speaker Amplifier
#define	MIXOUT_R_SELECT_ADD	0x4c	//Right Amplifier Mixer
#define MIXOUT_L_SELECT_ADD	0x4b	//Left Amplifier Mixer
#define	SYSTEM_MODES_O_ADD	0x51	//System Mode
#define	REFERENCES_ADD		0x23		//Refences
#define PLL_FRAC_TOP_ADD	0x24		//PLL Top Fraction
#define PLL_FRAC_BOTTOM_ADD	0x25	//PLL Bottom Fraction
#define PLL_INTEGER_ADD		0x26		//PLL Integer part
#define PLL_CTRL_ADD		0x27q			//PLL Control
#define	DAI_CLK_MODE_ADD	0x28		//Digital Audio Interface Clock Mode
#define	DAI_CTRL_ADD		0x29			//Digital Audio Interface Control
#define DIG_ROUTING_DAC_ADD	0x2a	//Digital Routing 
#define	HP_R_CTRL_ADD		0x6c			//Left Headphone Control
#define	HP_L_CTRL_ADD		0x6b			//Right Headphone Control
#define	LINE_CTRL_ADD		0x6d			//Line Speaker Control
#define	DAC_FILTERS4_ADD	0x43		//DAC Filter4
#define	DAC_FILTERS1_ADD	0x44		//DAC Filter1
#define	DAC_L_GAIN_ADD		0x45		//Left DAC Gain
#define	DAC_R_GAIN_ADD		0x46		//Right DAC Gain
#define	DAC_L_CTRL_ADD		0x69		//Left DAC Control
#define	DAC_R_CTRL_ADD		0x6a		//Right DAC Control


#define	DUMMY			0x00
//defination of various command write codes that is written to the audio CODEC
#define CODEC_RESET_COMMAND	0x80	//Codec reset command data
#define CODEC_I2SWRITE_REPEAT_MODE	0x01	//Codec command data for repeat mode
#define CODEC_I2START_COMMAND	0x01	//Codec start command data
#define CODEC_I2STOP_COMMAND	0x00	//Codec stop command data
#define	PLL_CTRL_ENABLE_COMMAND	0xC0	//PLL enable command data

//defination of the audio CODEC PLL parameter values
//values calculated for the device specification of 4000Hz
#define PLL_FRAC_TOP_VALUE	0x12	
#define PLL_FRAC_BOTTON_VALUE	0x6e
#define	PLL_INTEGER		0x18

//defination of the audio codec volume initial gain values
#define	MAX_AMP_GAIN		0x3f	//at 6db
#define	MIN_AMP_GAIN		0x0	//at 6db

//#define RIGHT_VOLUME(x)			(x)
//#define LEFT_VOLUME(x)			(x)
//#define RIGHT_VOLUME_DEC(x)			(x)
//#define LEFT_VOLUME_DEC(x)			(x)

/* typedef -----------------------------------------------------------------*/
//structure to that holds the parameters for the audio codec registers
//this values are used to configure the audio codec
typedef struct 
{
	uint8_t	dummy_clock_config1;	//write values for 3 dummy registers
	uint8_t	dummy_clock_config2;
	uint8_t	dummy_clock_config3;
	uint8_t cp_vol_threshold1;	//Charge pump threshold
	uint8_t	cp_delay;					//Charge pump delay
	uint8_t	cp_ctrl;					//Charge pump control value
	uint8_t	ldo_ctrl;					//LDO control value
	uint8_t sr;								//Sampling rate value
	uint8_t	references;				//For Codec reference capacitors
	uint8_t	pll_frac_top;			//PLL fraction numerator value
	uint8_t	pll_frac_buttom;	//PLL fraction denominator value
	uint8_t pll_integer;			//PLL integer value	
	uint8_t pll_ctrl;					//PLL switch on and control function
	uint8_t dai_ctrl;					//Digitala analogue interface configuration
	uint8_t dig_routing_dai;	//Digitala routing configuration
	uint8_t mixout_l_select;	//Left amplifier mixer value in db
	uint8_t mixout_r_select;	//Right amplifier mixer value in db
	uint8_t gain_ramp_ctrl;	//Gain of codec ramp
	uint8_t	system_mode;	//Device system mode
	uint8_t hp_l_gain;	//Left headphones gain value
	uint8_t hp_r_gain;	//Right headphones gain value
}config_structure_t;

//structure that contains all details of data been sent out via i2s
//the informations stored keeps track of the data been sent via the i2s
typedef struct
{
	uint8_t buffer_moved_cou;	//number of buffers moved already
	//this is erratic
	uint8_t buffer_moved_max;	//maximum number of buffers to be moved
	uint16_t buffer_size;		//buffer size, dynamic cos it is always changing
	uint8_t data_sample_cou;	//counter for data samples that has been moved might not be needed
	uint8_t data_samples_max;	//maximum number of data sample to be moved
	uint16_t data_sample_index_cou;	//counter for data sample array index been moved
	uint32_t total_data_sample_size;//total number of data sample to be moved ?? might not be needed
	uint32_t total_data_moved_data_cou;//back up to monitor data for exit of moving of data out to the codec
	uint16_t data_size[20];	//holds number of each data sample that forms part of the whole data to be sent out by i2s ?? perfect this line
}i2s_data_structure_t;

#endif //AUDIOCODEC_CONFIG_H