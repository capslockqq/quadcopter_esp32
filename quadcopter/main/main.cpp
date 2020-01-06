#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "../../freertos_distro/FreeRTOS_tasks/Application_interfaces.hpp"
#include "../../component_framework/components/ParameterWrite.hpp"

#include "../application_code/application_code.hpp"
#include "../../freertos_distro/FreeRTOS_tasks/Application_interfaces.hpp"
#include "../../freertos_distro/FreeRTOS_tasks/tasks.hpp"
#include <iostream>
/* Can use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
ParameterWrite *ParameterWrite::instance = 0;
extern "C"
{
    void app_main(void);
}

void app_main(void)
{
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    /* Set the GPIO as a push/pull output */
    I_application_code *app = new Application_code("App", "01");
    Tasks tasks(app);
        /* Blink off (output low) */
    tasks.SetUp_Tasks(tasks);
    while(1) { //Never terminating problem, hence, freeRTOS tasks wont stop
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("Main()\n");
        std::cout << __cplusplus << std::endl;

    }
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
        /* Blink on (output high) */
}