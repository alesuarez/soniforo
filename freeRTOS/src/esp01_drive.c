#include "esp01_drive.h"

#define MAX_COMMAND_LENGHT	 45

typedef enum CommandEsp8266 {
	ESP_SEND_AT,
	ESP_SEND_RST,
	ESP_SEND_ATE0,
	ESP_SEND_CWMODE_1,
	ESP_SEND_CWMODE_2,
	ESP_SEND_CWSAP,
	ESP_SEND_CWDHCP_0_1,
	ESP_SEND_CWDHCP_1_1,
	ESP_SEND_CIPSTART,
	ESP_SEND_CIPSEND,
	ESP_SEND_CIPMUX_1,
	ESP_SEND_CIPDINFO_1,
	ESP_SEND_CWAUTOCONN_0
} CommandEsp8266_t;

static const char CommandEsp8266ToString[][MAX_COMMAND_LENGHT] = {
		"AT\r\n",
		"AT+RST\r\n",
		"ATE0\r\n",
		"AT+CWMODE=1\r\n",
		"AT+CWMODE=2\r\n",
		"AT+CWSAP=\"Soniforo_CIAA\",\"\",10,0\r\n",
		"AT+CWDHCP=0,1\r\n",
		"AT+CWDHCP=1,1\r\n",
		"AT+CIPSTART=\"UDP\",\"0\",0,4096,2\r\n",
		"AT+CIPSEND=4,8\r\n",
		"AT+CIPMUX=1\r\n",
		"AT+CIPDINFO=1\r\n",
		"AT+CWAUTOCONN=0\r\n"
};

static char esp01Responses[][MAX_COMMAND_LENGHT] = {
		"AT\r\n",
		"OK\r\n",
		"ATE0\r\n",
		"\r\nOK\r\n",
		"AT+CWMODE=2\r\n",
		"CWSAP=\"Soniforo_CIAA\",\"\",10,0\r\n",
		"CWDHCP=0,1\r\n",
		"CWDHCP=1,1\r\n",
		"CIPSTART=3,\"UDP\",\"0\",0,4096,2",
		">>",
		"OK\r\n",
		"OK\r\n",
		"OK\r\n"

};

static bool_t sendCmd( uint8_t);
static bool_t cmdToEsp01( uint8_t);
static void rst();



bool_t esp01Init() {

	uartConfig(ESP01_UART, ESP01_BAUD_RATE);
	//stdioPrintf(ESP01_UART, CommandEsp8266ToString[ESP_SEND_AT]);
	//rst();

	//sendCmd(ESP_SEND_AT);
	//sendCmd(ESP_SEND_ATE0);
	//sendCmd(ESP_SEND_CWMODE_1);
	/*sendCmd(ESP_SEND_CIPMUX_1);
	sendCmd(ESP_SEND_CIPDINFO_1);
	sendCmd(ESP_SEND_CWAUTOCONN_0);
	sendCmd(ESP_SEND_CWDHCP_1_1);
	delay(500);*/

	return TRUE;
}

bool_t initAP() {
	bool_t retVal = FALSE;
	sendCmd(ESP_SEND_CWMODE_2);
	sendCmd(ESP_SEND_CWSAP);
	sendCmd(ESP_SEND_CWDHCP_0_1);
	return TRUE;
}

void sendUDP() {
	sendCmd(ESP_SEND_CIPSTART);
	sendCmd(ESP_SEND_CIPSEND);
	delay(500);
	stdioPrintf(ESP01_UART, "pepaso\r\n");
}


static bool_t sendCmd(CommandEsp8266_t cmd) {

	printf("Enviando: %s", CommandEsp8266ToString[cmd]);
	bool_t retVal = cmdToEsp01(cmd);

	if (retVal) {
		printf(">>>>OK\r\n");
	} else {
		printf(">>>>Error\r\n");
	}

	return retVal;
}


static bool_t cmdToEsp01(CommandEsp8266_t cmd) {
	uint16_t size = sizeof(esp01Responses[cmd]);
	printf("Size: %d", size);
	stdioPrintf(ESP01_UART, CommandEsp8266ToString[cmd]);

	return waitForReceiveStringOrTimeoutBlocking(ESP01_UART,
			esp01Responses[cmd], size , 500);
}

static void rst() {
	printf("Enviando: %s", CommandEsp8266ToString[ESP_SEND_RST]);
	stdioPrintf(ESP01_UART, CommandEsp8266ToString[ESP_SEND_RST]);
	delay(500);
}
