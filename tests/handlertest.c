/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include "coap.h"
#include "CommandModule.h"
#include "StreamDataRecorder.h"
#include "Handler.h"
#include "coap_messages_example.h"

#include <stdbool.h>
#include <strings.h>

#define PORT 5683

/*
 * Simple C Test Suite
 */
CRITICAL_SECTION CriticalSection;
SOCKET ReceivingSocket;

uint8_t scratch_b1[] = {
	0x40, 0x01, 0x00, 0x00, 0x61, 0x01, 0x5D, 0x05, 0x73, 0x74, 0x72, 0x65,
	0x61, 0x6D, 0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64,
	0x65, 0x72, 0x40
};
uint8_t scratch_b2[] = {
	0x40, 0x01, 0xFC, 0xB0, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0xC1, 0x06
};
uint8_t scratch_b3[] = {
	0x68, 0x5F, 0xCB, 0xED, 0x54, 0x5D, 0x82, 0x57, 0xE8, 0xE2, 0x11, 0x40,
	0x63, 0x01, 0x0D, 0x78, 0x61, 0x32, 0xB1, 0x0D, 0x52, 0x04, 0xB5
};
uint8_t scratch_b4[] = {
	0x40, 0x01, 0x61, 0xBD, 0xB6, 0x64, 0x65, 0x76, 0x69, 0x63,
	0x65, 0xC1, 0x06, 0x40
};
uint8_t scratch_b5[] = {
	0x58, 0x5F, 0x31, 0x97, 0x30, 0xA5, 0x38, 0x72, 0x2E, 0xBA,
	0xE8, 0x9E, 0x62, 0xDE, 0xBA, 0x61, 0x32, 0xB1, 0x0D, 0x52,
	0x04, 0xB5
};

coap_rw_buffer_t input[4] = {
	{scratch_b1, sizeof (scratch_b1)},
	{scratch_b2, sizeof (scratch_b2)},
	{scratch_b3, sizeof (scratch_b3)},
	{scratch_b4, sizeof (scratch_b4)}
};
coap_rw_buffer_t *messg1, *messg2, *messg3;

void testCoap_make_response()
{
	int i, j = 3;
	for (j = 0; j < 4; j++)
	{
		for (i = 0; i < input[j].len; i++)
		{
			printf("%02X ", input[j].p[i]);
		}
		printf("\n");
		for (i = 0; i < input[j].len; i++)
		{
			printf("%c", input[j].p[i]);
		}
		messg1 = MessageHandlerIntIP(
				&(input[j].p[0]),
				input[j].len,
				0, 0
				);
		printf("\nAnswer\n");
		for (i = 0; i < messg1->len; i++)
		{
			printf("%02X ", messg1->p[i]);
		}
		printf("\n");
		for (i = 0; i < messg1->len; i++)
		{
			printf("%c", messg1->p[i]);
		}
		printf("\n=================================================\n");
	}
}

uint8_t Sender(uint8_t output)
{
	printf("dd: %02X [%c]\n", output);
	return output;
}

uint8_t id = 0x10;
CSMACDController_t contr;
SOCKADDR_IN SenderAddr;
int SenderAddrSize = sizeof (SenderAddr);

DWORD WINAPI ThreadData(LPVOID lpParameter)
{
	int i;
	int ptr = 0;
	while (1)
	{
		Sleep(100); // Sleep three seconds
		// Request ownership of the critical section.
		EnterCriticalSection(&CriticalSection);

		AddSample();

		// Release ownership of the critical section.
		LeaveCriticalSection(&CriticalSection);
	}
	return 1;
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	int i;
	int ptr = 0;
	while (1)
	{
		Sleep(500); // Sleep three seconds
		// Request ownership of the critical section.
		EnterCriticalSection(&CriticalSection);

		messg3 = (coap_rw_buffer_t *) StreamObserverHandler();
		if (messg3 != 0)
		{
			printf("\nAnswer\n");
			for (i = 0; i < messg3->len; i++)
			{
				printf("%02X ", messg3->p[i]);
			}
			printf("\n");
			for (i = 0; i < messg3->len; i++)
			{
				printf("%c", messg3->p[i]);
			}
			printf("\n=================================================\n");
			printf("Server: Total Bytes answered: %d\n", messg3->len);
			if (sendto(
					ReceivingSocket,
					messg3->p,
					messg3->len,
					0,
					(struct sockaddr *) &SenderAddr,
					SenderAddrSize
					) < 0)
			{
				perror("sendto failed");
				return 0;
			}
		}

		// Release ownership of the critical section.
		LeaveCriticalSection(&CriticalSection);
	}
	return 1;
}

