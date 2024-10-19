#include "DataChangesOnFtpControl.hpp"

void DetectDataChangesOnFtp(ProductionData& DataFromFtpServer, ProductionData& DataCurrentlyOnPlc, LoggingToTextFile& MessageFile, WriteDataToPLC& PLC)
{
	/* Detecting moment of incoming data */
	if (DataFromFtpServer.IsEmpty() == 0 && DataCurrentlyOnPlc.IsEmpty() == 1)
	{
		//cout << "\nNew production data arrived: " << endl;
		MessageFile.AppendLog("New production data arrived", M_INFO);
		DataCurrentlyOnPlc.CopyData(DataFromFtpServer);

		DataCurrentlyOnPlc.PrintDataToConsole();
		MessageFile.AppendLog(DataCurrentlyOnPlc.PrintDataToFile(), M_INFO);

		/* Write data to PLC */
		if (PLC.Write(DataCurrentlyOnPlc, OPC_SERVER_ADRESS, MessageFile))
		{
			MessageFile.AppendLog("Data has not been written to PLC", M_ERROR);
		}
		else
		{
			MessageFile.AppendLog("Data has been written to PLC", M_INFO);
		}
	}
	else if (DataFromFtpServer.IsEmpty() == 1 && DataCurrentlyOnPlc.IsEmpty() == 0)
	{
		//cout << "\nProduction data cleared: " << endl;
		DataCurrentlyOnPlc.ClearData();

		DataCurrentlyOnPlc.PrintDataToConsole();
		MessageFile.AppendLog(DataCurrentlyOnPlc.PrintDataToFile(), M_INFO);

		/* Write data to PLC */
		if (PLC.Write(DataCurrentlyOnPlc, OPC_SERVER_ADRESS, MessageFile))
		{
			MessageFile.AppendLog("Data has not been written to PLC", M_ERROR);
		}
		else
		{
			MessageFile.AppendLog("Data has been written to PLC", M_INFO);
		}
	}
}