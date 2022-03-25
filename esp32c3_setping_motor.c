#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"
#include "esp32c3/rom/ets_sys.h"


#define GPIO_OUTPUT_IO_0    GPIO_NUM_0
#define GPIO_OUTPUT_IO_1    GPIO_NUM_1
#define GPIO_OUTPUT_IO_2    GPIO_NUM_2
#define GPIO_OUTPUT_IO_3    GPIO_NUM_3
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1) | (1ULL<<GPIO_OUTPUT_IO_2) | (1ULL<<GPIO_OUTPUT_IO_3))
#define SPEED 10

//delay time ms
void delay_ms(uint32_t x){

    ets_delay_us(x * 1000L);
}
//delay time us
void delay_us(uint32_t x){
    ets_delay_us(x);
}


void MotorInit(){
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
}

//zheng
void MotorCW(void){
        gpio_set_level(GPIO_NUM_0,1);
        gpio_set_level(GPIO_NUM_1,0);
        gpio_set_level(GPIO_NUM_2,0);
        gpio_set_level(GPIO_NUM_3,0);
        vTaskDelay(SPEED / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_0,0);
        gpio_set_level(GPIO_NUM_1,1);
        gpio_set_level(GPIO_NUM_2,0);
        gpio_set_level(GPIO_NUM_3,0);
        vTaskDelay(SPEED / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_0,0);
        gpio_set_level(GPIO_NUM_1,0);
        gpio_set_level(GPIO_NUM_2,1);
        gpio_set_level(GPIO_NUM_3,0);
        vTaskDelay(SPEED / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_0,0);
        gpio_set_level(GPIO_NUM_1,0);
        gpio_set_level(GPIO_NUM_2,0);
        gpio_set_level(GPIO_NUM_3,1);
        vTaskDelay(SPEED / portTICK_PERIOD_MS);
        printf("Motor was on...........\r\n");
        
}

void MotorCCW(void){
        gpio_set_level(GPIO_NUM_0,0);
        gpio_set_level(GPIO_NUM_1,0);
        gpio_set_level(GPIO_NUM_2,0);
        gpio_set_level(GPIO_NUM_3,1);
        vTaskDelay(SPEED / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_0,0);
        gpio_set_level(GPIO_NUM_1,0);
        gpio_set_level(GPIO_NUM_2,1);
        gpio_set_level(GPIO_NUM_3,0);
        vTaskDelay(SPEED / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_0,0);
        gpio_set_level(GPIO_NUM_1,1);
        gpio_set_level(GPIO_NUM_2,0);
        gpio_set_level(GPIO_NUM_3,0);
        vTaskDelay(SPEED / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_0,1);
        gpio_set_level(GPIO_NUM_1,0);
        gpio_set_level(GPIO_NUM_2,0);
        gpio_set_level(GPIO_NUM_3,0);
        vTaskDelay(SPEED / portTICK_PERIOD_MS);
        printf("Motor was off...........\r\n");
}

void MotorStop(){
    gpio_set_level(GPIO_NUM_0,0);
    gpio_set_level(GPIO_NUM_1,0);
    gpio_set_level(GPIO_NUM_2,0);
    gpio_set_level(GPIO_NUM_3,0);
    printf("Motor was stop...........\r\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}


static void Motor_Server(){
    int command = 1;
    MotorInit();
    while (1)
    {
        if (command == 1)
        {
            MotorCCW();
        }
        if (command == 2)
        {
            MotorCW();
        }
        if (command == 0)
        {
            MotorStop();
        }
        
    }
    

}
void app_main(void)
{
    xTaskCreate(Motor_Server, "Motor_Server", 4000, NULL, 10, NULL);
    while (1)
    {
        printf("main task\r\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