int main(int argc, char** argv)
{
	WSADATA wsaData;
	SOCKADDR_IN ReceiverAddr;
	int Port = PORT;
	char ReceiveBuf[1024];
	int BufLength = 1024;
	int ByteReceived = 5, SelectTiming, ErrorCode;
	char ch = 'Y';
	coap_rw_buffer_t *buff;
	int i;

	// Initialize the critical section one time only.
	if (!InitializeCriticalSectionAndSpinCount(&CriticalSection,
			0x00000400))
		return -1;
	// Initialize Winsock version 2.2
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Server: WSAStartup failed with error %ld\n", WSAGetLastError());
		return -1;
	} else
		printf("Server: The Winsock DLL status is %s.\n", wsaData.szSystemStatus);

	// Create a new socket to receive datagrams on.
	ReceivingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (ReceivingSocket == INVALID_SOCKET)
	{
		printf("Server: Error at socket(): %ld\n", WSAGetLastError());
		// Clean up
		WSACleanup();
		// Exit with error
		return -1;
	} else
		printf("Server: socket() is OK!\n");

	// Set up a SOCKADDR_IN structure that will tell bind that we
	// want to receive datagrams from all interfaces using port 5150.
	// The IPv4 family
	ReceiverAddr.sin_family = AF_INET;
	// Port no. 5150
	ReceiverAddr.sin_port = htons(Port);
	// From all interface (0.0.0.0)
	ReceiverAddr.sin_addr.s_addr = htonl(0);
	// Associate the address information with the socket using bind.
	// At this point you can receive datagrams on your bound socket.
	if (bind(ReceivingSocket, (SOCKADDR *) & ReceiverAddr, sizeof (ReceiverAddr)) == SOCKET_ERROR)
	{
		printf("Server: bind() failed! Error: %ld.\n", WSAGetLastError());
		// Close the socket
		closesocket(ReceivingSocket);
		// Do the clean up
		WSACleanup();
		// and exit with error
		return -1;
	} else
		printf("Server: bind() is OK!\n");

	// Some info on the receiver side...
	getsockname(ReceivingSocket, (SOCKADDR *) & ReceiverAddr, (int *) sizeof (ReceiverAddr));

	printf("Server: Receiving IP(s) used: %s\n", inet_ntoa(ReceiverAddr.sin_addr));
	printf("Server: Receiving port used: %d\n", htons(ReceiverAddr.sin_port));
	printf("Server: I\'m ready to receive a datagram...\n");

	printf("%%SUITE_STARTING%% handlertest\n");
	printf("%%SUITE_STARTED%%\n");

	csma_init(&contr, &Sender, &id);
	InitHandler(250, 8);

	HANDLE thread1 = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
	if (thread1)
	{
		// Optionally do stuff, such as wait on the thread.
	}

	HANDLE thread2 = CreateThread(NULL, 0, ThreadData, NULL, 0, NULL);
	if (thread2)
	{
		// Optionally do stuff, such as wait on the thread.
	}

	while (1)
	{
		// Call recvfrom() to get it then display the received data...
		ByteReceived = recvfrom(ReceivingSocket, ReceiveBuf, 1024,
				0, (SOCKADDR *) & SenderAddr, &SenderAddrSize);
		// Request ownership of the critical section.
		EnterCriticalSection(&CriticalSection);
		if (ByteReceived > 0)
		{
			printf("Server: Total Bytes received: %d\n", ByteReceived);
			printf("Bare:\n");
			for (i = 0; i < buff->len; i++)
			{
				printf("0x%02X, ", buff->p[i]);
			}
			//            printf("Server: The data is \"%s\"\n", ReceiveBuf);
		} else if (ByteReceived <= 0)
			printf("Server: Connection closed with error code: %ld\n",
				WSAGetLastError());
		else
			printf("Server: recvfrom() failed with error code: %d\n",
				WSAGetLastError());
		// Some info on the sender side
		getpeername(ReceivingSocket, (SOCKADDR *) & SenderAddr, &SenderAddrSize);
		printf("Server: Sending IP used: %s\n", inet_ntoa(SenderAddr.sin_addr));
		printf("Server: Sending port used: %d\n", htons(SenderAddr.sin_port));

		for (i = 0; i < ByteReceived; i++)
		{
			printf("%02X ", ReceiveBuf[i]);
		}
		printf("\n");
		for (i = 0; i < ByteReceived; i++)
		{
			printf("%c", ReceiveBuf[i]);
		}
		messg1 = MessageHandlerIntIP(
				ReceiveBuf,
				ByteReceived,
				0, 0
				);
		printf("\nAnswer\n");
		for (i = 0; i < messg1->len; i++)
		{
			printf("%02X ", messg1->p[i]);
		}
		printf("\n");
		for (i = 0; i < messg1->len; i++)
		{
			printf("%c", messg1->p[i]);
		}
		printf("\n=================================================\n");
		//        buff = MessageHandler(
		//                (const uint8_t *)ReceiveBuf, 
		//                ByteReceived, 
		//                inet_ntoa(SenderAddr.sin_addr), 
		//                htons(SenderAddr.sin_port)
		//        );
		printf("Server: Total Bytes answered: %d\n", messg1->len);
		//        printf("Bare:\n"); 
		//        for(i = 0;i < buff->len;i++)
		//        {
		//            printf("0x%02X, ",buff->p[i]);
		//        }
		//        printf("\r\n\r");
		if (sendto(
				ReceivingSocket,
				messg1->p,
				messg1->len,
				0,
				(struct sockaddr *) &SenderAddr,
				SenderAddrSize
				) < 0)
		{
			perror("sendto failed");
			return 0;
		}
		// Release ownership of the critical section.
		LeaveCriticalSection(&CriticalSection);
	}

	printf("%%SUITE_FINISHED%% time=0\n");
	// Release resources used by the critical section object.
	DeleteCriticalSection(&CriticalSection);
	return (EXIT_SUCCESS);
}


















