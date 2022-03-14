/* Includes ------------------------------------------------------------------*/
#include "usbd_midi.h"
#include "usbd_desc.h"
#include "usbd_ctlreq.h"


static uint8_t  USBD_MIDI_Init (USBD_HandleTypeDef *pdev,
                               uint8_t cfgidx);

static uint8_t  USBD_MIDI_DeInit (USBD_HandleTypeDef *pdev,
                                 uint8_t cfgidx);

static uint8_t  USBD_MIDI_Setup (USBD_HandleTypeDef *pdev,
                                USBD_SetupReqTypedef *req);

static uint8_t  USBD_MIDI_DataIn (USBD_HandleTypeDef *pdev,
                                 uint8_t epnum);

static uint8_t  USBD_MIDI_DataOut (USBD_HandleTypeDef *pdev,
                                 uint8_t epnum);

static uint8_t  USBD_MIDI_EP0_RxReady (USBD_HandleTypeDef *pdev);

static uint8_t  *USBD_MIDI_GetFSCfgDesc (uint16_t *length);

static uint8_t  *USBD_MIDI_GetHSCfgDesc (uint16_t *length);

static uint8_t  *USBD_MIDI_GetOtherSpeedCfgDesc (uint16_t *length);

static uint8_t  *USBD_MIDI_GetOtherSpeedCfgDesc (uint16_t *length);

uint8_t  *USBD_MIDI_GetDeviceQualifierDescriptor (uint16_t *length);

/* USB Standard Device Descriptor */
__ALIGN_BEGIN static uint8_t USBD_MIDI_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};

/**
  * @}
  */ 

/** @defgroup USBD_MIDI_Private_Variables
  * @{
  */ 


/* MIDI interface class callbacks structure */
USBD_ClassTypeDef  USBD_MIDI =
{
  USBD_MIDI_Init,
  USBD_MIDI_DeInit,
  USBD_MIDI_Setup,
  NULL,                 /* EP0_TxSent, */
  USBD_MIDI_EP0_RxReady,
  USBD_MIDI_DataIn,
  USBD_MIDI_DataOut,
  NULL,
  NULL,
  NULL,     
  USBD_MIDI_GetHSCfgDesc,
  USBD_MIDI_GetFSCfgDesc,
  USBD_MIDI_GetOtherSpeedCfgDesc,
  USBD_MIDI_GetDeviceQualifierDescriptor,
};

