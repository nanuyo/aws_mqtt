#include <aws_iot_config.h>
#include <aws_iot_mqtt_client.h>
#include <aws_iot_logging.h>

// Replace with your specific values
#define CLIENT_ID "YOUR_CLIENT_ID"
#define TOPIC "YOUR_TOPIC"
#define MESSAGE "Hello from AWS IoT!"

int gemini()
{
    IoT_Error_t connect_status = SUCCESS;
    IoT_Client_Init_Params mqttInitParams = iotClientInitParamsDefault;
    IoT_Client mqttClient;
    IoT_Publish_Info_t publishInfo;

    AWS_IoT_ logging_callback_onboard(LEVEL_INFO, LOCAL_LOG_LEVEL);

    mqttInitParams.endpoint = AWS_IOT_MY_REGION_ENDPOINT;
    mqttInitParams.privateKey = YOUR_DEVICE_PRIVATE_KEY;
    mqttInitParams.certificate = YOUR_DEVICE_CERTIFICATE;
    mqttInitParams.clientId = CLIENT_ID;

    IoTClient_Init(&mqttClient, &mqttInitParams);

    connect_status = IoTClient_Connect(mqttClient);

    if (connect_status != SUCCESS)
    {
        printf("Connection error: %d\n", connect_status);
        return -1;
    }

    publishInfo.qos = QOS1;
    publishInfo.retain = 0;
    publishInfo.topicName = TOPIC;
    publishInfo.topicNameLength = strlen(TOPIC);
    publishInfo.payload = (void *)MESSAGE;
    publishInfo.payloadLength = strlen(MESSAGE);

    IoTClient_Publish(mqttClient, &publishInfo);

    printf("Message published: %s\n", MESSAGE);

    IoTClient_Disconnect(mqttClient);
    IoTClient_Cleanup(&mqttClient);

    return 0;
}
