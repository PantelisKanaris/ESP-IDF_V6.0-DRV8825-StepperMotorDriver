#include <stdio.h>
#include "DRV8825.h"
void app_main(void)
{
    DRV8825_t * driverStruct = (DRV8825_t *) malloc(sizeof(DRV8825_t));
    DRV8825_InitializeLedc(driverStruct);
}
