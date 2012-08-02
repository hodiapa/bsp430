#define configBSP430_CONSOLE 1
#define configBSP430_UPTIME 1

/* Specify placement on P1.5  */
#define APP_DS18B20_PORT BSP430_HPL_PORT1
#define APP_DS18B20_BIT BIT5

/* Request the corresponding HPL */
#define configBSP430_PERIPH_PORT1 1

/* Get platform defaults */
#include <bsp430/platform/bsp430_config.h>