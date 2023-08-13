#include "KeyboardHidReport.h"

void KeyboardHidReport::hidReportPress( KeyCode_t keycode )
{
    int index, bitIndex;

    if (keycode < RESERVED)
    {
        index = keycode / 8;
        bitIndex = (keycode + 8) % 8;
    } else
    {
        index = keycode / 8 + 1;
        bitIndex = keycode % 8;
    }

    _hidReportBuffer[index + 1] |= (1 << bitIndex);
}


void KeyboardHidReport::hidReportRelease( KeyCode_t keycode)
{
    int index, bitIndex;

    if (keycode < RESERVED)
    {
        index = keycode / 8;
        bitIndex = (keycode + 8) % 8;
    } else
    {
        index = keycode / 8 + 1;
        bitIndex = keycode % 8;
    }

    _hidReportBuffer[index + 1] &= ~(1 << bitIndex);
}

bool KeyboardHidReport::hidReportIsPress( KeyCode_t keycode )
{
    int index, bitIndex;

    if (keycode < RESERVED)
    {
        index = keycode / 8;
        bitIndex = (keycode + 8) % 8;
    } else
    {
        index = keycode / 8 + 1;
        bitIndex = keycode % 8;
    }

    return _hidReportBuffer[index + 1] & (1 << bitIndex);
}

void KeyboardHidReport::hidReportReset()
{
    _hidReportBuffer[0] = 1;
    memset( _hidReportBuffer + 1 , 0 , 16 );
}

uint8_t* KeyboardHidReport::getReportBuffer( uint16_t* size )
{
    *size = 17;
    return _hidReportBuffer;
}
