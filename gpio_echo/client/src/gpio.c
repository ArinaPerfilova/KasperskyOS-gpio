#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gpio/gpio.h>
#include <stdbool.h>
#include <bsp/bsp.h>

//#define IN_MODE            (GPIO_DIR_IN | \
//                            GPIO_EVENT_RISE_EDGE | \
//                            GPIO_EVENT_FALL_EDGE)

#define IN_MODE            GPIO_DIR_IN 


#define DELAY_S            1
//#define GPIO_PIN_IN        9

#define GPIO_PIN_IN        16


#define GPIO_PIN_NUM_IN1 12U
#define GPIO_PIN_NUM_IN2 13U
#define GPIO_PIN_NUM_ENA 6U
#define GPIO_PIN_NUM_IN4 20U
#define GPIO_PIN_NUM_IN3 21U
#define GPIO_PIN_NUM_ENB 26U

#define HIGH 1
#define LOW 0



#define GPIO_PIN_OUT       12
#define GPIO_EVENT_DELAY_M 10
#define GPIO_LOW_LEVEL     0
#define GPIO_HIGH_LEVEL    1
#define GPIO_INVALID_LEVEL 2
#define HW_MODULE_CFG      "raspberry_pi4b.default"
#define HW_MODULE_NAME     "gpio0"

static int lastPinValue;


void forward(GpioHandle* handle){
    GpioOut(*handle, GPIO_PIN_NUM_IN1, HIGH);
    GpioOut(*handle, GPIO_PIN_NUM_IN2, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_IN3, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_IN4, HIGH);
    GpioOut(*handle, GPIO_PIN_NUM_ENA, HIGH);
    GpioOut(*handle, GPIO_PIN_NUM_ENB, HIGH);
}

void stop(GpioHandle* handle) {

    GpioOut(*handle, GPIO_PIN_NUM_IN1, LOW);
    fprintf(stderr, "IN1\n");

    GpioOut(*handle, GPIO_PIN_NUM_IN2, LOW);
    fprintf(stderr, "IN2\n");

    GpioOut(*handle, GPIO_PIN_NUM_IN3, LOW);
    fprintf(stderr, "IN3\n");

    GpioOut(*handle, GPIO_PIN_NUM_IN4, LOW);
    fprintf(stderr, "IN4\n");

    GpioOut(*handle, GPIO_PIN_NUM_ENA, LOW);
    fprintf(stderr, "ENA\n");

    GpioOut(*handle, GPIO_PIN_NUM_ENB, LOW);
    fprintf(stderr, "ENB\n");

}


static Retcode CheckGpioEvent(GpioHandle *handle)
{
    char buf[sizeof(KdfEvent) + sizeof(GpioEvent)] = { 0 };
    KdfEvent *event = (KdfEvent *) buf;
    Retcode rc = rcFail;

    if (NULL != handle)
    {
        /* Get actual gpio event. */
        rc = GpioGetEvent(*handle, event, GPIO_EVENT_DELAY_M);
        if (rcOk == rc)
        {
            /* Update GPIO input pin value. */
            if (GPIO_EVENT_TYPE_EDGE_RISE == event->type)
            {
                lastPinValue = GPIO_HIGH_LEVEL;
                fprintf(stderr, "GPIO module %s input pin %d is %d.\n",
                        HW_MODULE_NAME, GPIO_PIN_IN, GPIO_HIGH_LEVEL);
            }
            else if (GPIO_EVENT_TYPE_EDGE_FALL == event->type)
            {
                lastPinValue = GPIO_LOW_LEVEL;
                fprintf(stderr, "GPIO module %s input pin %d is %d.\n",
                        HW_MODULE_NAME, GPIO_PIN_IN, GPIO_LOW_LEVEL);
            }
            else
            {
                lastPinValue = GPIO_INVALID_LEVEL;
            }
        }
    }

    return rc;
}

