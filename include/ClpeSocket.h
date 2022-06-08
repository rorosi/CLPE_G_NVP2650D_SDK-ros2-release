/*
 * Copyright (C) 2022 Can-lab Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

// Definition of the Socket class

#ifndef ClpeSocket_class
#define ClpeSocket_class
 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define SOCKET_CLIENT
  
const int MAXCONNECTIONS = 5;

using namespace std;

class ClpeSocket
{
public:
	ClpeSocket();
	virtual ~ClpeSocket();

	// Server initialization
	bool create(int mcu_id);
	bool bind(const char *host ,const int port, int mcu_id);
	bool listen(int mcu_id) const;
	bool accept(ClpeSocket *new_socket, int mcu_id) const;

	// Client initialization
	bool connect(const string host, const int port, int mcu_id);

	// Data Transimission
	bool send(unsigned char *s, int mcu_id) const;
	bool recv(unsigned char *s, int mcu_id) const;

	void close(int mcu_id);

	void set_non_blocking(const bool, int mcu_id);

	bool is_valid_master() const { return m_sock_master != -1; }
    bool is_valid_slave() const { return m_sock_slave!= -1; }

private:
	int m_sock_master;
    int m_sock_slave;
	sockaddr_in m_addr;

};


#endif
