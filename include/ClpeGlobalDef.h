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

/**********************************************************************
  This is the ClpeServerUart Class Header of CanLab CLPE Client API. 
**********************************************************************/

#ifndef ClpeGlobalDef_h
#define ClpeGlobalDef_h


/* Command ID */
#define     SOCKET_PACKET_ID_PC_TO_XAVIER   (0x48)
#define     SOCKET_PACKET_ID_XAVIER_TO_PC   (0x49)

#if 0
#define     CMD_ID_GET_SER_LOCK_STAUS       (0x01)
#define     CMD_ID_GET_MICOM_FIRM_VERSION   (0x02)
#define     CMD_ID_REQ_POWER_OFF            (0x03)
#define     CMD_ID_REQ_PC_POWER_ON          (0x04)
#define     CMD_ID_SET_FPS                  (0x05)
#define     CMD_ID_GET_XAVIER_VERSION       (0x06)
#define     CMD_ID_SET_TIME_SYNC            (0x07)
#define     CMD_ID_REQ_START_STREAM         (0x08)
#define     CMD_ID_REQ_STOP_STREAM          (0x09)
#define     CMD_ID_GET_EEPROM_DATA          (0x0A)
#else
#define     CMD_ID_GET_SER_LOCK_STAUS       (0x01)
#define     CMD_ID_GET_MICOM_FIRM_VERSION   (0x02)
#define     CMD_ID_REQ_POWER_OFF            (0x03)
#define     CMD_ID_REQ_PC_POWER_ON          (0x04)
#define     CMD_ID_SET_FPS                  (0x05)
#define     CMD_ID_GET_EEPROM_DATA          (0x06)
#define     CMD_ID_UART_MAX                 (CMD_ID_GET_EEPROM_DATA)        
#define     CMD_ID_GET_XAVIER_VERSION       (CMD_ID_UART_MAX+1)
#define     CMD_ID_SET_TIME_SYNC            (CMD_ID_UART_MAX+2)
#define     CMD_ID_REQ_START_STREAM         (CMD_ID_UART_MAX+3)
#define     CMD_ID_REQ_STOP_STREAM          (CMD_ID_UART_MAX+4)
//#define     CMD_ID_GET_EEPROM_DATA          (CMD_ID_UART_MAX+5)
#define     CMD_ID_GET_MCU_ID               (CMD_ID_UART_MAX+6)     // no need it in pc
#define     CMD_ID_REQ_RESYNC_TIME          (CMD_ID_UART_MAX+7)
#endif

/* Xavier to PC command message size */
#define     SOCKET_CMD_TX_PAYLOAD_SIZE_NORMAL    (0)
#define     SOCKET_CMD_TX_PAYLOAD_SIZE_MAX       (1)
#define     SOCKET_CMD_TX_PACKET_SIZE_NORMAL     (SOCKET_CMD_TX_PAYLOAD_SIZE_NORMAL + 5)
#define     SOCKET_CMD_TX_PACKET_SIZE_MAX        (SOCKET_CMD_TX_PAYLOAD_SIZE_MAX + 5)
#define     SOCKET_CMD_RX_PAYLOAD_SIZE_NORMAL    (8)
#define     SOCKET_CMD_RX_PAYLOAD_SIZE_MAX       (108)//(96)
#define     SOCKET_CMD_RX_PACKET_SIZE_NORMAL     (SOCKET_CMD_RX_PAYLOAD_SIZE_NORMAL + 5)
#define     SOCKET_CMD_RX_PACKET_SIZE_MAX        (SOCKET_CMD_RX_PAYLOAD_SIZE_MAX + 5)

#define     MCU_ID_MASTER   0
#define     MCU_ID_SLAVE    1

#endif // #ifndef ClpeGlobalDef_h
