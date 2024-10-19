#include<iostream>

#include "Settings.hpp"
#include "FtpReadProductionData.hpp"
#include "ProductionData.hpp"
#include "WriteDataToPLC.hpp"

/* Function for detecting   */
void DetectDataChangesOnFtp(ProductionData& DataFromFtpServer, ProductionData& DataCurrentlyOnPlc, LoggingToTextFile& MessageFile, WriteDataToPLC& PLC);
