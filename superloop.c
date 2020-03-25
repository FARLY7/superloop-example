// timeMilliseconds is written to by the timer interrupt, nothing else.
// Any of the event handlers can read from it to get the current time.
uint32_t timeMilliseconds = 0;

// Events
bool timerEvent = false;
bool event2 = false;
bool event3 = false;
bool event4 = false;
bool event5 = false;
// etc...

interrupt timerInterrupt(void) {
	disableInterrupts();
	
	timeMilliseconds++;
	timerEvent = true;
	
	enableInterrupts();
}

void initializeClock(void) {
	// configure timer peripheral to call the timerInterrupt every 1ms.
}

int main(void) {

	initializeClock();
	initializePeripheral2();
	initializePeripheral3();
	// etc...
	
	// This is an example of the "Super Loop" pattern.
	while (1) {
	
		// If you want to limit how often an event can occur, put it within this block.
		if (timerEvent) {
			timerEvent = false;
			
			// since there must be a timerEvent for this condition to be checked, handleEvent4() will not be called more than once per millisecond.
			if (event4) {
				event4 = false;
				handleEvent4();
			}
			
			// This is an example of how you can have time-based events.
			// e.g. event5 will only be checked once every 10 ms.
			if (event5 && (timeMilliseconds % 10 == 0) {
				event5 = false;
				handleEvent5();
			}
		}
		
		// Since event2 doesn't require a timerEvent, it could be run as frequently as the processor runs through the main loop. 
		// This could be useful if you want to respond to events that come in more often than the timerEvent occurs, or if
		// you want to respond to something with lower latency than it would take to wait for the next timerEvent.
		if (event2) {
			event2 = false;
			handleEvent2();
		}
		
		if (event3) {
			event3 = false;
			handleEvent3();
		}
		
		// Pause the processor to save power. Configure it so that it will wake up again when any interrupt occurs.
		// If there's no other activity, it will be woken up by the next timer interrupt less than 1ms from now.
		sleep(); 
	}
	
	return 0; // will never return
}
