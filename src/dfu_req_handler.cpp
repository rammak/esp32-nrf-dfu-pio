#include "dfu_req_handler.h"

uint8_t select_res[] = {0x60, 0x06, 0x01, 0x00, 0x00, 0x00 , 0x00, 0x00, 0x00, 0x00 , 0x00, 0x00, 0x00, 0x00, 0xff};
uint8_t ret_data[INIT_COMMAND_MAX_SIZE]; //static allotment

ctr_response esp32_dfu_req_handler::process_command(const char *cmd, uint16_t len){
    Serial.printf("Received command - ");
    for(int i = 0; i < len; i++) {
        Serial.print(*(cmd+i), HEX);
        Serial.print(" ");
    }
    Serial.println();
    nrf_dfu_result_t *res;
    ctr_response ret;
    switch (*cmd)
    {
        // case NRF_DFU_OP_OBJECT_CREATE:
        // {
        //     on_cmd_obj_create_request(*cmd, res);
        // } break;

        // case NRF_DFU_OP_CRC_GET:
        // {
        //     on_cmd_obj_crc_request(*cmd, res);
        // } break;

        // case NRF_DFU_OP_OBJECT_WRITE:
        // {
        //     on_cmd_obj_write_request(*cmd, res);
        // } break;

        // case NRF_DFU_OP_OBJECT_EXECUTE:
        // {
        //     on_cmd_obj_execute_request(*cmd, res);
        // } break;

        case NRF_DFU_OP_OBJECT_SELECT:
        {
            nrf_dfu_response_select_t t = on_cmd_obj_select_request((nrf_dfu_op_t *)cmd, res);
            uint8_t *buff = (uint8_t *)malloc(sizeof(t));
            memcpy(buff,(uint8_t*)&t,sizeof(t));
            ret = this->create_response(0x06, 0x01, buff, sizeof(t));
            free(buff);
            return ret;
        } break;

        default:
        {
        } break;
    }
}

nrf_dfu_response_select_t esp32_dfu_req_handler::on_cmd_obj_select_request(nrf_dfu_op_t * p_req, nrf_dfu_result_t * p_res)
{
    Serial.printf("Select command");
    nrf_dfu_response_select_t response;
    response.crc = 0;
    response.max_size = INIT_COMMAND_MAX_SIZE;
    response.offset = 0;
    return response;
}

ctr_response esp32_dfu_req_handler::create_response(uint8_t cmd, uint8_t ret_val, uint8_t *data, uint16_t len){
    ctr_response r;
    ret_data[0] = 0x60;
    ret_data[1] = cmd;
    ret_data[2] = ret_val;
    for(int i = 3; i < len + 3; i++){
        ret_data[i] = *(data+i-3);
    }
    r.len = len + 3;
    r.data = ret_data;
    return r;
}