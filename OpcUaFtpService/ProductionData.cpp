#include "ProductionData.hpp"

/* Method to simulate Production data input from future csv file (only for testing purpose) */
void ProductionData::TestInputData() {
    /* Input of ExampleInt */
    ExampleInt1 = 1;
    
    /* Input of ExampleString1 */
    ExampleString1 = "HelloExampleString1";

    /* Input of ExampleString2 */
    ExampleString2 = "HelloExampleString2";

    /* Input of ExampleString3 */
    ExampleString3 = "HelloExampleString3";
}

/* Method to clearing production Data structure */
void ProductionData::ClearData() {
    /* Clear example data */
    ExampleInt1 = 0;

    ExampleString1 = "";

    ExampleString2 = "";

    ExampleString3 = "";

}

void ProductionData::PrintDataToConsole()
{
    /* Print of Example integer 1 */
    std::cout << "\nExample integer 1: " << ExampleInt1;

    /* Print of Example string 1 */
    std::cout << "\nExample string 1: " << ExampleString1;

    /* Print of Example string 2 */
    std::cout << "\nExample string 2: " << ExampleString2;

    /* Print of Example string 3 */
    std::cout << "\nExample string 3: " << ExampleString3;

}
std::string ProductionData::PrintDataToFile()
{
    std::stringstream LogFile;

    /* Print of Example integer 1 */
    LogFile << "\nExample integer 1: " << ExampleInt1;

    /* Print of Example string 1 */
    LogFile << "\nExample string 1: " << ExampleString1;

    /* Print of Example string 2 */
    LogFile << "\nExample string 2: " << ExampleString2;

    /* Print of Example string 3 */
    LogFile << "\nExample string 3: " << ExampleString3;

    return LogFile.str();
}
/* Check whether Production Data structure is empty */
int ProductionData::IsEmpty()
{
    if (ExampleInt1 == 0 && ExampleString1 == "" && ExampleString2 == "" && ExampleString3 == "")
    {
        return 1;
    }
    else if(ExampleInt1 != 0 && ExampleString1 != "" && ExampleString2 != "" && ExampleString3 != "")
    {
        return 0;
    }
    else
    {
        return 999;
    }
}
void ProductionData::CopyData(ProductionData& InputData)
{
    ExampleInt1 = InputData.ExampleInt1;
    ExampleString1 = InputData.ExampleString1;
    ExampleString2 = InputData.ExampleString2;
    ExampleString3 = InputData.ExampleString3;
}