/* USB MIDI device Configuration Descriptor */
__ALIGN_BEGIN uint8_t USBD_MIDI_CfgHSDesc[USB_MIDI_CONFIG_DESC_SIZ] __ALIGN_END =
{
  /*Configuration Descriptor*/
  0x09,   /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,      /* bDescriptorType: Configuration */
  USB_MIDI_CONFIG_DESC_SIZ,                /* wTotalLength:no of returned bytes */
  0x00,
  0x02,   /* bNumInterfaces: 2 interface */
  0x01,   /* bConfigurationValue: Configuration value */
  0x00,   /* iConfiguration: Index of string descriptor describing the configuration */
  0xC0,   /* bmAttributes: self powered */
  0x32,   /* MaxPower 0 mA */
  
  /*---------------------------------------------------------------------------*/
  
  /* AudioControl Interface Descriptor */
  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: Interface */
  /* Interface descriptor type */
  0x00,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x00,   /* bNumEndpoints: One endpoints used */
  0x01,   /* bInterfaceClass: MIDI Interface Class */
  0x01,   /* bInterfaceSubClass: Abstract Control Model */
  0x00,   /* bInterfaceProtocol: Common AT commands */
  0x00,   /* iInterface: */
  
  /*Header Functional Descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x01,   /* bDescriptorSubtype: Header Func Desc */
  0x00,
  0x01,
  0x09,
  0x00,
  0x01,
  0x01,
  
  /* MIDIStreaming interface descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
  0x01,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  0x01,   /* bInterfaceClass: AUDIO */
  0x03,   /* bInterfaceSubClass: MS */
  0x00,   /* bInterfaceProtocol: */
  0x00,   /* iInterface: */

  /* Class-specific MS Interface Descriptor */
  0x07, /* length of descriptor in bytes */
  0x24, /* descriptor type */
  0x01, /* header functional descriptor */
  0x00, /* bcdADC */
  0x01,
  0x41, /* wTotalLength */
  0x00,

  /* MIDI IN Jack Descriptor */
  0x06, /* bLength */
  0x24, /* descriptor type */
  0x02, /* MIDI_IN_JACK desc subtype */
  0x01, /* EMBEDDED bJackType */
  0x01, /* bJackID */
  0x00, /* iJack */

  0x06, /* bLength */
  0x24, /* descriptor type */
  0x02, /* MIDI_IN_JACK desc subtype */
  0x02, /* EXTERNAL bJackType */
  0x02, /* bJackID */
  0x00, /* iJack */

  /* MIDI OUT Jack Descriptor */
  0x09, /* length of descriptor in bytes */
  0x24, /* descriptor type */
  0x03, /* MIDI_OUT_JACK descriptor */
  0x01, /* EMBEDDED bJackType */
  0x03, /* bJackID */
  0x01, /* No of input pins */
  0x02, /* BaSourceID */
  0x01, /* BaSourcePin */
  0x00, /* iJack */

  0x09, /* bLength of descriptor in bytes */
  0x24, /* bDescriptorType */
  0x03, /* MIDI_OUT_JACK bDescriptorSubtype */
  0x02, /* EXTERNAL bJackType */
  0x04, /* bJackID */
  0x01, /* bNrInputPins */
  0x01, /* baSourceID (0) */
  0x01, /* baSourcePin (0) */
  0x00, /* iJack */

  /* Bulk IN Endpoint Descriptors */
  0x09, /* bLenght */
  USB_DESC_TYPE_ENDPOINT, /* bDescriptorType = endpoint */
  0x01, /* bEndpointAddress OUT endpoint number 1 */
  0x03, /* bmAttributes: 2:Bulk, 3:Interrupt endpoint */
  0x08, /* wMaxPacketSize */
  0x00,
  0x0A, /* bInterval in ms */
  0x00, /* bRefresh */
  0x00, /* bSyncAddress */

  /* Class-specific MS Bulk OUT Endpoint Descriptor */
  0x05, /* bLength of descriptor in bytes */
  0x25, /* bDescriptorType */
  0x01, /* bDescriptorSubtype */
  0x01, /* bNumEmbMIDIJack  */
  0x01, /* baAssocJackID (0) */

  /* Bulk IN Endpoint Descriptors */
  0x09, /* bLenght */
  USB_DESC_TYPE_ENDPOINT, /* bDescriptorType = endpoint */
  0x81, /* bEndpointAddress IN endpoint number 1 */
  0x03, /* bmAttributes: 2: Bulk, 3: Interrupt endpoint */
  0x08, /* wMaxPacketSize */
  0x00,
  0x0A, /* bInterval in ms */
  0x00, /* bRefresh */
  0x00, /* bSyncAddress */

  /* Class-specific MS Bulk IN Endpoint Descriptor */
  0x05, /* bLength of descriptor in bytes */
  0x25, /* bDescriptorType */
  0x01, /* bDescriptorSubtype */
  0x01, /* bNumEmbMIDIJack (0) */
  0x03, /* baAssocJackID (0) */
} ;


