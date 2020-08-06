#ifndef DFU_TYPES_H__
#define DFU_TYPES_H__

#include <Arduino.h>
/**
 * @brief DFU object types.
 */
typedef enum
{
    NRF_DFU_OBJ_TYPE_INVALID,                   //!< Invalid object type.
    NRF_DFU_OBJ_TYPE_COMMAND,                   //!< Command object.
    NRF_DFU_OBJ_TYPE_DATA,                      //!< Data object.
} nrf_dfu_obj_type_t;

/**
 * @brief DFU protocol operation.
 */
typedef enum
{
    NRF_DFU_OP_PROTOCOL_VERSION     = 0x00,     //!< Retrieve protocol version.
    NRF_DFU_OP_OBJECT_CREATE        = 0x01,     //!< Create selected object.
    NRF_DFU_OP_RECEIPT_NOTIF_SET    = 0x02,     //!< Set receipt notification.
    NRF_DFU_OP_CRC_GET              = 0x03,     //!< Request CRC of selected object.
    NRF_DFU_OP_OBJECT_EXECUTE       = 0x04,     //!< Execute selected object.
    NRF_DFU_OP_OBJECT_SELECT        = 0x06,     //!< Select object.
    NRF_DFU_OP_MTU_GET              = 0x07,     //!< Retrieve MTU size.
    NRF_DFU_OP_OBJECT_WRITE         = 0x08,     //!< Write selected object.
    NRF_DFU_OP_PING                 = 0x09,     //!< Ping.
    NRF_DFU_OP_HARDWARE_VERSION     = 0x0A,     //!< Retrieve hardware version.
    NRF_DFU_OP_FIRMWARE_VERSION     = 0x0B,     //!< Retrieve firmware version.
    NRF_DFU_OP_ABORT                = 0x0C,     //!< Abort the DFU procedure.
    NRF_DFU_OP_RESPONSE             = 0x60,     //!< Response.
    NRF_DFU_OP_INVALID              = 0xFF,
} nrf_dfu_op_t;

/**
 * @brief DFU operation result code.
 */
typedef enum
{
    NRF_DFU_RES_CODE_INVALID                 = 0x00,    //!< Invalid opcode.
    NRF_DFU_RES_CODE_SUCCESS                 = 0x01,    //!< Operation successful.
    NRF_DFU_RES_CODE_OP_CODE_NOT_SUPPORTED   = 0x02,    //!< Opcode not supported.
    NRF_DFU_RES_CODE_INVALID_PARAMETER       = 0x03,    //!< Missing or invalid parameter value.
    NRF_DFU_RES_CODE_INSUFFICIENT_RESOURCES  = 0x04,    //!< Not enough memory for the data object.
    NRF_DFU_RES_CODE_INVALID_OBJECT          = 0x05,    //!< Data object does not match the firmware and hardware requirements, the signature is wrong, or parsing the command failed.
    NRF_DFU_RES_CODE_UNSUPPORTED_TYPE        = 0x07,    //!< Not a valid object type for a Create request.
    NRF_DFU_RES_CODE_OPERATION_NOT_PERMITTED = 0x08,    //!< The state of the DFU process does not allow this operation.
    NRF_DFU_RES_CODE_OPERATION_FAILED        = 0x0A,    //!< Operation failed.
    NRF_DFU_RES_CODE_EXT_ERROR               = 0x0B,    //!< Extended error. The next byte of the response contains the error code of the extended error (see @ref nrf_dfu_ext_error_code_t.
} nrf_dfu_result_t;

typedef enum
{
    NRF_DFU_FIRMWARE_TYPE_SOFTDEVICE    = 0x00,
    NRF_DFU_FIRMWARE_TYPE_APPLICATION   = 0x01,
    NRF_DFU_FIRMWARE_TYPE_BOOTLOADER    = 0x02,
    NRF_DFU_FIRMWARE_TYPE_UNKNOWN       = 0xFF,
} nrf_dfu_firmware_type_t;

/**
 * @brief @ref NRF_DFU_OP_OBJECT_SELECT response details.
 */
typedef struct
{
    uint32_t max_size;                  //!< Current offset.
    uint32_t offset;                    //!< Current CRC.
    uint32_t crc;                       //!< Maximum size of selected object.
} nrf_dfu_response_select_t;

/**
 * @brief @ref Control characteristic return value.
 */
typedef struct
{
    uint8_t *data;
    uint16_t len;
} ctr_response;

#endif //DFU_TYPES_H__