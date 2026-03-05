/* File: src/main.c */
 
#include <stdio.h>
#include <zephyr/kernel.h>        /* k_msleep(), printk() */
#include <zephyr/drivers/gpio.h>  /* gpio_dt_spec, gpio_pin_configure_dt() */
 
/* How long to keep the LED on/off in milliseconds */
#define SLEEP_TIME_MS  500
 
/*
 * DT_ALIAS(led0) expands to the DeviceTree node behind the 'led0' alias.
 * GPIO_DT_SPEC_GET reads the gpios property of that node at compile time.
 * The result is a gpio_dt_spec struct with .port and .pin filled in.
 */
//expands to a device tree node and it will be expanded to something like DT_N_ALIAS_led0  
//so LED0_NODE will be have DT_N_ALIAS_led0
#define LED0_NODE DT_ALIAS(led0)
 

//I guess you need to check devivcetree_generated.h file to see if the required devicetree symbol is generated
#if !DT_NODE_HAS_STATUS(LED0_NODE, okay)
#error "led0 alias is not defined for this board"
#endif
 
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
 
int main(void)
{
    int ret;
 
    /* Verify the GPIO controller is ready before touching it */
    if (!gpio_is_ready_dt(&led)) {
        printf("Error: GPIO device not ready\n");
        return -ENODEV;
    }
 
    /* Configure the pin as an output, initially active (LED ON) */
    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printf("Error %d: pin configure failed\n", ret);
        return ret;
    }
 
    printf("Blinky running on %s\n", CONFIG_BOARD);
 
    while (1) {
        /* Toggle the pin state each iteration */
        ret = gpio_pin_toggle_dt(&led);
        if (ret < 0) { return ret; }
 
        /* Yield to the Zephyr scheduler for SLEEP_TIME_MS milliseconds */
        k_msleep(SLEEP_TIME_MS);
    }
 
    return 0;
}
