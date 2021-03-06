/*
 * Copyright (c) Jan Pochyla, SatoshiLabs
 *
 * Licensed under TREZOR License
 * see LICENSE file for details
 */

#ifndef __TREZORHAL_USB_H__
#define __TREZORHAL_USB_H__

#include <stdint.h>

#define USB_EP_DIR_OUT 0x00
#define USB_EP_DIR_IN  0x80
#define USB_EP_DIR_MSK 0x80

typedef struct __attribute__((packed)) {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t bcdUSB;
    uint8_t bDeviceClass;
    uint8_t bDeviceSubClass;
    uint8_t bDeviceProtocol;
    uint8_t bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t iManufacturer;
    uint8_t iProduct;
    uint8_t iSerialNumber;
    uint8_t bNumConfigurations;
} usb_device_descriptor_t;

typedef struct __attribute__((packed)) {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t wData;
} usb_langid_descriptor_t;

typedef struct __attribute__((packed)) {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t wTotalLength;
    uint8_t bNumInterfaces;
    uint8_t bConfigurationValue;
    uint8_t iConfiguration;
    uint8_t bmAttributes;
    uint8_t bMaxPower;
} usb_config_descriptor_t;

typedef struct __attribute__((packed)) {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
} usb_interface_descriptor_t;

typedef struct __attribute__((packed)) {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bFirstInterface;
    uint8_t bInterfaceCount;
    uint8_t bFunctionClass;
    uint8_t bFunctionSubClass;
    uint8_t bFunctionProtocol;
    uint8_t iFunction;
} usb_interface_assoc_descriptor_t;

typedef struct __attribute__((packed)) {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bEndpointAddress;
    uint8_t bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t bInterval;
} usb_endpoint_descriptor_t;

typedef enum {
    USB_LANGID_ENGLISH_US = 0x409,
} usb_language_id_t;

typedef struct {
    const uint8_t *manufacturer;
    const uint8_t *product;
    const uint8_t *serial_number;
} usb_dev_string_table_t;

typedef struct {
    uint16_t vendor_id;
    uint16_t product_id;
    uint16_t release_num;
    const uint8_t *manufacturer;
    const uint8_t *product;
    const uint8_t *serial_number;
} usb_dev_info_t;

typedef enum {
    USB_IFACE_TYPE_DISABLED = 0,
    USB_IFACE_TYPE_VCP      = 1,
    USB_IFACE_TYPE_HID      = 2,
} usb_iface_type_t;

#include "usb_hid-defs.h"
#include "usb_vcp-defs.h"

typedef struct {
    union {
        usb_hid_state_t hid;
        usb_vcp_state_t vcp;
    };
    usb_iface_type_t type;
} usb_iface_t;

int usb_init(const usb_dev_info_t *dev_info);
int usb_deinit(void);
int usb_start(void);
int usb_stop(void);

#endif
