/* Definitions of class WriteDataToPLC members */
#pragma warning(disable : 4996)
#include "WriteDataToPLC.hpp"

/*
* Initialize connection with OPC UA Server
* @param: string server adress
* @return: Server initialization status code
*/
int WriteDataToPLC::InitOpcUaServerConnection(std::string ServerAdress, LoggingToTextFile& MessageFile) {

    MessageFile.AppendLog("InitOpcUaServerConnection function starting with server adress: " + ServerAdress, M_INFO);

    /* Convert server adress to c_tring */
    char* CstrServerAdress = new char[ServerAdress.length() + 1];
    strcpy_s(CstrServerAdress, ServerAdress.length() + 1, ServerAdress.c_str());

    client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));
    UA_StatusCode retval = UA_Client_connect(client, CstrServerAdress);

    /* Check server connection status */
    if (retval != UA_STATUSCODE_GOOD)
    {
        UA_Client_delete(client);
        // std::cout << "\nLog: OpcUa Server connection initialization failed code: " << (int)retval;
        MessageFile.AppendLog("OpcUa Server Connection Failed: " + to_string((int)retval), M_ERROR);

        /* Save server connection status */
        ServerConnectionStatus = (int)retval;
        return (int)retval;
    }
    else
    {
        //std::cout << "\nLog: OpcUa Server connection initialization successful: ";
        MessageFile.AppendLog("OpcUa Server connection initialization successful", M_INFO);
    }
    /* Save server connection status */
    ServerConnectionStatus = (int)retval;

    return 0;
}

/* Function to convert input std::String type to UA_String type
* @param: StrToConvert -> Input string to convert
* @param: StrConverted -> Output string converted
* @return: status of conversion
*/

void WriteDataToPLC::StringToUAString(std::string& StrToConvert, UA_String& StrConverted) {

    /* Write length of input string */
    StrConverted.length = StrToConvert.length();

    /* Define temp char's array */
    char* ConvertArray = new char[StrToConvert.length() + 1];
    UA_Byte* ConvertByteArray = new UA_Byte[StrToConvert.length() + 1];

    // copying the contents of the
    // string to char array
    strcpy_s(ConvertArray, StrToConvert.length() + 1, StrToConvert.c_str());

    for (int i = 0; i < StrToConvert.length(); i++) {
        ConvertByteArray[i] = (UA_Byte)(ConvertArray[i]);
    }
    StrConverted.data = ConvertByteArray;
}

