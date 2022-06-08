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

/**************************************************
  This is the Example for CanLab CLPE Client API.  
***************************************************/

#include "ClpeClientApi.h"

#define CLPE_TEST_GET_CAM_STATUS		(1)
#define CLPE_TEST_GET_MICOM_VERSION		(CLPE_TEST_GET_CAM_STATUS+1)
#define CLPE_TEST_GET_XAVIER_VERSION	(CLPE_TEST_GET_CAM_STATUS+2)
#define CLPE_TEST_GET_SDK_VERSION		(CLPE_TEST_GET_CAM_STATUS+3)
#define CLPE_TEST_GET_EEPROM_DATA		(CLPE_TEST_GET_CAM_STATUS+4)
#define CLPE_TEST_REQ_XAVIER_OFF		(CLPE_TEST_GET_CAM_STATUS+6)
#define CLPE_TEST_CHECK_TIME_SYNC		(CLPE_TEST_REQ_XAVIER_OFF+1)
#define CLPE_TEST_CHECK_PCI_CONNECT		(CLPE_TEST_REQ_XAVIER_OFF+2)
#define CLPE_TEST_CHECK_NETWORK_CONNECT	(CLPE_TEST_REQ_XAVIER_OFF+3)
#define CLPE_TEST_CHECK_PING_TO_XAVIER	(CLPE_TEST_REQ_XAVIER_OFF+4)
#define CLPE_TEST_REQ_RESYNC_TIME		(CLPE_TEST_REQ_XAVIER_OFF+5)
#define CLPE_TEST_START_STREAM			(CLPE_TEST_REQ_RESYNC_TIME+1)
#define CLPE_TEST_STOP_STREAM			(CLPE_TEST_REQ_RESYNC_TIME+2)
#define CLPE_TEST_GET_FRAME_ONE_CAM		(CLPE_TEST_REQ_RESYNC_TIME+3)
#define CLPE_TEST_GET_FRAME_ALL_CAM		(CLPE_TEST_REQ_RESYNC_TIME+4)
#define CLPE_TEST_MAX					(CLPE_TEST_GET_FRAME_ALL_CAM)

//#define USE_NO_PASSWORD

/** You can get frame by make custom function **/
/** This function will be used start stream **/
int Clpe_GetFrameExample(unsigned int inst, unsigned char* buffer, unsigned int size, struct timeval* camera_timeStamp)
{
	/* You can insert your code */

	return 0;
}
  
