/**
 * @file cpp_uni_logger.h
 * @author Sledoff (norscreecs@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2025-11-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef CPP_UNI_LOGGER_H_
#define CPP_UNI_LOGGER_H_

#include <cstdint>
#include <iostream>
#include <filesystem>
#include <string.h>

namespace fs = std::filesystem;

enum msg_level : uint8_t
{
    SIMPLE_MSG = 0,
    FATAL_ERROR_MSG = 1,
    ERROR_MSG = 2,
    WARNING_MSG = 3,
    INFO_MSG = 4,
    DEBUG_MSG = 5
};

class cpp_uni_logger
{
private:
    static cpp_uni_logger* instance;

    cpp_uni_logger(cpp_uni_logger &obj) = delete;
    ~cpp_uni_logger() = delete;
    cpp_uni_logger();

    std::string file_path = "log/";
    msg_level log_level = ERROR_MSG;
    bool rewrite_flag = true;
public:
    static cpp_uni_logger* get_instance(){
        if(instance == nullptr)
            instance = new cpp_uni_logger();
        return instance;
    }
    int set_log_level(msg_level level);
    void set_rewrite_flag(bool flag);
    int set_file_path(const std::string& file_path);

    int create_log_file();
    int create_log_file(const std::string& file_name);
    int create_log_file(const std::string& file_name, msg_level level);

    int print_info(const std::string& msg, msg_level level);

};
#endif