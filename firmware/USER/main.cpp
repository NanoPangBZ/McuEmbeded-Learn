#include "stm32f1xx.h"
#include "usbd_custom_hid_if.h"

#include "keyboardHidReport.h"
#include "Keyboard.h"

#include "elog.h"
#include "usart.h"

#include "function_section.h"

extern USBD_HandleTypeDef hUsbDeviceFS;
static KeyboardHidReport keyboardHidReport;

extern "C" int user_main()
{
    uint16_t keycodeHidReportSize = 0;

    elog_init();
    elog_start();

    elog_i( "main" , "set up" );
    elog_flush();

    while(1)
    {
        keyboardHidReport.hidReportPress( H );
        USBD_CUSTOM_HID_SendReport( &hUsbDeviceFS , keyboardHidReport.getReportBuffer( &keycodeHidReportSize ) ,  keycodeHidReportSize );
        HAL_Delay( 50 );
        keyboardHidReport.hidReportRelease( H );
        keyboardHidReport.hidReportPress( L );
        USBD_CUSTOM_HID_SendReport( &hUsbDeviceFS , keyboardHidReport.getReportBuffer( &keycodeHidReportSize ) ,  keycodeHidReportSize );
        HAL_Delay( 50 );
        keyboardHidReport.hidReportReset();
        USBD_CUSTOM_HID_SendReport( &hUsbDeviceFS , keyboardHidReport.getReportBuffer( &keycodeHidReportSize ) ,  keycodeHidReportSize );
        HAL_Delay( 1000 );
    }
    return -1;
}

DECLARE_FUNCTION_INFO(  user_main , NULL )
