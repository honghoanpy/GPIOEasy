/* Includes ------------------------------------------------------------------*/
#include <Arduino.h>
#include "timeout.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private global variables --------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
 * @brief Set begin value, timeout value.
 * @param None
 * @retval None
 */
void TimeOut::Update(uint32_t TO_val) {
	_Status=TO_ENABLE;
	_timeWait=TO_val;
	_timeStart=millis();
}

/**
 * @brief Disable timeout.
 * @param None
 * @retval None
 */
void TimeOut::Disable(void){
	_Status=TO_DISABLE;
	_timeWait=0;
	_timeStart=0;
}
/**
 * @brief Check is timeout
 * @param None
 * @retval 1: Timeout    |   0: Not timeout
 */
uint8_t TimeOut::Expired(void){
	if((_Status==TO_ENABLE) && ((millis()-_timeStart) > _timeWait)) {
		_Status=TO_DISABLE;
		return 1;  // timeout
	}
	return 0;  // Not timeout
}

/**
 * @brief Get value timeout
 * @param None
 * @retval Timer value
 */
uint32_t TimeOut::Remain(void) {
	if(_Status==TO_ENABLE) {
		if((millis()-_timeStart) < _timeWait) {
			return _timeWait - (millis()-_timeStart);
		}
	}
	return 0;
}

/**
 * @brief Set begin value, timeout value.
 * @param None
 * @retval None
 */
void usTimeOut::Update(uint32_t TO_val) {
	_Status=TO_ENABLE;
	_timeWait=TO_val;
	_timeStart=micros();
}

/**
 * @brief Disable timeout.
 * @param None
 * @retval None
 */
void usTimeOut::Disable(void){
	_Status=TO_DISABLE;
	_timeWait=0;
	_timeStart=0;
}
/**
 * @brief Check is timeout
 * @param None
 * @retval 1: Timeout    |   0: Not timeout
 */
uint8_t usTimeOut::Expired(void){
	if((_Status==TO_ENABLE) && ((micros()-_timeStart) > _timeWait)) {
		_Status=TO_DISABLE;
		return 1;  // timeout
	}
	return 0;  // Not timeout
}

/**
 * @brief Get value timeout
 * @param None
 * @retval Timer value
 */
uint32_t usTimeOut::Remain(void) {
	if(_Status==TO_ENABLE) {
		if((micros()-_timeStart) < _timeWait) {
			return _timeWait - (micros()-_timeStart);
		}
	}
	return 0;
}
/************************* End of File ****************************************/