/* USB MIDI device Configuration Descriptor */
__ALIGN_BEGIN uint8_t USBD_MIDI_CfgFSDesc[USB_MIDI_CONFIG_DESC_SIZ] __ALIGN_END =
{
  /*Configuration Descriptor*/
  0x09,   /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,      /* bDescriptorType: Configuration */
  USB_MIDI_CONFIG_DESC_SIZ,                /* wTotalLength:no of returned bytes */
  0x00,
  0x02,   /* bNumInterfaces: 2 interface */
  0x01,   /* bConfigurationValue: Configuration value */
  0x00,   /* iConfiguration: Index of string descriptor describing the configuration */
  0xC0,   /* bmAttributes: self powered */
  0x32,   /* MaxPower 0 mA */
  
  /*---------------------------------------------------------------------------*/
  
  /* AudioControl Interface Descriptor */
  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: Interface */
  /* Interface descriptor type */
  0x00,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x00,   /* bNumEndpoints: One endpoints used */
  0x01,   /* bInterfaceClass: MIDI Interface Class */
  0x01,   /* bInterfaceSubClass: Abstract Control Model */
  0x00,   /* bInterfaceProtocol: Common AT commands */
  0x00,   /* iInterface: */
  
  /*Header Functional Descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x01,   /* bDescriptorSubtype: Header Func Desc */
  0x00,
  0x01,
  0x09,
  0x00,
  0x01,
  0x01,
  
  /* MIDIStreaming interface descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
  0x01,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  0x01,   /* bInterfaceClass: AUDIO */
  0x03,   /* bInterfaceSubClass: MS */
  0x00,   /* bInterfaceProtocol: */
  0x00,   /* iInterface: */

  /* Class-specific MS Interface Descriptor */
  0x07, /* length of descriptor in bytes */
  0x24, /* descriptor type */
  0x01, /* header functional descriptor */
  0x00, /* bcdADC */
  0x01,
  0x41, /* wTotalLength */
  0x00,

  /* MIDI IN Jack Descriptor */
  0x06, /* bLength */
  0x24, /* descriptor type */
  0x02, /* MIDI_IN_JACK desc subtype */
  0x01, /* EMBEDDED bJackType */
  0x01, /* bJackID */
  0x00, /* iJack */

  0x06, /* bLength */
  0x24, /* descriptor type */
  0x02, /* MIDI_IN_JACK desc subtype */
  0x02, /* EXTERNAL bJackType */
  0x02, /* bJackID */
  0x00, /* iJack */

  /* MIDI OUT Jack Descriptor */
  0x09, /* length of descriptor in bytes */
  0x24, /* descriptor type */
  0x03, /* MIDI_OUT_JACK descriptor */
  0x01, /* EMBEDDED bJackType */
  0x03, /* bJackID */
  0x01, /* No of input pins */
  0x02, /* BaSourceID */
  0x01, /* BaSourcePin */
  0x00, /* iJack */

  0x09, /* bLength of descriptor in bytes */
  0x24, /* bDescriptorType */
  0x03, /* MIDI_OUT_JACK bDescriptorSubtype */
  0x02, /* EXTERNAL bJackType */
  0x04, /* bJackID */
  0x01, /* bNrInputPins */
  0x01, /* baSourceID (0) */
  0x01, /* baSourcePin (0) */
  0x00, /* iJack */

  /* Bulk IN Endpoint Descriptors */
  0x09, /* bLenght */
  USB_DESC_TYPE_ENDPOINT, /* bDescriptorType = endpoint */
  0x01, /* bEndpointAddress OUT endpoint number 1 */
  0x03, /* bmAttributes: 2:Bulk, 3:Interrupt endpoint */
  0x08, /* wMaxPacketSize */
  0x00,
  0x01, /* bInterval in ms */
  0x00, /* bRefresh */
  0x00, /* bSyncAddress */

  /* Class-specific MS Bulk OUT Endpoint Descriptor */
  0x05, /* bLength of descriptor in bytes */
  0x25, /* bDescriptorType */
  0x01, /* bDescriptorSubtype */
  0x01, /* bNumEmbMIDIJack  */
  0x01, /* baAssocJackID (0) */

  /* Bulk IN Endpoint Descriptors */
  0x09, /* bLenght */
  USB_DESC_TYPE_ENDPOINT, /* bDescriptorType = endpoint */
  0x81, /* bEndpointAddress IN endpoint number 1 */
  0x03, /* bmAttributes: 2: Bulk, 3: Interrupt endpoint */
  0x08, /* wMaxPacketSize */
  0x00,
  0x01, /* bInterval in ms */
  0x00, /* bRefresh */
  0x00, /* bSyncAddress */

  /* Class-specific MS Bulk IN Endpoint Descriptor */
  0x05, /* bLength of descriptor in bytes */
  0x25, /* bDescriptorType */
  0x01, /* bDescriptorSubtype */
  0x01, /* bNumEmbMIDIJack (0) */
  0x03, /* baAssocJackID (0) */
} ;

