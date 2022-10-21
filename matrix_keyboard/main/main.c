#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "soc/usb_serial_jtag_reg.h"

#define ROW1 GPIO_NUM_0
#define ROW2 GPIO_NUM_1
#define ROW3 GPIO_NUM_18

#define COL1 GPIO_NUM_19
#define COL2 GPIO_NUM_8
#define COL3 GPIO_NUM_9

static gpio_num_t rows[] = {ROW1, ROW2, ROW3};
#define rowCount 3

static gpio_num_t cols[] = {COL1, COL2, COL3};
#define colCount 3

esp_err_t event_handler(void *ctx, system_event_t *event)
{
    return ESP_OK;
}

void printMatrix(int keys[colCount][rowCount])
{
    for (int rowIndex = 0; rowIndex < rowCount; rowIndex++)
    {
        printf("%i", rowIndex);
        printf(": ");

        for (int colIndex = 0; colIndex < colCount; colIndex++)
        {
            printf("%i", keys[colIndex][rowIndex]);
            if (colIndex < colCount)
                printf(", ");
        }
        printf("\n");
    }
    printf("\n");
}

void getPressed(int keys[colCount][rowCount])
{
    
    for (int colIndex = 0; colIndex < colCount; colIndex++)
    {
        gpio_num_t curCol = cols[colIndex];
        for (int colIndex2 = 0; colIndex2 < colCount; colIndex2++)
        {
            if(colIndex2!=colIndex)
            gpio_set_level(cols[colIndex2], 1);
        }
        gpio_set_level(curCol, 0);

        for (int rowIndex = 0; rowIndex < rowCount; rowIndex++)
        {
            uint8_t curRow = rows[rowIndex];
            if (gpio_get_level(curRow) == 0)
            {
                printf("(%i, %i)\n", rowIndex, colIndex);
                keys[colIndex][rowIndex] = 1;
            }
            else
            {
                keys[colIndex][rowIndex] = 0;
            }
        }
        // disable the column
        gpio_set_level(curCol, 1);
    }
}

void readMatrix()
{
    int keys1[colCount][rowCount] = {{ 0 }};
    int keys2[colCount][rowCount] = {{ 0 }};
    getPressed(keys1);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    getPressed(keys2);
    for (int colIndex = 0; colIndex < colCount; colIndex++)
    {
        for (int rowIndex = 0; rowIndex < rowCount; rowIndex++)
        {
            if(keys1[colIndex][rowIndex] == 1 && keys1[colIndex][rowIndex] == keys2[colIndex][rowIndex])
            {
                printf("(%i, %i) is pressed\n\n", rowIndex, colIndex);
            }
        }
    }
}


void configure_gpio(void)
{
    CLEAR_PERI_REG_MASK(USB_SERIAL_JTAG_CONF0_REG, USB_SERIAL_JTAG_DP_PULLUP);
    for (int x = 0; x < rowCount; x++)
    {
        printf("%i", rows[x]);
        gpio_reset_pin(rows[x]);
        gpio_set_direction(rows[x], GPIO_MODE_INPUT);
        gpio_set_pull_mode(rows[x], GPIO_PULLUP_ONLY);
    }

    for (int x = 0; x < colCount; x++)
    {
        printf("%i", cols[x]);
        gpio_reset_pin(cols[x]);
        gpio_set_direction(cols[x], GPIO_MODE_OUTPUT);
        gpio_set_pull_mode(cols[x], GPIO_PULLUP_ONLY);
        gpio_set_level(cols[x], 1);
    }
}

void app_main(void)
{
    configure_gpio();
    while (1)
    {
        readMatrix();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    // printf("Start.\n");

    // gpio_set_direction(ROW1, GPIO_MODE_INPUT);
    // gpio_set_pull_mode(ROW1, GPIO_PULLUP_ONLY);

    // gpio_set_direction(COL1, GPIO_MODE_OUTPUT);
    // gpio_set_level(COL1, 0);
    // gpio_set_pull_mode(COL1, GPIO_PULLDOWN_ONLY);

    // static int press = 0;

    // while (1)
    // {
    //     printf("Not Pressed.\n");
    //     if (gpio_get_level(ROW1) == 0)
    //     {
    //         press = 1;
    //         printf("Pressed.\n");
    //     }
    //     if(press == 1)
    //     {
    //         printf("Pressed.\n");
    //     }
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    // }
}
