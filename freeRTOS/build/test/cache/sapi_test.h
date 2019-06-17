typedef enum {







   T_FIL1, T_COL2, T_COL0, T_FIL2, T_FIL3, T_FIL0, T_COL1,

   CAN_TD, CAN_RD, RS232_TXD, RS232_RXD,





   GPIO8, GPIO7, GPIO5, GPIO3, GPIO1,

   LCD1, LCD2, LCD3, LCDRS, LCD4,

   SPI_MISO,

   ENET_TXD1, ENET_TXD0, ENET_MDIO, ENET_CRS_DV, ENET_MDC, ENET_TXEN, ENET_RXD1,

   GPIO6, GPIO4, GPIO2, GPIO0,

   LCDEN,

   SPI_MOSI,

   ENET_RXD0,







   TEC1, TEC2, TEC3, TEC4,







   LEDR, LEDG, LEDB, LED1, LED2, LED3,







   DI0, DI1, DI2, DI3, DI4, DI5, DI6, DI7,



   DO0, DO1, DO2, DO3, DO4, DO5, DO6, DO7

} gpioMap_t;



typedef uint8_t bool_t;



bool_t gpioWrite( gpioMap_t pin, bool_t value );
