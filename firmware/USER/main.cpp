#include "stm32f1xx.h"
#include "usbd_custom_hid_if.h"

#include "KeycodeHidReport.h"

extern USBD_HandleTypeDef hUsbDeviceFS;
static KeycodeHidReport keycodeHidReport;

extern "C" int user_main()
{
    // memset( keycode_report_buf , 0 , 17 );

    uint16_t keycodeHidReportSize = 0;

    while(1)
    {
        keycodeHidReport.hidReportPress( H );
        USBD_CUSTOM_HID_SendReport( &hUsbDeviceFS , keycodeHidReport.getReportBuffer( &keycodeHidReportSize ) ,  keycodeHidReportSize );
        HAL_Delay( 50 );
        keycodeHidReport.hidReportRelease( H );
        keycodeHidReport.hidReportPress( L );
        USBD_CUSTOM_HID_SendReport( &hUsbDeviceFS , keycodeHidReport.getReportBuffer( &keycodeHidReportSize ) ,  keycodeHidReportSize );
        HAL_Delay( 50 );
        keycodeHidReport.hidReportReset();
        USBD_CUSTOM_HID_SendReport( &hUsbDeviceFS , keycodeHidReport.getReportBuffer( &keycodeHidReportSize ) ,  keycodeHidReportSize );
        HAL_Delay( 1000 );
    }
    return -1;
}