__ALIGN_BEGIN uint8_t USBD_MIDI_OtherSpeedCfgDesc[USB_MIDI_CONFIG_DESC_SIZ] __ALIGN_END =
{ 
  0x09,   /* bLength: Configuation Descriptor size */
  USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION,   
  USB_MIDI_CONFIG_DESC_SIZ,
  0x00,
  0x02,   /* bNumInterfaces: 2 interfaces */
  0x01,   /* bConfigurationValue: */
  0x04,   /* iConfiguration: */
  0xC0,   /* bmAttributes: */
  0x32,   /* MaxPower 100 mA */  
  
  /*Interface Descriptor */
  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: Interface */
  /* Interface descriptor type */
  0x00,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x01,   /* bNumEndpoints: One endpoints used */
  0x02,   /* bInterfaceClass: Communication Interface Class */
  0x02,   /* bInterfaceSubClass: Abstract Control Model */
  0x01,   /* bInterfaceProtocol: Common AT commands */
  0x00,   /* iInterface: */
  
  /*Header Functional Descriptor*/
  0x05,   /* bLength: Endpoint Descriptor size */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x00,   /* bDescriptorSubtype: Header Func Desc */
  0x10,   /* bMIDIDC: spec release number */
  0x01,
  
  /*Call Management Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x01,   /* bDescriptorSubtype: Call Management Func Desc */
  0x00,   /* bmCapabilities: D0+D1 */
  0x01,   /* bDataInterface: 1 */
  
  /*ACM Functional Descriptor*/
  0x04,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,   /* bmCapabilities */
  
  /*Union Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x06,   /* bDescriptorSubtype: Union func desc */
  0x00,   /* bMasterInterface: Communication class interface */
  0x01,   /* bSlaveInterface0: Data Class Interface */
  
  /*Endpoint 2 Descriptor*/
  0x07,                           /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT      ,   /* bDescriptorType: Endpoint */
  MIDI_CMD_EP,                     /* bEndpointAddress */
  0x03,                           /* bmAttributes: Interrupt */
  LOBYTE(MIDI_CMD_PACKET_SIZE),     /* wMaxPacketSize: */
  HIBYTE(MIDI_CMD_PACKET_SIZE),
  0xFF,                           /* bInterval: */
  
  /*---------------------------------------------------------------------------*/
  
  /*Data class interface descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
  0x01,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  0x0A,   /* bInterfaceClass: MIDI */
  0x00,   /* bInterfaceSubClass: */
  0x00,   /* bInterfaceProtocol: */
  0x00,   /* iInterface: */
  
  /*Endpoint OUT Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  MIDI_OUT_EP,                        /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  0x40,                              /* wMaxPacketSize: */
  0x00,
  0x00,                              /* bInterval: ignore for Bulk transfer */
  
  /*Endpoint IN Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,     /* bDescriptorType: Endpoint */
  MIDI_IN_EP,                        /* bEndpointAddress */
  0x02,                             /* bmAttributes: Bulk */
  0x40,                             /* wMaxPacketSize: */
  0x00,
  0x00                              /* bInterval */
};

/**
  * @}
  */ 

/** @defgroup USBD_MIDI_Private_Functions
  * @{
  */ 

