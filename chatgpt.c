#include <stdio.h>
#include "aws_iot_mqtt_client_interface.h"
#include "aws_iot_version.h"

#define AWS_ENDPOINT "your-aws-endpoint"
#define AWS_PORT 8883
#define CLIENT_ID "your-client-id"
#define TOPIC "your-topic"
#define QOS 0

AWS_IoT_Client mqttClient;

void messageArrivedOnSubscribeCallbackHandler(AWS_IoT_Client *pClient, char *topicName,
                                              uint16_t topicNameLen, IoT_Publish_Message_Params *params, void *pData)
{
    printf("Message received on topic %s: %.*s\n", topicName, (int)params->payloadLen, (char *)params->payload);
}

int chatgpt()
{
    IoT_Client_Init_Params mqttInitParams = iotClientInitParamsDefault;
    mqttInitParams.enableAutoReconnect = false; // Disable auto reconnect
    mqttInitParams.pHostURL = AWS_ENDPOINT;
    mqttInitParams.port = AWS_PORT;
    mqttInitParams.pRootCALocation = "your-root-ca-path";
    mqttInitParams.pDeviceCertLocation = "your-device-cert-path";
    mqttInitParams.pDevicePrivateKeyLocation = "your-private-key-path";
    mqttInitParams.mqttCommandTimeout_ms = 20000;
    mqttInitParams.tlsHandshakeTimeout_ms = 5000;
    mqttInitParams.isSSLHostnameVerify = true;
    mqttInitParams.disconnectHandler = NULL;

    if (aws_iot_mqtt_init(&mqttClient, &mqttInitParams) != SUCCESS)
    {
        printf("Error initializing MQTT client.\n");
        return -1;
    }

    IoT_Publish_Message_Params paramsQOS0;
    paramsQOS0.qos = QOS;
    paramsQOS0.payload = "Hello from MQTT client";
    paramsQOS0.payloadLen = strlen("Hello from MQTT client");

    if (aws_iot_mqtt_connect(&mqttClient) != SUCCESS)
    {
        printf("Error connecting to MQTT broker.\n");
        return -1;
    }

    if (aws_iot_mqtt_subscribe(&mqttClient, TOPIC, strlen(TOPIC), QOS,
                               messageArrivedOnSubscribeCallbackHandler, NULL) != SUCCESS)
    {
        printf("Error subscribing to topic %s.\n", TOPIC);
        return -1;
    }

    if (aws_iot_mqtt_publish(&mqttClient, TOPIC, strlen(TOPIC), &paramsQOS0) != SUCCESS)
    {
        printf("Error publishing message to topic %s.\n", TOPIC);
        return -1;
    }

    // Wait for message to be received
    // For a real application, you may want to add a loop to keep the program running

    aws_iot_mqtt_disconnect(&mqttClient);

    return 0;
}
