#pragma once
// file_transfer.h
#ifndef FILE_TRANSFER_H
#define FILE_TRANSFER_H

#include <string>

// 客户端函数
void client_send_file(const std::string& filename);

// 服务端函数
void server_receive_file();

#endif // FILE_TRANSFER_H
