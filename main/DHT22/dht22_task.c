#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "rom/ets_sys.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "sdkconfig.h"


void dht22_task(void *pvParameter)
{
	setDHTgpio( 4 );
	printf( "Starting DHT Measurement \n\n");

	while(1) {
	
		printf("=== Reading DHT ===\n" );
		int ret = readDHT();
		
		errorHandler(ret);

		printf( "Hum %.2f\n", getHumidity() );
		printf( "Tmp %.2f\n", getTemperature() );
		
		// -- wait at least 2 sec before reading again ------------
		// The interval of whole process must be beyond 2 seconds !! 
		vTaskDelay( 3000 / portTICK_RATE_MS );
	}
}

void publicar_temperatura_task(void * parm)
{

	int message_id;
	
  char json[300];
	char topic[350];
	
  char temperature[15];
  char humidity[15];
	char rssi_chunk[15];

	float temperature_threshold = 24;
  float humidity_threshold = 90;
  int8_t rssi = 0;
  uint32_t rand;

	wifi_ap_record_t ap_info;
  setDHTgpio( 4 );
	
  while(1) {
        if (mqtt_client_connected) {
            
            vTaskDelay(TEMP_PUBLISH_INTERVAL_SECONDS * 1000 / portTICK_PERIOD_MS);

            rand = esp_random();
            if (rand >  2147483648) temperature_threshold += 0.3;
            else temperature_threshold -= 0.3;
            
            if (temperature_threshold > 40) temperature_threshold = 39.5;
            if (temperature_threshold < 5) temperature_threshold = 5.5;

            int ret = readDHT();
            errorHandler(ret);
            humidity_threshold = getHumidity();
            temperature_threshold = getTemperature();
                
            esp_wifi_sta_get_ap_info(&ap_info);
            rssi = ap_info.rssi;

            snprintf(temperature, sizeof(temperature), "%.2f", temperature_threshold);
            snprintf(humidity, sizeof(humidity), "%.2f", humidity_threshold);
            snprintf(rssi_chunk, sizeof(rssi_chunk), "%d", rssi_chunk);

                json[0] = 0;

                strcat(json, "{ \"dev_id\": ");
                strcat(bufferJson, IOTCORE_DEVICE_NUMBER);
                strcat(json, ", \"temperatura\": ");
                strcat(json, temperature);
                strcat(json, ", \"humedad\": ");
                strcat(json, humidity);
                strcat(json, ", \"rssi\": ");
                strcat(json, rssi_chunk);
                strcat(json, " }");

                topic[0] = 0;
                strcat(topic, "/devices/");
                strcat(bufferTopic, IOTCORE_DEVICEID);
                strcat(topic, "/events/temperatura");

                msg_id = esp_mqtt_client_publish(cliente, bufferTopic, bufferJson, 0, 1, 0);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
    vTaskDelete(NULL);
}
