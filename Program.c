#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BLYNK_TEMPLATE_ID "TMPL3i0tJmnR4"
#define BLYNK_TEMPLATE_NAME "blink led"
#define BLYNK_AUTH_TOKEN "69EN2IF2m_KAmDrZgS85xAX41k7ZWljs"

#define LED_PURPLE   GPIO_NUM_18
#define LED_ORANGE GPIO_NUM_4
#define LED_CYAN  GPIO_NUM_15


void led_task(void *pvParameter)
{
    gpio_num_t led_gpio = (gpio_num_t) pvParameter;
    uint8_t led_value = 0;
    TickType_t blink_time = 1000;   // default

    // Decide blink time depending on GPIO
    if (led_gpio == LED_PURPLE)   blink_time = 1000;
    if (led_gpio == LED_ORANGE)  blink_time = 500;
    if (led_gpio == LED_CYAN) blink_time = 2000;

    gpio_reset_pin(led_gpio);
    gpio_set_direction(led_gpio, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level(led_gpio, led_value);
        led_value = !led_value;
        vTaskDelay(blink_time / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void app_main()
{
    xTaskCreate(
        &led_task,
        "purple_led_task",
        2048,
        (void *)LED_PURPLE,
        5,
        NULL);

    xTaskCreate(
        &led_task,
        "orange_led_task",
        2048,
        (void *)LED_ORANGE,
        5,
        NULL);

    xTaskCreate(
        &led_task,
        "cyan_led_task",
        2048,
        (void *)LED_CYAN,
        5,
        NULL);
}