int main(void)
{
    int fevent;
    int returnValue = EXIT_FAILURE;
    Retcode rc = rcFail;
    GpioHandle handle = GPIO_INVALID_HANDLE;
    lastPinValue = GPIO_INVALID_LEVEL;

    fprintf(stderr, "Start GPIO_echo test.\n");

    /**
     * Initialize the board support package (BSP) driver and set configuration
     * for GPIO pins. It is required for stdout by UART.
     */
    rc = BspInit(NULL);
    if (rcOk != rc)
    {
        fprintf(stderr, "Failed to initialize BSP, error code: %d.\n",
                RC_GET_CODE(rc));
    }

    /* Setting config for BSP driver. */
    if (rcOk == rc)
    {
        rc = BspSetConfig(HW_MODULE_NAME, HW_MODULE_CFG);
        if (rcOk != rc)
        {
            fprintf(stderr,
                    "Failed to set mux configuration for %s module, "
                    "error code: %d.\n", HW_MODULE_NAME, RC_GET_CODE(rc));
        }
    }

    /* Initialize GPIO. */
    if (rcOk == rc)
    {
        rc = GpioInit();
        if (rcOk != rc)
        {
            fprintf(stderr, "GpioInit failed, error code: %d.\n",
                    RC_GET_CODE(rc));
        }
    }

    /* Initialize and setup HW_MODULE_NAME port. */
    if (rcOk == rc)
    {
        rc = GpioOpenPort(HW_MODULE_NAME, &handle);
        if (rcOk != rc)
        {
            fprintf(stderr,
                    "GpioOpenPort for %s port failed, error code: %d.\n",
                    HW_MODULE_NAME, RC_GET_CODE(rc));
        }
        else if (GPIO_INVALID_HANDLE == handle)
        {
            fprintf(stderr, "Error: invalid GPIO handle.\n");
            rc = rcFail;
        }
    }

    /* Setting GPIO mode for output pin. */
    if (rcOk == rc)
    {
        rc = GpioSetMode(handle, GPIO_PIN_OUT, GPIO_DIR_OUT);
        if (rcOk != rc)
        {
            fprintf(stderr,
                    "GpioSetMode for GPIO module %s pin %d failed, "
                    "error code: %d.\n", HW_MODULE_NAME, GPIO_PIN_OUT,
                    RC_GET_CODE(rc));
        }
    }

    /* Setting GPIO mode for output pin. */
    if (rcOk == rc)
    {
        rc = GpioSetMode(handle, GPIO_PIN_NUM_IN2, GPIO_DIR_OUT);
        if (rcOk != rc)
        {
            fprintf(stderr,
                    "GpioSetMode for GPIO module %s pin %d failed, "
                    "error code: %d.\n", HW_MODULE_NAME, GPIO_PIN_OUT,
                    RC_GET_CODE(rc));
        }
    }

    /* Setting GPIO mode for output pin. */
    if (rcOk == rc)
    {
        rc = GpioSetMode(handle, GPIO_PIN_NUM_IN3, GPIO_DIR_OUT);
        if (rcOk != rc)
        {
            fprintf(stderr,
                    "GpioSetMode for GPIO module %s pin %d failed, "
                    "error code: %d.\n", HW_MODULE_NAME, GPIO_PIN_OUT,
                    RC_GET_CODE(rc));
        }
    }

    /* Setting GPIO mode for output pin. */
    if (rcOk == rc)
    {
        rc = GpioSetMode(handle, GPIO_PIN_NUM_IN4, GPIO_DIR_OUT);
        if (rcOk != rc)
        {
            fprintf(stderr,
                    "GpioSetMode for GPIO module %s pin %d failed, "
                    "error code: %d.\n", HW_MODULE_NAME, GPIO_PIN_OUT,
                    RC_GET_CODE(rc));
        }
    }

    /* Setting GPIO mode for output pin. */
    if (rcOk == rc)
    {
        rc = GpioSetMode(handle, GPIO_PIN_NUM_ENA, GPIO_DIR_OUT);
        if (rcOk != rc)
        {
            fprintf(stderr,
                    "GpioSetMode for GPIO module %s pin %d failed, "
                    "error code: %d.\n", HW_MODULE_NAME, GPIO_PIN_OUT,
                    RC_GET_CODE(rc));
        }
    }

    /* Setting GPIO mode for output pin. */
    if (rcOk == rc)
    {
        rc = GpioSetMode(handle, GPIO_PIN_NUM_ENB, GPIO_DIR_OUT);
        if (rcOk != rc)
        {
            fprintf(stderr,
                    "GpioSetMode for GPIO module %s pin %d failed, "
                    "error code: %d.\n", HW_MODULE_NAME, GPIO_PIN_OUT,
                    RC_GET_CODE(rc));
        }
    }




    /* Setting GPIO mode for input pin. */
    if (rcOk == rc)
    {
        rc = GpioSetMode(handle, GPIO_PIN_IN, IN_MODE);
        if (rcOk != rc)
        {
            fprintf(stderr,
                    "GpioSetMode for GPIO module %s pin %d failed, "
                    "error code: %d.\n", HW_MODULE_NAME, GPIO_PIN_IN,
                    RC_GET_CODE(rc));
        }
    }

while(1) {
    sleep(1);

    fevent = 0;

    while(!fevent) {
    /* Capture GPIO event and update GPIO input pin value. */

                rtl_uint32_t pinVal = 0;

                rc = GpioIn(handle, 16, &pinVal);


        fprintf(stderr,"Val  OK %u \n",pinVal);


        fprintf(stderr,"Try out \n");


    /* Set GPIO output pin in HIGH level. */
    if (rcOk == rc)
    {
        fprintf(stderr,"Out OK %u \n",pinVal);

        fprintf(stderr, "GPIO module %s output pin %d set %d.\n",
                HW_MODULE_NAME, GPIO_PIN_OUT, GPIO_HIGH_LEVEL);

        if (!pinVal) {
    	    rc = GpioOut(handle, GPIO_PIN_OUT, GPIO_HIGH_LEVEL);
	    GpioOut(handle, GPIO_PIN_NUM_ENA, GPIO_HIGH_LEVEL);
	    GpioOut(handle, GPIO_PIN_NUM_ENB, GPIO_HIGH_LEVEL);

	}
	else {
    	    rc = GpioOut(handle, GPIO_PIN_OUT, GPIO_LOW_LEVEL);
	    GpioOut(handle, GPIO_PIN_NUM_ENA, GPIO_LOW_LEVEL);
	    GpioOut(handle, GPIO_PIN_NUM_ENB, GPIO_LOW_LEVEL);

	}
        if (rcOk != rc)
        {
            fprintf(stderr,
                    "GpioOut %d for GPIO module %s pin %d failed, "
                    "error code: %d.\n", GPIO_HIGH_LEVEL, HW_MODULE_NAME,
                    GPIO_PIN_OUT, RC_GET_CODE(rc));
        }
    }



    sleep(1);

}

}

    return returnValue;
}
