#ifndef __TIMEOUT_H
#define __TIMEOUT_H
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
/* Public define ------------------------------------------------------------*/
#define TO_DISABLE 		0
#define TO_ENABLE		1

/* Public typedef -----------------------------------------------------------*/

/* Class --------------------------------------------------------------------*/
class TimeOut
{
	public:
	/*Default use*/ 
	TimeOut(uint32_t ToWait=0):_timeWait(ToWait) {
		Update(_timeWait);
	};
	/*Update timeout*/
	void Update(uint32_t TO_val);
	/*Stop timeout*/
	void Disable(void);
	/*Check timeout*/
	uint8_t Expired(void);
	/*Get timecount from time start*/
	uint32_t Passed(void);
	
	private:
	/*Start timestamp*/
	uint32_t _timeStart;
	/*Wait time from start timestamp*/
	uint32_t _timeWait;
	/*Status timeout counter*/
	uint8_t	_Status;
};

class usTimeOut
{
	public:
	/*Default use*/ 
	usTimeOut(uint32_t ToWait=0):_timeWait(ToWait) {
		Update(_timeWait);
	};
	/*Update timeout*/
	void Update(uint32_t TO_val);
	/*Stop timeout*/
	void Disable(void);
	/*Check timeout*/
	uint8_t Expired(void);
	/*Get time from timer restart*/
	uint32_t Passed(void);
	
	private:
	/*Start timestamp*/
	uint32_t _timeStart;
	/*Wait time from start timestamp*/
	uint32_t _timeWait;
	/*Status timeout counter*/
	uint8_t	_Status;
};

#endif /* __TIMEOUT_H */
/************************* End of File ****************************************/

