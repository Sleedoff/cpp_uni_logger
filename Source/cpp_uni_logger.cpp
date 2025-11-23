/**
 * @file cpp_uni_logger.cpp
 * @author Sledoff (norscreecs@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2025-11-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "cpp_uni_logger.h"

/**
 * @brief Set max log level that will be write into file. Default = ERROR_MSG.
 * 
 * @param level - max log level
 * @return new log level or -EINVAL.
 */
int cpp_uni_logger::set_log_level(msg_level level){
    if(level > DEBUG_MSG)
        return -EINVAL;
    log_level = level;
    return level;
}

/**
 * @brief Flag for rewrite data into file with the same name
 * 
 * @param flag false - for make unique file for every time
 */
void cpp_uni_logger::set_rewrite_flag(bool flag){
    rewrite_flag = flag;
}

int cpp_uni_logger::set_file_path(const std::string &file_path){
    fs::path fp = file_path;
    if((!fs::is_directory(fp)) && (!fs::exists(fp)))
        return -ENOENT;
    return 0;
}

/**
 * @brief Create file for log data with default name "log"
 */
int cpp_uni_logger::create_log_file(){
    int state = 0;
    state = create_log_file("log");
    return state;
}

/**
 * @brief Create file for log data with name from user. And set max log level
 * 
 * @param file_name name of file
 * @param level max log level
 */
int cpp_uni_logger::create_log_file(const std::string &file_name, msg_level level){
    int state = 0;
    state = set_log_level(level);
    if(state != level)
        return state;
    state = create_log_file("log");
    return state;
}

/**
 * @brief main function for create file.
 * 
 * @param file_name name of file
 * @return int 
 */
int cpp_uni_logger::create_log_file(const std::string &file_name){
    if(file_name.size() == 0)
        return -EINVAL;
    if(rewrite_flag){

    }
    if(FILE *file = fopen(file_name.c_str(), "r"))
        fclose(file);
    return 0;
}

/**
   * @brief Print info into terminal
   *
   * @param msg text what will be write into terminal
   * @param level type of message
   * @return 0 - OK, -EINVAL - error
   */
int cpp_uni_logger::print_info(const std::string &msg, msg_level level){
    if(msg.size() == 0)
        return -EINVAL;
    switch (level)
    {
    case SIMPLE_MSG:
        std::cout << "\033[37m [INFO] " << msg << "\033[0m" << std::endl;
        break;
    case FATAL_ERROR_MSG:
        std::cout << "\033[41m [FATAL ERROR] " << msg << "\033[0m" << std::endl;
        break;
    case ERROR_MSG:
        std::cout << "\033[31m [ERROR] " << msg << "\033[0m" << std::endl;
        break;
    case WARNING_MSG:
        std::cout << "\033[33m [WARNING] " << msg << "\033[0m" << std::endl;
        break;
    case INFO_MSG:
        std::cout << "\033[32m [INFO] " << msg << "\033[0m" << std::endl;
        break;
    case DEBUG_MSG:
        std::cout << "\033[43m [DEBUG] " << msg << "\033[0m" << std::endl;
        break;
    default:
        return -EINVAL;
        break;
    }
    return 0;
}