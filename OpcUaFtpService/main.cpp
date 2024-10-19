#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread>
#include <mutex>

#include "FtpThreadListening.hpp"
#include "ProductionData.hpp"
#include "DataChangesOnFtpControl.hpp"
#include "Logging.hpp"
#include "Settings.hpp"
#include "WriteDataToPLC.hpp"

//Final version

int main()
{
	std::mutex Mlock;

	/* Create general program folder */
		/* Create new local folder if doesn't exist */
	if (CreateDirectory(ROOT_PATH, NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		if (ERROR_ALREADY_EXISTS != GetLastError())
		{
			cout << "\nLog: New folder created: " << ROOT_PATH;
		}
	}
	else
	{
		cout << "\nLog: Fail during folder creation";
	}
	/* Declare object responsible for writing data on PLC */
	WriteDataToPLC PLC;

	/* Declare production data structure instance wchich is receiving from external server */
	ProductionData DataFromFtpServer, DataCurrentyOnPlc;

	/* Create text file logging object */
	LoggingToTextFile MessageFile(LOGGING_PATH);

	/* Log print Examples */
	MessageFile.AppendLog("Program is starting",M_INFO);

	/* Clear Declared Production Data */
	DataFromFtpServer.ClearData();
	DataCurrentyOnPlc.ClearData();

	//this_thread::sleep_for(50000ms);

	/* Create FTP Read Production Thread */
	std::thread FtpListener(FtpListeningThread, std::ref(DataFromFtpServer), std::ref(Mlock), std::ref(MessageFile));

	/* Endless loop for testing */
	while (true)
	/* Detecting changes on input from FTP */
	{
		Mlock.lock();
		DetectDataChangesOnFtp(DataFromFtpServer, DataCurrentyOnPlc, MessageFile, PLC);
		Mlock.unlock();

	}

	/* Wait for end thred jobs */
	FtpListener.join();

	return 0;

}
