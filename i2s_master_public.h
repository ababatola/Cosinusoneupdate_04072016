 /************************************************************************//**
 *	@brief		i2s.h holds data variables and function name for the i2s function of the soc
 *	@version 	V0.0
 *	@date		06.04.2016
 *	@author		cosinuss
 ****************************************************************************/
/* The I2S configures the slave and master I2S chips and also handles all I2S related operation*/

#ifndef I2S_MASTER_PUBLIC_H_
#define I2S_MASTER_PUBLIC_H_

/* Includes ----------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "nrf52_bitfields.h"
#include "nrf52.h"

/* Exported define ---------------------------------------------------------*/
 
/* Exported typedef --------------------------------------------------------*/

/* Exported variables ------------------------------------------------------*/


/* Exported functions ------------------------------------------------------*/
 /************************************************************************//**
 * starts i2s transmission
 * @param[out] void  		
 * @param[in]  void  		   		
 * @retval     void 	
 ****************************************************************************/
void I2Smaster_startTransmit(void);

 /************************************************************************//**
 * Function initialization and configuration of the i2s module
 * @param[out] void  		
 * @param[in]  void  		    		
 * @retval     void 	
 ****************************************************************************/
void I2Smaster_config(void);
#endif //I2S_MASTER_PUBLIC_H_