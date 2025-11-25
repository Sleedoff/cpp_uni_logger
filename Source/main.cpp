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
    logger->simple_msg("This is simple message!");
    logger->fatal_error_msg("This is fatal error message!");
    logger->fatal_error_msg("This is fatal error message with error code!", 10);
    logger->error_msg("This is error message!");
    logger->error_msg("This is error message with error code!", 5);
    logger->warning_msg("This is warning message!");
    logger->info_msg("This is info message!");
    logger->debug_msg("This is debug message!");
    return 0;
}