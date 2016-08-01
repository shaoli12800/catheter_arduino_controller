#pragma once
#ifndef SIMPLE_THREAD_H
#define SIMPLE_THREAD_H

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "ser/serial_sender.h"
#include "gui/status_text.h"
#include "gui/status_frame.h"


// This class acts a thread manager for offloading the serial communication. (high-level)
// Prevents gui hangs.
class SerialThreadObject
{
public:
	
	SerialThreadObject();
	void setStatusTextPtr(CatheterStatusText*);
	void setStatusGrid(StatusGrid* );

	
enum ThreadCmd {
		noCmd = 0, resetArduino = -2, resetSerial = -1, poll  = 1, connect, disconnect
	};
enum ThreadStatus{
		ready, error
	};

	~SerialThreadObject();

	// status commands
	void queueCommands(const std::vector< CatheterChannelCmdSet > &, bool = false);

	void queueCommand(const CatheterChannelCmdSet &, bool = false);

	/*
	 * @brief: This function is for sending data back to the gui window probably useless for now
	 */
	void getResponse(); 

	/*
	 * @brief: This sends a command to the  loop thread
	 */
	void serialCommand(const ThreadCmd&);
	
	void stopThreads();

	void restartThread();

private:

	ThreadCmd incomingCommand;
	ThreadStatus currentStatus;

	boost::mutex threadMutex;

	boost::thread thrd;  // by default, this is the thread object (it will run the serial Data object)


	// This is the loop function
	// (The meat of where stuff happens)
	void serialLoop();  

	// serial data.
	bool active; 

	bool connected;

    // serial connection
    CatheterSerialSender* ss;

    //
	std::vector< CatheterChannelCmdSet > commandsToArd;
	CatheterChannelCmdSet commandFromArd;


	// gui handles
	CatheterStatusText* textStatus;
	StatusGrid* gridStatus;
};













#endif