/**
  * @brief  USBD_MIDI_Init
  *         Initialize the MIDI interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_MIDI_Init (USBD_HandleTypeDef *pdev,
                               uint8_t cfgidx)
{
  uint8_t ret = 0;
  USBD_MIDI_HandleTypeDef   *hmidi;
  
  if(pdev->dev_speed == USBD_SPEED_HIGH  ) 
  {  
    /* Open EP IN */
    USBD_LL_OpenEP(pdev,
                   MIDI_IN_EP,
                   USBD_EP_TYPE_BULK,
                   MIDI_DATA_HS_IN_PACKET_SIZE);
    
    /* Open EP OUT */
    USBD_LL_OpenEP(pdev,
                   MIDI_OUT_EP,
                   USBD_EP_TYPE_BULK,
                   MIDI_DATA_HS_OUT_PACKET_SIZE);
    
  }
  else
  {
    /* Open EP IN */
    USBD_LL_OpenEP(pdev,
                   MIDI_IN_EP,
                   USBD_EP_TYPE_BULK,
                   MIDI_DATA_FS_IN_PACKET_SIZE);
    
    /* Open EP OUT */
    USBD_LL_OpenEP(pdev,
                   MIDI_OUT_EP,
                   USBD_EP_TYPE_BULK,
                   MIDI_DATA_FS_OUT_PACKET_SIZE);
  }
  /* Open Command IN EP */
  USBD_LL_OpenEP(pdev,
                 MIDI_CMD_EP,
                 USBD_EP_TYPE_INTR,
                 MIDI_CMD_PACKET_SIZE);
  
    
  pdev->pClassData = USBD_malloc(sizeof (USBD_MIDI_HandleTypeDef));
  
  if(pdev->pClassData == NULL)
  {
    ret = 1; 
  }
  else
  {
    hmidi = (USBD_MIDI_HandleTypeDef*) pdev->pClassData;
    
    /* Init  physical Interface components */
    ((USBD_MIDI_ItfTypeDef *)pdev->pUserData)->Init();
    
    /* Init Xfer states */
    hmidi->TxState =0;
    hmidi->RxState =0;
       
    if(pdev->dev_speed == USBD_SPEED_HIGH  ) 
    {      
      /* Prepare Out endpoint to receive next packet */
      USBD_LL_PrepareReceive(pdev,
                             MIDI_OUT_EP,
                             hmidi->RxBuffer,
                             MIDI_DATA_HS_OUT_PACKET_SIZE);
    }
    else
    {
      /* Prepare Out endpoint to receive next packet */
      USBD_LL_PrepareReceive(pdev,
                             MIDI_OUT_EP,
                             hmidi->RxBuffer,
                             MIDI_DATA_FS_OUT_PACKET_SIZE);
    }
    
    
  }
  return ret;
}

/**
  * @brief  USBD_MIDI_Init
  *         DeInitialize the MIDI layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_MIDI_DeInit (USBD_HandleTypeDef *pdev,
                                 uint8_t cfgidx)
{
  uint8_t ret = 0;
  
  /* Open EP IN */
  USBD_LL_CloseEP(pdev,
              MIDI_IN_EP);
  
  /* Open EP OUT */
  USBD_LL_CloseEP(pdev,
              MIDI_OUT_EP);
  
  /* Open Command IN EP */
  USBD_LL_CloseEP(pdev,
              MIDI_CMD_EP);
  
  
  /* DeInit  physical Interface components */
  if(pdev->pClassData != NULL)
  {
    ((USBD_MIDI_ItfTypeDef *)pdev->pUserData)->DeInit();
    USBD_free(pdev->pClassData);
    pdev->pClassData = NULL;
  }
  
  return ret;
}

