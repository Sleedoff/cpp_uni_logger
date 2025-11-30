/**
 * @file main.cpp
 * @author Sledoff (norscreecs@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2025-11-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "cpp_uni_logger.h"

int main(){
    cpp_uni_logger* logger = cpp_uni_logger::get_instance();
    logger->set_log_level(DEBUG_MSG);
    int status = logger->create_log_file("test");
    if(status != 0)
        logger->error_msg("Something wrong with function \"create_log_file\" ", status);

    logger->simple_msg("This is simple message!");
    logger->fatal_error_msg("This is fatal error message!");
    logger->fatal_error_msg("This is fatal error message with error code!", 10);
    logger->error_msg("This is error message!");
    logger->error_msg("This is error message with error code!", 5);
    logger->warning_msg("This is warning message!");
    logger->info_msg("This is info message!");
    logger->debug_msg("This is debug message!");

    status = logger->write_log("This is simple message!", SIMPLE_MSG);
    if(status != 0)
        logger->error_msg("Something wrong with function \"write_log\" ", status);
    return 0;
}