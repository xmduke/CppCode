// AllProj.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "proj_0901.h"
#include "proj_0908.h"
#include "proj_0915.h"
#include "proj_0916.h"
#include "proj_1006.h"
#include "proj_1006-2.h"
#include "proj_1013.h"
#include "proj_1014.h"
#include "proj_1021.h"
#include "proj_1028.h"




int _tmain(int argc, _TCHAR* argv[])
{
	//0901-1.计算一个整数的二进制中有多少个1
	printf("0901-1.计算一个整数的二进制中有多少个1\n");
	printf("count_one(8) : %d个\n", count_one(8));
	printf("count_one_2(8) : %d个\n\n", count_one_2(8));

	//0901-2.设计一个函数把十进制的正整数转换为36进制字符串
	// “0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ”
	//  1 = "0001"; 10 = "000A"; 20 = "000K"; 35 = "000Z"; 36 = "0010";
	printf("0901-2.设计一个函数把十进制的正整数转换为36进制字符串\n");
	char buf[4] = {0};
	char *buf2;
	buf2 = dto36(20734, buf, 4);
	printf("20734的36进制为：%s\n\n", buf2);

	//0901-3.判断一个平台是低位优先还是高位优先
	printf("0901-3.判断一个平台是低位优先还是高位优先\n");
	if (get_endian())
	{
		printf("小端\n\n");
	}
	else
	{
		printf("大端\n\n");
	}

	//0901-4.改变一个整数的存储方式（0x12345678->0x87654321）
	printf("0901-4.改变一个整数的存储方式\n");
	int num = 0x12345678;//0x12345678-->0x78563412(0x87654321?)
	printf("Before reverse bytes order: 0x%x\n", num);
	reverse_int(&num);
	printf("After reverse bytes order: 0x%x\n\n", num);

	//0901-5.将一个字符串按照单词逆置 "hello world" -> "world hello"
	printf("0901-5.将一个字符串按照单词逆置\"hello world\" -> \"world hello\"\n");
	RevWord("Hello world");
	printf("\n\n");
	
	//0901-6.将一个字符串左旋N个字符。如，左旋3个字符"hello world" "lo worldhel"
	printf("0901-6.将一个字符串左旋N个字符。如，左旋3个字符\"hello world\" \"lo worldhel\"\n");
	reverse_Nch("hello world");
	printf("%s\n\n", tmp);

	//0901-7.通过异或实现一个只带一个指针域的双向链表
	printf("0901-7.通过异或实现一个只带一个指针域的双向链表");
	Linker();
	printf("\n");

	//0908-1.查找子串
	printf("0908-1.查找子串\n");
	printf("%s\n", _strstr("hello world", "o"));
	printf("%s\n", _strstr("hello world", "xyz"));
	printf("%s\n\n", _strstr("hello world", NULL));

	//0915-1.把一个IPv4地址字符串与32位整数进行转换 255.255.255.255 <-> 0xFFFFFFFF
	printf("0915-1.把一个IPv4地址字符串与32位整数进行转换 255.255.255.255 <-> 0xFFFFFFFF\n");
	char ip1[16];
	char ip2[16];
	ip2str(0x12345678, ip1, 16);
	printf("ip:%s\n", ip1);
	iptostr(0x12345678, ip2, 16);
	printf("ip:%s\n", ip2);
	ip2str(0xffffffff, ip1, 16);
	printf("ip:%s\n\n", ip1);
	
	//0916-1.实现void *memmove(void *pDst, const void *pSrc, size_t len) 考虑重叠
	printf("0916-1.实现void *memmove(void *pDst, const void *pSrc, size_t len) 考虑重叠\n");
	char pDir[12] = { 0 };
	_memmove(pDir, "hello world", sizeof("hello world"));
	printf("%s\n\n", pDir);

	//0916-2.实现void itoa(int i, char *buf) / int atoi(char *str)
	printf("0916-2.实现void itoa(int i, char *buf) / int atoi(char *str)\n");
	char my_itoa_buf[12] = { 0 };
	int res;
	res = my_itoa(0x80000000, my_itoa_buf);
	printf("%s\n", my_itoa_buf);
	char my_itoa_buf2[12] = { 0 };
	int res1;
	res1 = my_itoa(0x71234567, my_itoa_buf2);
	printf("%s\n", my_itoa_buf2);
	char my_itoa_buf3[12] = { 0 };
	int res2;
	res2 = my_itoa(0x81234567, my_itoa_buf3);
	printf("%s\n", my_itoa_buf3);

	printf("%d\n", my_atoi("1234567890"));
	printf("%d\n", my_atoi("2147483647"));
	printf("%d\n", my_atoi("-2128394905"));
	printf("%d\n\n", my_atoi("-2147483648"));


	//1006-1.如何判断一个单链表存在循环
	printf("1006-1.如何判断一个单链表存在循环\n");
	node *nodelist;
	nodelist = creatList();
	node* resnode = FindLoop(nodelist);
	if (resnode == NULL)
	{
		printf("无循环\n\n");
	}
	else
	{
		printf("有循环，循环入口地址为：0x%x\n\n", resnode);
	}

	//1006-2.找出单向非循环链表中倒数m结点
	printf("1006-2.找出单向非循环链表中倒数m结点\n");
	node2 *nodelist1;
	nodelist1 = creatList2();
	node2 *resnode1 = FindLoopNumber(nodelist1, 3);
	if (resnode1 == NULL)
	{
		printf("num 大于 节点数, num 不在链表范围内\n");
	}
	else
	{
		printf("第%d个结点的地址为：0x%x\n", 3, resnode);
	}

	//1013-1.找出40000以内的素数（筛法）
	printf("1013-1.找出40000以内的素数（筛法）\n");
	printf("40000以内一共%d个素数\n\n", sift_prime());

	//1013-2.一个纯数字的字符串，输出所有标准的IP，例如“11022345”
	// 110.2.234.5 1.102.234.5 1.102.23.45 110.2.23.45
	printf("1013-2.一个纯数字的字符串，输出所有标准的IP\n");
	enumerate_ips("11022345");
	printf("\n");

	//1014-1.将一个字符串中所有的*提前 he*llo wor*l*d  ->  ***hello world
	printf("1014-1.将一个字符串中所有的*提前 he*llo wor*l*d  ->  ***hello world\n");
	char SS[] = { "he*llo wor*l*d" };
	move_stars_to_front(SS);
	printf("%s\n\n", SS);

	//1014-2.从一个正整数组中找出重复的数，假设数组的值的范围都小于65536
	printf("1014-2.从一个正整数组中找出重复的数，假设数组的值的范围都小于65536\n");
	FindRepNum();
	printf("\n");


	//1021-1.//1.逆置一个链表（2种方法）
			 //2.链表排序
			 //3.从一个链表中删除一个结点（效率高）
	printf("1021-1.链表操作\n");
	//非递归逆置
	printf("****非递归逆置****\n");
	node3 *nodeList = (node3*)malloc(LEN);
	nodeList->next = NULL;
	creatList(nodeList);
	showResult(nodeList);
	nodeList = ListOprReverse(nodeList);
	showResult(nodeList);
	free(nodeList);
	nodeList = NULL;

	//递归逆置
	printf("****递归逆置****\n");
	node3 *nodeList2 = (node3*)malloc(LEN);
	nodeList2->next = NULL;
	creatList(nodeList2);
	showResult(nodeList2);
	nodeList2 = ListOprReverse2(nodeList2);
	showResult(nodeList2);
	free(nodeList2);
	nodeList2 = NULL;

	//排序
	printf("****排序****\n");
	node3 *nodeList3 = (node3*)malloc(LEN);
	nodeList3->next = NULL;
	creatList(nodeList3);
	showResult(nodeList3);
	nodeList3 = ListOprSort(nodeList3);
	showResult(nodeList3);
	free(nodeList3);
	nodeList3 = NULL;

	//删除
	printf("****删除****\n");
	node3 *nodeList4 = (node3*)malloc(LEN);
	nodeList4->next = NULL;
	creatList(nodeList4);
	showResult(nodeList4);
	nodeList4 = ListOprDelNode(nodeList4, 5);
	showResult(nodeList4);
	free(nodeList4);
	nodeList4 = NULL;

	//删除尾结点
	printf("****删除尾结点****\n");
	node3 *nodeList5 = (node3*)malloc(LEN);
	nodeList5->next = NULL;
	creatList(nodeList5);
	showResult(nodeList5);
	nodeList5 = ListOprDelNode(nodeList5, 1);
	showResult(nodeList5);
	free(nodeList5);
	nodeList5 = NULL;
	printf("\n");

	//1028-1.从一个特定字符串中删除一个特定字符
	//void delChar(char *str, char del)
	//void delChars(char *str, char dels[], size_t len)
	//Hello world o -> Hell wrld
	//Hello world ol -> He wrd
	printf("1028-1.从一个特定字符串中删除一个特定字符\n");
	char *str = "Hello world";
	char pwrite[12] = { 0 };
	str = delChar(str, pwrite, 'o');
	printf("%s\n", str);
	char *str2 = "Hello world";
	char dels[] = { "ol" };
	char pwrite2[12] = { 0 };
	str2 = delChars(str2, pwrite2, dels, 2);
	printf("%s\n", str2);

	return 0;
}