/**
  * @brief  USBD_MIDI_Setup
  *         Handle the MIDI specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t  USBD_MIDI_Setup (USBD_HandleTypeDef *pdev,
                                USBD_SetupReqTypedef *req)
{
  USBD_MIDI_HandleTypeDef   *hmidi = (USBD_MIDI_HandleTypeDef*) pdev->pClassData;
  static uint8_t ifalt = 0;
    
  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
  case USB_REQ_TYPE_CLASS :
    if (req->wLength)
    {
      if (req->bmRequest & 0x80)
      {
        ((USBD_MIDI_ItfTypeDef *)pdev->pUserData)->Control(req->bRequest,
                                                          (uint8_t *)hmidi->data,
                                                          req->wLength);
          USBD_CtlSendData (pdev, 
                            (uint8_t *)hmidi->data,
                            req->wLength);
      }
      else
      {
        hmidi->CmdOpCode = req->bRequest;
        hmidi->CmdLength = req->wLength;
        
        USBD_CtlPrepareRx (pdev, 
                           (uint8_t *)hmidi->data,
                           req->wLength);
      }
      
    }
    else
    {
      ((USBD_MIDI_ItfTypeDef *)pdev->pUserData)->Control(req->bRequest,
                                                        (uint8_t*)req,
                                                        0);
    }
    break;

  case USB_REQ_TYPE_STANDARD:
    switch (req->bRequest)
    {      
    case USB_REQ_GET_INTERFACE :
      USBD_CtlSendData (pdev,
                        &ifalt,
                        1);
      break;
      
    case USB_REQ_SET_INTERFACE :
      break;
    }
    break;
 
  default: 
    break;
  }
  return USBD_OK;
}

/**
  * @brief  USBD_MIDI_DataIn
  *         Data sent on non-control IN endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
static uint8_t  USBD_MIDI_DataIn (USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  USBD_MIDI_HandleTypeDef   *hmidi = (USBD_MIDI_HandleTypeDef*) pdev->pClassData;
  
  if(pdev->pClassData != NULL)
  {
    
    hmidi->TxState = 0;

    return USBD_OK;
  }
  else
  {
    return USBD_FAIL;
  }
}

/**
  * @brief  USBD_MIDI_DataOut
  *         Data received on non-control Out endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
static uint8_t  USBD_MIDI_DataOut (USBD_HandleTypeDef *pdev, uint8_t epnum)
{      
  USBD_MIDI_HandleTypeDef   *hmidi = (USBD_MIDI_HandleTypeDef*) pdev->pClassData;
  
  /* Get the received data length */
  hmidi->RxLength = USBD_LL_GetRxDataSize (pdev, epnum);
  
  /* USB data will be immediately processed, this allow next USB traffic being 
  NAKed till the end of the application Xfer */
  if(pdev->pClassData != NULL)
  {
    ((USBD_MIDI_ItfTypeDef *)pdev->pUserData)->Receive(hmidi->RxBuffer, &hmidi->RxLength);

    return USBD_OK;
  }
  else
  {
    return USBD_FAIL;
  }
}



/**
  * @brief  USBD_MIDI_DataOut
  *         Data received on non-control Out endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
static uint8_t  USBD_MIDI_EP0_RxReady (USBD_HandleTypeDef *pdev)
{ 
  USBD_MIDI_HandleTypeDef   *hmidi = (USBD_MIDI_HandleTypeDef*) pdev->pClassData;
  
  if((pdev->pUserData != NULL) && (hmidi->CmdOpCode != 0xFF))
  {
    ((USBD_MIDI_ItfTypeDef *)pdev->pUserData)->Control(hmidi->CmdOpCode,
                                                      (uint8_t *)hmidi->data,
                                                      hmidi->CmdLength);
      hmidi->CmdOpCode = 0xFF;
      
  }
  return USBD_OK;
}

/**
  * @brief  USBD_MIDI_GetFSCfgDesc
  *         Return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_MIDI_GetFSCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_MIDI_CfgFSDesc);
  return USBD_MIDI_CfgFSDesc;
}

/**
  * @brief  USBD_MIDI_GetHSCfgDesc
  *         Return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_MIDI_GetHSCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_MIDI_CfgHSDesc);
  return USBD_MIDI_CfgHSDesc;
}

/**
  * @brief  USBD_MIDI_GetCfgDesc
  *         Return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_MIDI_GetOtherSpeedCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_MIDI_OtherSpeedCfgDesc);
  return USBD_MIDI_OtherSpeedCfgDesc;
}

/**
* @brief  DeviceQualifierDescriptor 
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *USBD_MIDI_GetDeviceQualifierDescriptor (uint16_t *length)
{
  *length = sizeof (USBD_MIDI_DeviceQualifierDesc);
  return USBD_MIDI_DeviceQualifierDesc;
}

/**
* @brief  USBD_MIDI_RegisterInterface
  * @param  pdev: device instance
  * @param  fops: CD  Interface callback
  * @retval status
  */