int main() 
{
	int ret = 0;

	char passwordBuff[100] = "";
	string password = "";

	ClpeClientApi clpe_api;	

	printf("===================================================================================\n");
	printf("                  This is the example for canlab clpe API !!!                      \n");
	printf("===================================================================================\n\n");

	printf("Initial network connection between PC and Xavier...\n");
	printf("You must run this progress at the every first run for using clpe api function !!!\n\n");
#ifndef USE_NO_PASSWORD
	printf("Enter your sudo password : ");
	scanf("%s", passwordBuff);
	printf("\n");

	password = passwordBuff;
#endif
	printf("Wait to initial the clpe network connection...\n");

	/*** network connection between pc and xavier ***/
#ifndef USE_NO_PASSWORD
	ret = clpe_api.Clpe_Connection(password); 	     // input value is PC sudo password
#else
	ret = clpe_api.Clpe_Connection();
#endif
	/*********************************
		< Error status >
		  0 - no error
		 -1 - can not probe driver
		 -2 - can not find network
		 -3 - can not set address
		 -4 - can not ping
		 -5 - can not create socket
		 -6 - can not connect socket
	**********************************/
											    
	if(ret == 0)
	{
		printf("Initial successed.\n\n");
	}
	else
	{
		printf("Failed to initial the clpe network connection. Error number = ( %d )\n\n", ret);
		printf("Exiting application...\n");
		return -1;		
	}

	while(1)
	{
		int selectNum = 0;
		printf("================================ Enter the command ================================\n");
		printf("------------------------------------( Get/Set )------------------------------------\n");
		printf("%d. Get camera status \n", CLPE_TEST_GET_CAM_STATUS);
		printf("%d. Get micom version \n", CLPE_TEST_GET_MICOM_VERSION);
		printf("%d. Get xavier version  \n", CLPE_TEST_GET_XAVIER_VERSION);
		printf("%d. Get SDK version  \n", CLPE_TEST_GET_SDK_VERSION);
		printf("%d. Get EEPROM data  \n", CLPE_TEST_GET_EEPROM_DATA);
		printf("%d. Xavier power off \n", CLPE_TEST_REQ_XAVIER_OFF);
		printf("-------------------------------------( Check )-------------------------------------\n");
		printf("%d. Check time sync \n", CLPE_TEST_CHECK_TIME_SYNC);
		printf("%d. Check pci connection \n", CLPE_TEST_CHECK_PCI_CONNECT);
		printf("%d. Check network connection \n", CLPE_TEST_CHECK_NETWORK_CONNECT);
		printf("%d. Check ping to xavier \n", CLPE_TEST_CHECK_PING_TO_XAVIER);
		printf("%d. Request resync time \n", CLPE_TEST_REQ_RESYNC_TIME);
		printf("-------------------------------------( Stream )------------------------------------\n");
		printf("%d. Start stream \n", CLPE_TEST_START_STREAM);
		printf("%d. Stop stream \n", CLPE_TEST_STOP_STREAM);
		printf("%d. Get frame one cam \n", CLPE_TEST_GET_FRAME_ONE_CAM);
		printf("%d. Get frame all cam  \n", CLPE_TEST_GET_FRAME_ALL_CAM);
		printf("-----------------------------------------------------------------------------------\n");
		printf("0. Exit \n");
		printf("-----------------------------------------------------------------------------------\n");
		printf("Select Command : ");
		scanf("%d", &selectNum);
		printf("\n");

		if(selectNum == 0)
		{
			printf("<::::: Result :::::> Exit application\n\n");
			break;
		}
		if(selectNum > CLPE_TEST_MAX)
		{
			printf("<::::: Error :::::> Invalid Command Number : %d \n\n", selectNum);
			continue;
		}

		if(selectNum == CLPE_TEST_GET_CAM_STATUS) /* Get camera lock status of five(5) cameras */
		{
			int *camStat = (int*) calloc(4, sizeof(int));

			ret = clpe_api.Clpe_GetCamStatus(camStat); 
			if(ret == 0)
			{
				printf("<::::: Result :::::> Camera Status [1] = %d, [2] = %d, [3] = %d, [4] = %d \n\n", camStat[0], camStat[1], camStat[2], camStat[3]);
			}
			else
			{
				printf("<::::: Error :::::> Get Camera Status error num [ %d ]\n\n", ret);
			}

			free(camStat);
		}
		if(selectNum == CLPE_TEST_GET_MICOM_VERSION) /* Get firmware version of micom */
		{
			unsigned char *micomVer_master = (unsigned char*) malloc(6);

			ret = clpe_api.Clpe_GetMicomVersion(micomVer_master);
			if(ret == 0)
			{
				printf("<::::: Result :::::> Master Micom Version = %s  \n\n", micomVer_master);
			}
			else
			{
				printf("<::::: Error :::::> Get Micom Version error num [ %d ]\n\n", ret);
			}

			free(micomVer_master);
		}
		if(selectNum == CLPE_TEST_GET_XAVIER_VERSION) /* Get firmware version of xavier */
		{
			unsigned char *xavierVer_master = (unsigned char*) malloc(6);

			ret = clpe_api.Clpe_GetXavierVersion(xavierVer_master);		
			if(ret == 0)
			{
				printf("<::::: Result :::::> Master Xavier Version = %s  \n\n", xavierVer_master);
			}
			else
			{
				printf("<::::: Error :::::> Get Xavier Version error num [ %d ]\n\n", ret);
			}

			free(xavierVer_master);
		}
		if(selectNum == CLPE_TEST_GET_SDK_VERSION) /* Get firmware version of xavier */
		{
			unsigned char *sdkVer = (unsigned char*) malloc(6);

			ret = clpe_api.Clpe_GetSDKVersion(sdkVer);
			if(ret == 0)
			{
				printf("<::::: Result :::::> SDK Version = %s\n\n", sdkVer);
			}

			free(sdkVer);
		}
		if(selectNum == CLPE_TEST_GET_EEPROM_DATA) /* Get firmware version of xavier */
		{
			unsigned char *eepromData = (unsigned char*) malloc(107);
			int camId;

			while(1)
			{
				printf("Set camId to (0 ~ 3) : ");
				scanf("%d", &camId);
				printf("\n");

				if((camId < 0) || (camId > 3))
				{
					printf("<::::: Error :::::> camId value available from 0 to 3 ! Try again\n");
				}
				else
				{
					break;
				}
			}

			ret = clpe_api.Clpe_GetEepromData(camId, eepromData);

			/*********************************
				< Error status >
				 0 - no error
			**********************************/			
			if(ret == 0)
			{
				printf("<::::: Result :::::> Eeprom data !! \n");				
				for(int i = 0; i < 107; i++)
				{
					printf("[%02d]0x%x(%c)	", i, eepromData[i], eepromData[i]);
					if(((i + 1) % 4) == 0)
					{
						printf("\n");
					}
						
				}
				printf("\n");
			}
			else
			{
				printf("<::::: Error :::::> Get Eeprom data error num [ %d ]\n\n", ret);
			}

			free(eepromData);
		}
		if(selectNum == CLPE_TEST_REQ_XAVIER_OFF) /* Set xavier power off */
		{
			ret = clpe_api.Clpe_SetXavierPowerOff();
			if(ret == 0)
			{
				printf("<::::: Result :::::> Xavier power off success ! Check the LED is off\n\n");
				break;
			}
			else
			{
				printf("<::::: Error :::::> Set Xavier Power Off error num [ %d ]\n\n", ret);
			}
		}
		if(selectNum == CLPE_TEST_CHECK_TIME_SYNC) /* Check chrony sync */
		{
			printf("This takes about 10 ~ 20 seconds.\n");
			ret = clpe_api.Clpe_CheckTimeSyncStatus();
			if(ret == 0)
			{
				printf("<::::: Result :::::> Time is synced.\n\n");
			}
			else
			{
				printf("<::::: Error :::::> Time is not synced. Error number = ( %d )\n\n", ret);
			}
		}
		if(selectNum == CLPE_TEST_CHECK_PCI_CONNECT) /* Check pci connection */
		{
			ret = clpe_api.Clpe_CheckPci();
			if(ret == 0)
			{
				printf("<::::: Result :::::> pci device is connected.\n\n");
			}
			else
			{
				printf("<::::: Error :::::> pci device is not connected. Error number = ( %d )\n\n", ret);
			}
		}
		if(selectNum == CLPE_TEST_CHECK_NETWORK_CONNECT) /* Check network connection */
		{
			ret = clpe_api.Clpe_CheckNetwork();
			
			/*********************************
			< Error status >
			  0 - no error
			 -1 - check network connection error
			**********************************/
			if(ret == 0)
			{
				printf("<::::: Result :::::> network device is connected.\n\n");
			}
			else
			{
				printf("<::::: Error :::::> network device is not connected. Error number = ( %d )\n\n", ret);
			}
		}
		if(selectNum == CLPE_TEST_CHECK_PING_TO_XAVIER) /* Check ping to Xavier */
		{
			ret = clpe_api.Clpe_CheckPing();
			if(ret == 0)
			{
				printf("<::::: Result :::::> ping successed.\n\n");
			}
			else
			{
				printf("<::::: Error :::::> ping failed. Error number = ( %d )\n\n", ret);
			}
		}
		if(selectNum == CLPE_TEST_REQ_RESYNC_TIME) /* Check chrony sync */
		{
			ret = clpe_api.Clpe_ReqResyncTime();
			if(ret == 0)
			{
				printf("<::::: Result :::::> Time resync successed.\n\n");
			}
			else
			{
				printf("<::::: Error :::::> Time resync failed. Error number = ( %d )\n\n", ret);
			}
		}
		if(selectNum == CLPE_TEST_START_STREAM) /* Start stream cam you want to stream */
		{
			int camNum[4] = {0, };
			int display_on;
			
			printf("stream < cam 1 >  1(yes) or 0(no) : ");
			scanf("%d", &camNum[0]);
			printf("\n");
			printf("stream < cam 2 >  1(yes) or 0(no) : ");
			scanf("%d", &camNum[1]);
			printf("\n");
			printf("stream < cam 3 >  1(yes) or 0(no) : ");
			scanf("%d", &camNum[2]);
			printf("\n");
			printf("stream < cam 4 >  1(yes) or 0(no) : ");
			scanf("%d", &camNum[3]);
			printf("\n");
			printf("display on  1(yes) or 0(no) : ");
			scanf("%d", &display_on);
			printf("\n");

			ret = clpe_api.Clpe_StartStream(Clpe_GetFrameExample, camNum[0], camNum[1], camNum[2], camNum[3], display_on);
			if(ret == 0)
			{
				printf("<::::: Result :::::> stream start successed.\n\n");
			}
			else
			{
				printf("<::::: Error :::::> stream start failed. Error number = ( %d )\n\n", ret);
			}
		}
		if(selectNum == CLPE_TEST_STOP_STREAM) /* Stop stream all the cam */
		{
			ret = clpe_api.Clpe_StopStream();
			if(ret == 0)
			{
				printf("<::::: Result :::::> stream stop successed.\n\n");
			}
			else
			{
				printf("<::::: Error :::::> stream stop failed. Error number = ( %d )\n\n", ret);
			}
		}
		if(selectNum == CLPE_TEST_GET_FRAME_ONE_CAM) /* Get frame from one of streaming cam you choose */
		{
            int camera_id = 0;
            unsigned char *p_buffer;
            unsigned int size;
            struct timeval t_camera_timeStamp;
            struct tm  ltm_frame;
	        int fd;
	        static int cntId = 0;
	        char fileNameBuffer[256] = {0, };

			printf("enter cam number to get the frame (0 ~ 3): ");
			scanf("%d", &camera_id);
			printf("\n");

			ret = clpe_api.Clpe_GetFrameOneCam(camera_id, &(p_buffer), &size, &t_camera_timeStamp);
			if(ret == 0)
			{
        	    sprintf(fileNameBuffer, "../capture/camid_%d_count_%d.raw", camera_id, cntId);
                fd = open(fileNameBuffer, O_CREAT | O_RDWR | O_TRUNC);
        	    write(fd, p_buffer, size);
        	    cntId++;
        	    close(fd);
                localtime_r(&t_camera_timeStamp.tv_sec, &ltm_frame);

				printf("<::::: Result :::::> frame get successed.\n\n");
			}
			else
			{
				printf("<::::: Error :::::> frame get failed. Error number = ( %d )\n\n", ret);
			}
		}
		if(selectNum == CLPE_TEST_GET_FRAME_ALL_CAM) /* Get frame from all of streaming cam */
		{
            int camera_id = 0;
            unsigned char *p_buffer;
            unsigned int size;
            struct timeval t_camera_timeStamp;
            struct tm  ltm_frame;
	        int fd;
	        static int cntAny = 0;
	        char fileNameBuffer[256] = {0, };

			ret = clpe_api.Clpe_GetFrameAllCam(&camera_id, &(p_buffer), &size, &t_camera_timeStamp);
			if(ret == 0)
			{
        	    sprintf(fileNameBuffer, "../capture/camid_%d_count_%d.raw", camera_id, cntAny);
                fd = open(fileNameBuffer, O_CREAT | O_RDWR | O_TRUNC);
        	    write(fd, p_buffer, size);
        	    cntAny++;
        	    close(fd);
                localtime_r(&t_camera_timeStamp.tv_sec, &ltm_frame);

				printf("<::::: Result :::::> frame get successed.\n\n");
			}
			else
			{
				printf("<::::: Error :::::> frame get failed. Error number = ( %d )\n\n", ret);
			}
		}
	}
	
	printf("Exiting application...\n");

	return 0;
}
