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


int cpp_uni_logger::set_log_level(msg_level level){
    if(level > DEBUG_MSG)
        return -EINVAL;
    log_level = level;
    return level;
}

void cpp_uni_logger::set_rewrite_flag(bool flag){
    rewrite_flag = flag;
}

int cpp_uni_logger::set_file_path(std::string u_file_path){
    std::string buf = u_file_path.substr(u_file_path.size() - 1, 1);
    if(std::strcmp(buf.c_str(), "/") != 0)
        u_file_path.insert(u_file_path.size(), "/");
    buf.clear();
    buf = u_file_path.substr(0, 1);
    if(std::strcmp(buf.c_str(), "/") == 0)
        u_file_path.erase(0, 1);
    fs::path fp = u_file_path;
    if(!fs::exists(fp)){
        std::cout << "\033[33m Directory doesn\'t exist! Create directory: " << u_file_path << "\033[0m" << std::endl;  
        fs::create_directory(u_file_path);
        if(!fs::exists(fp)){
            std::cout << "\033[33m Can\'t create directory! \033[0m" << std::endl;
            exit(EPERM);
        }
    }
    file_path = u_file_path;
    return 0;
}

int cpp_uni_logger::create_log_file(){
    int state = 0;
    state = create_log_file("log");
    return state;
}

int cpp_uni_logger::create_log_file(const std::string &file_name, msg_level level){
    int state = 0;
    state = set_log_level(level);
    if(state != level)
        return state;
    state = create_log_file("log");
    return state;
}

int cpp_uni_logger::create_log_file(const std::string &file_name){
    if(file_name.size() == 0)
        return -EINVAL;
    set_file_path(file_path);
    if(rewrite_flag){
        full_file_name = file_path;
        full_file_name.insert(full_file_name.size(), file_name);
        full_file_name.insert(full_file_name.size(), ".log");
        int fp = open(full_file_name.c_str(), O_WRONLY | O_CREAT | O_APPEND, S_IRWXO | S_IRWXG | S_IRWXU);
        if(fp < 0)
            return -ENOENT;
        close(fp);
    } else{
        bool create_file = false;
        uint8_t add_num = 0;
        while (!create_file){
            full_file_name = file_path;
            full_file_name.insert(full_file_name.size(), file_name);
            if(add_num != 0)
                full_file_name.insert(full_file_name.size(), std::to_string(add_num));
            full_file_name.insert(full_file_name.size(), ".log");
            int fp = open(full_file_name.c_str(), O_RDWR);
            if(fp < 0){
                close(fp);
                fp = open(full_file_name.c_str(), O_RDWR | O_CREAT | O_APPEND, S_IRWXO | S_IRWXG | S_IRWXU);
                if(fp < 0)
                    return -ENOENT;
                close(fp);
                create_file = true;
            }
            close(fp);
            if(add_num < 255)
                add_num++;
            else
                return -EINVAL;
        }
        return 0;
    }
    return 0;
}

int cpp_uni_logger::write_log(const std::string &msg, msg_level level){
    if(level > log_level)
        return -EPERM;
    //make log string
    std::string input_msg;
    std::time_t t = std::time(nullptr);
    char time_buf[100];
    if(std::strftime(time_buf, sizeof(time_buf), "%F %T", std::localtime(&t)))
        input_msg = time_buf;
    switch (level)
    {
    case SIMPLE_MSG:
        input_msg.insert(input_msg.size(), " [MSG] - ");
        break;
    case FATAL_ERROR_MSG:
        input_msg.insert(input_msg.size(), " [FATAL ERROR] - ");
        break;
    case ERROR_MSG:
        input_msg.insert(input_msg.size(), " [ERROR] - ");
        break;
    case WARNING_MSG:
        input_msg.insert(input_msg.size(), " [WARNING] - ");
        break;
    case INFO_MSG:
        input_msg.insert(input_msg.size(), " [INFO] - ");
        break;
    case DEBUG_MSG:
        input_msg.insert(input_msg.size(), " [DEBUG] - ");
        break;
    default:
        return -EINVAL;
        break;
    }
    input_msg.insert(input_msg.size(), msg);
    //open file and write down
    int fp = open(full_file_name.c_str(), O_RDWR);
    if(fp < 0)
        return -ENOENT;
    int wr = write(fp, input_msg.c_str(), input_msg.size());
    if(wr != input_msg.size())
        return -EINVAL;
    close(fp);
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
        std::cout << "\033[37m [MSG] " << msg << "\033[0m" << std::endl;
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
        std::cout << "\033[34m [DEBUG] " << msg << "\033[0m" << std::endl;
        break;
    default:
        return -EINVAL;
        break;
    }
    return 0;
}

int cpp_uni_logger::simple_msg(const std::string &msg){
    return print_info(msg, SIMPLE_MSG);
}

int cpp_uni_logger::fatal_error_msg(const std::string &msg){
    return print_info(msg, FATAL_ERROR_MSG);
}

int cpp_uni_logger::fatal_error_msg(const std::string &msg, int8_t error_num){
    std::string buf_msg;
    buf_msg.insert(0, msg);
    buf_msg.insert(buf_msg.size(), " Return status: ");
    buf_msg.insert(buf_msg.size(), std::to_string(error_num));
    return print_info(buf_msg, FATAL_ERROR_MSG);
}

int cpp_uni_logger::error_msg(const std::string &msg){
    return print_info(msg, ERROR_MSG);
}

int cpp_uni_logger::error_msg(const std::string &msg, int8_t error_num){
    std::string buf_msg;
    buf_msg.insert(0, msg);
    buf_msg.insert(buf_msg.size(), " Return status: ");
    buf_msg.insert(buf_msg.size(), std::to_string(error_num));
    return print_info(buf_msg, ERROR_MSG);
}

int cpp_uni_logger::warning_msg(const std::string &msg){
    return print_info(msg, WARNING_MSG);
}

int cpp_uni_logger::info_msg(const std::string &msg){
    return print_info(msg, INFO_MSG);
}

int cpp_uni_logger::debug_msg(const std::string &msg){
    return print_info(msg, DEBUG_MSG);
}