uint8_t  USBD_MIDI_RegisterInterface  (USBD_HandleTypeDef   *pdev,
                                      USBD_MIDI_ItfTypeDef *fops)
{
  uint8_t  ret = USBD_FAIL;
  
  if(fops != NULL)
  {
    pdev->pUserData= fops;
    ret = USBD_OK;    
  }
  
  return ret;
}

/**
  * @brief  USBD_MIDI_SetTxBuffer
  * @param  pdev: device instance
  * @param  pbuff: Tx Buffer
  * @retval status
  */
uint8_t  USBD_MIDI_SetTxBuffer  (USBD_HandleTypeDef   *pdev,
                                uint8_t  *pbuff,
                                uint16_t length)
{
  USBD_MIDI_HandleTypeDef   *hmidi = (USBD_MIDI_HandleTypeDef*) pdev->pClassData;
  
  hmidi->TxBuffer = pbuff;
  hmidi->TxLength = length;
  
  return USBD_OK;  
}


/**
  * @brief  USBD_MIDI_SetRxBuffer
  * @param  pdev: device instance
  * @param  pbuff: Rx Buffer
  * @retval status
  */
uint8_t  USBD_MIDI_SetRxBuffer  (USBD_HandleTypeDef   *pdev,
                                   uint8_t  *pbuff)
{
  USBD_MIDI_HandleTypeDef   *hmidi = (USBD_MIDI_HandleTypeDef*) pdev->pClassData;
  
  hmidi->RxBuffer = pbuff;
  
  return USBD_OK;
}

/**
  * @brief  USBD_MIDI_DataOut
  *         Data received on non-control Out endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
uint8_t  USBD_MIDI_TransmitPacket(USBD_HandleTypeDef *pdev)
{      
  USBD_MIDI_HandleTypeDef   *hmidi = (USBD_MIDI_HandleTypeDef*) pdev->pClassData;
  
  if(pdev->pClassData != NULL)
  {
    if(hmidi->TxState == 0)
    {
      /* Tx Transfer in progress */
      hmidi->TxState = 1;
      
      /* Transmit next packet */
      USBD_LL_Transmit(pdev,
                       MIDI_IN_EP,
                       hmidi->TxBuffer,
                       hmidi->TxLength);
      
      return USBD_OK;
    }
    else
    {
      return USBD_BUSY;
    }
  }
  else
  {
    return USBD_FAIL;
  }
}


/**
  * @brief  USBD_MIDI_ReceivePacket
  *         prepare OUT Endpoint for reception
  * @param  pdev: device instance
  * @retval status
  */
uint8_t  USBD_MIDI_ReceivePacket(USBD_HandleTypeDef *pdev)
{      
  USBD_MIDI_HandleTypeDef   *hmidi = (USBD_MIDI_HandleTypeDef*) pdev->pClassData;
  
  /* Suspend or Resume USB Out process */
  if(pdev->pClassData != NULL)
  {
    if(pdev->dev_speed == USBD_SPEED_HIGH  ) 
    {      
      /* Prepare Out endpoint to receive next packet */
      USBD_LL_PrepareReceive(pdev,
                             MIDI_OUT_EP,
                             hmidi->RxBuffer,
                             MIDI_DATA_HS_OUT_PACKET_SIZE);
    }
    else
    {
      /* Prepare Out endpoint to receive next packet */
      USBD_LL_PrepareReceive(pdev,
                             MIDI_OUT_EP,
                             hmidi->RxBuffer,
                             MIDI_DATA_FS_OUT_PACKET_SIZE);
    }
    return USBD_OK;
  }
  else
  {
    return USBD_FAIL;
  }
}
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
