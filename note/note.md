USB HID（Human Interface Device）设备通信涉及以下描述符：

1. 设备描述符（Device Descriptor）：
   - 用于描述USB设备的基本信息，如USB协议版本、设备类别、供应商ID、产品ID等。
   - 描述符类型（bDescriptorType）：0x01。

2. 配置描述符（Configuration Descriptor）：
   - 描述设备的配置信息，包括配置值、最大功率、接口数等。
   - 描述符类型（bDescriptorType）：0x02。

3. 接口描述符（Interface Descriptor）：
   - 描述设备的接口信息，包括接口号、设置号、接口类别、子类别、协议等。
   - 描述符类型（bDescriptorType）：0x04。

4. 端点描述符（Endpoint Descriptor）：
   - 描述设备的端点（Endpoint）信息，包括端点地址、传输类型、同步类型、最大数据包大小等。
   - 描述符类型（bDescriptorType）：0x05。

5. 字符串描述符（String Descriptor）：
   - 提供与设备相关的字符串信息，如制造商名称、产品名称、序列号等。
   - 描述符类型（bDescriptorType）：0x03。

6. HID描述符（HID Descriptor）：
   - 用于描述HID设备的特性和功能。
   - 描述符类型（bDescriptorType）：0x21。

7. HID报告描述符（HID Report Descriptor）：
   - 定义HID设备的输入和输出报告的格式和结构。
   - 描述符类型（bDescriptorType）：0x22。

以上描述符是USB HID设备通信中常见的描述符。它们共同描述了设备的基本属性、功能、接口和报告格式，使得主机能够正确地与HID设备进行通信和交互。每个描述符都有特定的格式和字段，用于传递与设备相关的信息。在实际应用中，设备会根据需要提供必要的描述符，并与主机进行正确的交互和数据传输。



STMCubeMX生成的配置(包括了配置描述符之外的一些描述符):

```c
/* USB CUSTOM_HID device FS Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_CUSTOM_HID_CfgFSDesc[USB_CUSTOM_HID_CONFIG_DESC_SIZ] __ALIGN_END =
{
  0x09, /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
  USB_CUSTOM_HID_CONFIG_DESC_SIZ,
  /* wTotalLength: Bytes returned */
  0x00,
  0x01,         /*bNumInterfaces: 1 interface*/
  0x01,         /*bConfigurationValue: Configuration value*/
  0x00,         /*iConfiguration: Index of string descriptor describing
  the configuration*/
  0xC0,         /*bmAttributes: bus powered */
  0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/

  /************** Descriptor of CUSTOM HID interface ****************/
  /* 09 */
  0x09,         /*bLength: Interface Descriptor size*/
  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
  0x00,         /*bInterfaceNumber: Number of Interface*/
  0x00,         /*bAlternateSetting: Alternate setting*/
  0x02,         /*bNumEndpoints*/
  0x03,         /*bInterfaceClass: CUSTOM_HID*/
  0x00,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x00,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,            /*iInterface: Index of string descriptor*/
  /******************** Descriptor of CUSTOM_HID *************************/
  /* 18 */
  0x09,         /*bLength: CUSTOM_HID Descriptor size*/
  CUSTOM_HID_DESCRIPTOR_TYPE, /*bDescriptorType: CUSTOM_HID*/
  0x11,         /*bCUSTOM_HIDUSTOM_HID: CUSTOM_HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of CUSTOM_HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  USBD_CUSTOM_HID_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
  /******************** Descriptor of Custom HID endpoints ********************/
  /* 27 */
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/

  CUSTOM_HID_EPIN_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  CUSTOM_HID_EPIN_SIZE, /*wMaxPacketSize: 2 Byte max */
  0x00,
  CUSTOM_HID_FS_BINTERVAL,          /*bInterval: Polling Interval */
  /* 34 */

  0x07,          /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT, /* bDescriptorType: */
  CUSTOM_HID_EPOUT_ADDR,  /*bEndpointAddress: Endpoint Address (OUT)*/
  0x03, /* bmAttributes: Interrupt endpoint */
  CUSTOM_HID_EPOUT_SIZE,  /* wMaxPacketSize: 2 Bytes max  */
  0x00,
  CUSTOM_HID_FS_BINTERVAL,  /* bInterval: Polling Interval */
  /* 41 */
};
```

报告描述符实例:

```c
#define LSB(_x) ((_x) & 0xFF)
#define MSB(_x) ((_x) >> 8)

#define RAWHID_USAGE_PAGE	0xFFC0
#define RAWHID_USAGE		0x0C00
#define RAWHID_TX_SIZE 64
#define RAWHID_RX_SIZE 64

__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
        0x05, 0x01,         //   Usage Page (Generic Desktop),
        0x09, 0x06,         //   Usage (Keyboard),
        0xA1, 0x01,         //   Collection (Application),
        0x85, 0x01,                    //     REPORT_ID (1)
        // bitmap of modifiers
        0x75, 0x01,         //   Report Size (1),
        0x95, 0x08,         //   Report Count (8),
        0x05, 0x07,       //   Usage Page (Key Codes),
        0x19, 0xE0,       //   Usage Minimum (224),
        0x29, 0xE7,       //   Usage Maximum (231),
        0x15, 0x00,       //   Logical Minimum (0),
        0x25, 0x01,       //   Logical Maximum (1),
        0x81, 0x02,       //   Input (Data, Variable, Absolute), ;Modifier byte
        // bitmap of keys
        0x95, 0x78,       //   Report Count (120),
        0x75, 0x01,       //   Report Size (1),
        0x15, 0x00,       //   Logical Minimum (0),
        0x25, 0x01,       //   Logical Maximum(1),
        0x05, 0x07,       //   Usage Page (Key Codes),
        0x19, 0x00,       //   Usage Minimum (0),
        0x29, 0x77,       //   Usage Maximum (),
        0x81, 0x02,       //   Input (Data, Variable, Absolute),
#if 1
        // LED output report
        0x95, 0x05,       //   Report Count (5),
        0x75, 0x01,       //   Report Size (1),
        0x05, 0x08,       //   Usage Page (LEDs),
        0x19, 0x01,       //   Usage Minimum (1),
        0x29, 0x05,       //   Usage Maximum (5),
        0x91, 0x02,       //   Output (Data, Variable, Absolute),
        0x95, 0x01,       //   Report Count (1),
        0x75, 0x03,       //   Report Size (3),
        0x91, 0x03,       //   Output (Constant),
#endif
        0xC0  ,                 //   End Collection

#if 1
        //	RAW HID
	0x06, LSB(RAWHID_USAGE_PAGE), MSB(RAWHID_USAGE_PAGE),	// 30
	0x0A, LSB(RAWHID_USAGE), MSB(RAWHID_USAGE),

	0xA1, 0x01,				// Collection 0x01
    0x85, 0x02,             // REPORT_ID (3)
	0x75, 0x08,				// report size = 8 bits
	0x15, 0x00,				// logical minimum = 0
	0x26, 0xFF, 0x00,		// logical maximum = 255

	0x95, 32,				// report count TX
	0x09, 0x01,				// usage
	0x81, 0x02,				// Input (array)

	0x95, 32,				// report count RX
	0x09, 0x02,				// usage
	0x91, 0x02,				// Output (array)
	0xC0					// end collection
#endif
};
```



![bushound](D:\UnderwayProject\MiniWitch\note\图\bushound.png)