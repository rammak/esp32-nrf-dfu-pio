#ifndef DFU_REQ_HANDLER_H__
#define DFU_REQ_HANDLER_H__

#include <Arduino.h>
#include "dfu_types.h"

#define INIT_COMMAND_MAX_SIZE       256

class esp32_dfu_req_handler {
public:
    ctr_response process_command(const char *cmd, uint16_t len);
private:
    nrf_dfu_response_select_t on_cmd_obj_select_request(nrf_dfu_op_t * p_req, nrf_dfu_result_t * p_res);
    ctr_response create_response(uint8_t cmd, uint8_t ret_val, uint8_t *data, uint16_t len);
};







#endif //DFU_REQ_HANDLER_H__