# ESP-MQTT SSL Sample application (mutual authentication)

This example connects to the broker test.mosquitto.org using ssl transport with client certificate and as a demonstration subscribes/unsubscribes and send a message on certain topic.
(Please note that the public broker is maintained by the community so may not be always available, for details please visit http://test.mosquitto.org)

It uses ESP-MQTT library which implements mqtt client to connect to mqtt broker.

## How to use example

### Hardware Required

This example can be executed on any ESP32 board, the only required interface is WiFi and connection to internet.

### Configure the project

* Open the project configuration menu (`idf.py menuconfig`)
* Configure Wi-Fi or Ethernet under "Example Connection Configuration" menu. See "Establishing Wi-Fi or Ethernet Connection" section in [examples/protocols/README.md](../../README.md) for more details.
* When using Make build system, set `Default serial port` under `Serial flasher config`.

* Generate your client keys and certificate

Navigate to the main directory

```
cd main
```

Generate a client key and a CSR. When you are generating the CSR, do not use the default values. At a minimum, the CSR must include the Country, Organisation and Common Name fields.

```
openssl genrsa -out client.key
openssl req -out client.csr -key client.key -new
```

Paste the generated CSR in the [Mosquitto test certificate signer](https://test.mosquitto.org/ssl/index.php), click Submit and copy the downloaded `client.crt` in the `main` directory.

Please note, that the supplied files `client.crt` and `client.key` in the `main` directory are only placeholders for your client certificate and key (i.e. the example "as is" would compile but would not connect to the broker)

The server certificate `mosquitto.org.crt` can be downloaded in pem format from [mosquitto.org.crt](https://test.mosquitto.org/ssl/mosquitto.org.crt).

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
idf.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for full steps to configure and use ESP-IDF to build projects.

## Example Output

```
I (3714) event: sta ip: 192.168.0.139, mask: 255.255.255.0, gw: 192.168.0.2
I (3714) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFUSE
I (3964) MQTT_CLIENT: Sending MQTT CONNECT message, type: 1, id: 0000
I (4164) MQTTS_EXAMPLE: MQTT_EVENT_CONNECTED
I (4174) MQTTS_EXAMPLE: sent publish successful, msg_id=41464
I (4174) MQTTS_EXAMPLE: sent subscribe successful, msg_id=17886
I (4174) MQTTS_EXAMPLE: sent subscribe successful, msg_id=42970
I (4184) MQTTS_EXAMPLE: sent unsubscribe successful, msg_id=50241
I (4314) MQTTS_EXAMPLE: MQTT_EVENT_PUBLISHED, msg_id=41464
I (4484) MQTTS_EXAMPLE: MQTT_EVENT_SUBSCRIBED, msg_id=17886
I (4484) MQTTS_EXAMPLE: sent publish successful, msg_id=0
I (4684) MQTTS_EXAMPLE: MQTT_EVENT_SUBSCRIBED, msg_id=42970
I (4684) MQTTS_EXAMPLE: sent publish successful, msg_id=0
I (4884) MQTT_CLIENT: deliver_publish, message_length_read=19, message_length=19
I (4884) MQTTS_EXAMPLE: MQTT_EVENT_DATA
TOPIC=/topic/qos0
DATA=data
I (5194) MQTT_CLIENT: deliver_publish, message_length_read=19, message_length=19
I (5194) MQTTS_EXAMPLE: MQTT_EVENT_DATA
TOPIC=/topic/qos0
DATA=data
```

## Configuracion SSID y PASS WiFi
Este ejemplo usa la funcion *example_connect()* de la platarforma ESP-IDF.

Para configurar el SSID y PASSWORD se debe hacer clic en el icono "engranaje" (configuracion) de la barra inferior del VSCode y all’ en la secci—n de WiFi se podr‡n configurar los datos necesarios.

## Configurar URI del Broker
Dentro del archivo app_main.c hay que configurar la definición "BROKER_URI" que se encuentra al inicio del archivo, colocando los datos correctos del broker a utilizar.

Configurar certificados:
En los archivos client.crt, client.key y broker_CA.crt, hay que pegar el contenido de los certificados que se crean con el script crea_certs.sh. Recordar reemplazar la IP que se encuentra dentro del script, por TU IP LOCAL



## Links de interes

- [Codigo de ejemplo para conectar el sensor DHT22](https://github.com/lzimperz/DAIoT_2022-esp_idf-gpio_led_task)

- [Codigo de ejemplo para conexion ESP-MQTT con SSL](https://github.com/lzimperz/DAIoT_2022-esp32_ssl_mutual_auth)



