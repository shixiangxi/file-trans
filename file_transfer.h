#pragma once
// file_transfer.h
#ifndef FILE_TRANSFER_H
#define FILE_TRANSFER_H

#include <string>

// �ͻ��˺���
void client_send_file(const std::string& filename);

// ����˺���
void server_receive_file();

#endif // FILE_TRANSFER_H
