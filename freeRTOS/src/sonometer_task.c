#include "sonometer_task.h"
#include "task.h"
#include "sapi.h"
#include "peripheral_driver.h"

#define MUY_BAJO 4
#define BAJO 3
#define MEDIO 2
#define ALTO 1
#define alpha 0.05
#define VENTANA_MUESTRA 20
#define CANTIDAD_MUESTRA 10
#define PRIMERA_VENTANA 10
#define MUESTRA_VENTANA_VENTANA 10

static void updateSignalPowerValue( uint16_t);

void sonomterTask(void * a) {
	portTickType xPeriodicity = 200 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	uint16_t muestra = 0;
	uint16_t adc_filtrado = 0;
	uint16_t maxMuestra = 0;
	uint16_t minMuestra = 1024;
	uint16_t contadorMuestras = 0;
	uint16_t indexVentana = 0;
	uint16_t ventanaMuestras[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	uint16_t promVentana = 0;

	uint16_t muestraVentana = 0;
	uint16_t maxMuestraVentana = 0;
	uint16_t minMuestraVentana = 0;
	uint16_t indexMuestraVentana = 0;
	uint16_t contadorMuestraVentana = 0;
	uint16_t promMuestraVentana = 0;
	uint16_t ventanaMuestrasVentana[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	uint16_t otherWindows[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	uint16_t contadorOtherWindows = 0;
	uint16_t indexOtherWindows = 0;
	uint16_t promOtherWindows = 0;
	uint16_t valorFinal = 0;

	// ---------- REPETIR POR SIEMPRE --------------------------
	while (TRUE) {
		//gpioToggle(LEDB);
		// Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)

		muestra = adcRead(CH1);
		if (muestra > maxMuestra) {
			maxMuestra = muestra;
		}
		if (muestra < minMuestra) {
			minMuestra = muestra;
		}

		if (contadorMuestras >= CANTIDAD_MUESTRA) {
			taskENTER_CRITICAL();
			ventanaMuestras[indexVentana] = maxMuestra - minMuestra;
			taskEXIT_CRITICAL();
			indexVentana++;
			contadorMuestras = 0;
			maxMuestra = 0;
			minMuestra = 1024;
		}

		if (indexVentana >= VENTANA_MUESTRA) {
			indexVentana = 0;
		}

		contadorMuestras++;

		for (int i = 0; i < PRIMERA_VENTANA; i++) {
			promVentana += ventanaMuestras[i];
		}

		muestraVentana = promVentana / PRIMERA_VENTANA;

		if (muestraVentana > maxMuestraVentana) {
			maxMuestraVentana = muestraVentana;
		}

		if (muestraVentana > minMuestraVentana) {
			minMuestraVentana = muestraVentana;
		}

		contadorMuestraVentana++;

		if (contadorMuestraVentana >= MUESTRA_VENTANA_VENTANA) {
			ventanaMuestrasVentana[indexMuestraVentana] = (maxMuestraVentana
					+ minMuestraVentana) / 2;
			indexMuestraVentana++;
			maxMuestraVentana = 0;
			minMuestraVentana = 1024;
			contadorMuestraVentana = 0;
		}

		if (indexMuestraVentana >= MUESTRA_VENTANA_VENTANA) {
			indexMuestraVentana = 0;
		}

		for (int i = 0; i < MUESTRA_VENTANA_VENTANA; i++) {
			promMuestraVentana += ventanaMuestrasVentana[i];
		}

		contadorOtherWindows++;

		if (contadorOtherWindows >= MUESTRA_VENTANA_VENTANA) {
			otherWindows[indexOtherWindows] = promMuestraVentana
					/ MUESTRA_VENTANA_VENTANA;
			indexOtherWindows++;
			contadorOtherWindows = 0;
		}

		for (int i = 0; i < MUESTRA_VENTANA_VENTANA; i++) {
			promOtherWindows += otherWindows[i];
		}

		if (indexOtherWindows >= MUESTRA_VENTANA_VENTANA) {
			indexOtherWindows = 0;
		}

		valorFinal = promOtherWindows / MUESTRA_VENTANA_VENTANA;

		adc_filtrado = (alpha * valorFinal) + ((1 - alpha) * adc_filtrado);

		updateSignalPowerValue(adc_filtrado);

		promVentana = 0;
		promMuestraVentana = 0;
		promOtherWindows = 0;
		vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

static void updateSignalPowerValue(uint16_t signal) {
	if (signal < 400) {
		/*gpioWrite(LED3, ON);
		 gpioWrite(LED2, OFF);
		 gpioWrite(LED1, OFF);
		 gpioWrite(LEDB, OFF);*/
		setSignalPower(MUY_BAJO);
	}

	if (signal > 500 & signal < 600) {
		/*gpioWrite(LED3, ON);
		 gpioWrite(LED2, ON);
		 gpioWrite(LED1, OFF);
		 gpioWrite(LEDB, OFF);*/
		setSignalPower(BAJO);
	}
	if (signal > 600 & signal < 700) {
		/*gpioWrite(LED3, ON);
		 gpioWrite(LED2, ON);
		 gpioWrite(LED1, ON);
		 gpioWrite(LEDB, OFF);*/
		setSignalPower(MEDIO);
	}
	if (signal > 700) {
		/*gpioWrite(LED3, ON);
		 gpioWrite(LED2, ON);
		 gpioWrite(LED1, ON);
		 gpioWrite(LEDB, ON);*/
		setSignalPower(ALTO);

	}
}