int WriteDataToPLC::Write(ProductionData& Data, std::string ServerAdress, LoggingToTextFile& MessageFile) {

    /* Initialize server connection */
    //std::cout << "\LOG: InitOpcUaServerConnection function starting with server adress: " << ServerAdress;
    InitOpcUaServerConnection(ServerAdress, MessageFile);



    if (ServerConnectionStatus != UA_STATUSCODE_GOOD)
    {
        MessageFile.AppendLog("Cannot write data to PLC, wrong server connection status, : " + to_string(ServerConnectionStatus), M_ERROR);
        return ServerConnectionStatus;
    }
    else
    {
        int ret; /* Error code handler */
        /* Check condition of OpcUaServer */

        /*------------------- Example integer 1 --------------*/
        //std::cout << "\nAttempt to write example integer 1: " << Data.ExampleInt1 << std::endl;
        MessageFile.AppendLog("Attempt to write example integer 1: " + Data.ExampleInt1, M_INFO);

        UA_Int16 UaExampleInt1 = (UA_Int16)(Data.ExampleInt1); /* Write string variable */
        UA_Variant VariantExampleInt1; /* Variants can hold scalar values and arrays of any type */

        UA_Variant_init(&VariantExampleInt1);
        UA_Variant_setScalar(&VariantExampleInt1, &UaExampleInt1, &UA_TYPES[UA_TYPES_INT16]);

        /* NodeId of the variable holding the Example integer 1 */
        const UA_NodeId NodeExampleInt1 = UA_NODEID_STRING(3, (char*)"\"ProductionData\".\"ProductionData\".\"ExampleInt1\"");
        ret = UA_Client_writeValueAttribute(client, NodeExampleInt1, &VariantExampleInt1);

        //std::cout << "\nLOG: Example integer write result: " << (int)ret << std::endl;
        MessageFile.AppendLog("Example integer write result: " + to_string((int)ret), M_INFO);


        /*------------------- Example string 1 ----------------*/
        //std::cout << "\nAttempt to write example string 1: " << Data.ExampleString1 << " String length: " << Data.ExampleString1.length() << std::endl;
        MessageFile.AppendLog("Attempt to write example string 1: " + Data.ExampleString1, M_INFO);

        UA_String UaExampleString1; /* Write string variable */
        UA_Variant VariantExampleString1; /* Variants can hold scalar values and arrays of any type */

        /* Convert string data type to UA_String */
        StringToUAString(Data.ExampleString1, UaExampleString1);
        UA_Variant_init(&VariantExampleString1);
        UA_Variant_setScalar(&VariantExampleString1, &UaExampleString1, &UA_TYPES[UA_TYPES_STRING]);

        /* NodeId of the variable holding the example string 1 */
        const UA_NodeId ExampleString1NodeId = UA_NODEID_STRING(3, (char*)"\"ProductionData\".\"ProductionData\".\"ExampleString1\"");
        ret = UA_Client_writeValueAttribute(client, ExampleString1NodeId, &VariantExampleString1);

        //std::cout << "\nLOG: Example string 1 write result: " << (int)ret << std::endl;
        MessageFile.AppendLog("Example strin 1 write result: " + to_string((int)ret), M_INFO);


        /*------------------- Example string 2 ----------------*/
        //std::cout << "\nAttempt to write example string 2: " << Data.ExampleString2 << " String length: " << Data.ExampleString2.length() << std::endl;
        MessageFile.AppendLog("Attempt to write example string 2: " + Data.ExampleString2, M_INFO);

        UA_String UaExampleString2; /* Write string variable */
        UA_Variant VariantExampleString2; /* Variants can hold scalar values and arrays of any type */

        /* Convert string data type to UA_String */
        StringToUAString(Data.ExampleString2, UaExampleString2);
        UA_Variant_init(&VariantExampleString2);
        UA_Variant_setScalar(&VariantExampleString2, &UaExampleString2, &UA_TYPES[UA_TYPES_STRING]);

        /* NodeId of the variable holding the example string 2 */
        const UA_NodeId ExampleString2NodeId = UA_NODEID_STRING(3, (char*)"\"ProductionData\".\"ProductionData\".\"ExampleString2\"");
        ret = UA_Client_writeValueAttribute(client, ExampleString2NodeId, &VariantExampleString2);

        //std::cout << "\nLOG: Example string 2 write result: " << (int)ret << std::endl;
        MessageFile.AppendLog("Example string 2 write result: " + to_string((int)ret), M_INFO);

        /*------------------- Example string 3 ----------------*/
        //std::cout << "\nAttempt to write example string 3: " << Data.ExampleString2 << " String length: " << Data.ExampleString3.length() << std::endl;
        MessageFile.AppendLog("Attempt to write example string 3: " + Data.ExampleString3, M_INFO);

        UA_String UaExampleString3; /* Write string variable */
        UA_Variant VariantExampleString3; /* Variants can hold scalar values and arrays of any type */

        /* Convert string data type to UA_String */
        StringToUAString(Data.ExampleString3, UaExampleString3);
        UA_Variant_init(&VariantExampleString3);
        UA_Variant_setScalar(&VariantExampleString3, &UaExampleString3, &UA_TYPES[UA_TYPES_STRING]);

        /* NodeId of the variable holding the example string 3 */
        const UA_NodeId ExampleString3NodeId = UA_NODEID_STRING(3, (char*)"\"ProductionData\".\"ProductionData\".\"ExampleString3\"");
        ret = UA_Client_writeValueAttribute(client, ExampleString3NodeId, &VariantExampleString3);

        //std::cout << "\nLOG: Example string 3 write result: " << (int)ret << std::endl;
        MessageFile.AppendLog("Example string 3 write result: " + to_string((int)ret), M_INFO);


        /* Clean Up after OPC UA connections */
        CleanUp();

        return 0;
    }




}

/*
* Clean up after OPC UA client connection
* @param: NULL
* @return: NULL
*/

void WriteDataToPLC::CleanUp()
{
    UA_Client_delete(client);
}

/* Function only for manual test purpose
* @param: Production data
* @return: NULL
*/


