#ifndef BLINK_H
#define BLINK_H

#include <cstdint>
#include <string>

#include "../module.h"
#include "../../drivers/pin/pin.h"

void createBlink(void);

class Blink : public Module
{

	private:

		bool 		bState;
		uint32_t 	periodCount;
		uint32_t 	blinkCount;

		Pin *blinkPin;	// class object members - Pin objects

	public:

		Blink(std::string, uint32_t, uint32_t);

		virtual void update(void);
		virtual void slowUpdate(void);
};

#endif
