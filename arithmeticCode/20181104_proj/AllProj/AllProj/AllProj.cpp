// AllProj.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//0901-1.����һ�������Ķ��������ж��ٸ�1
	printf("0901-1.����һ�������Ķ��������ж��ٸ�1\n");
	printf("count_one(8) : %d��\n", count_one(8));
	printf("count_one_2(8) : %d��\n\n", count_one_2(8));

	//0901-2.���һ��������ʮ���Ƶ�������ת��Ϊ36�����ַ���
	// ��0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ��
	//  1 = "0001"; 10 = "000A"; 20 = "000K"; 35 = "000Z"; 36 = "0010";
	printf("0901-2.���һ��������ʮ���Ƶ�������ת��Ϊ36�����ַ���\n");
	char buf[4] = {0};
	char *buf2;
	buf2 = dto36(20734, buf, 4);
	printf("20734��36����Ϊ��%s\n\n", buf2);

	//0901-3.�ж�һ��ƽ̨�ǵ�λ���Ȼ��Ǹ�λ����
	printf("0901-3.�ж�һ��ƽ̨�ǵ�λ���Ȼ��Ǹ�λ����\n");
	if (get_endian())
	{
		printf("С��\n\n");
	}
	else
	{
		printf("���\n\n");
	}

	//0901-4.�ı�һ�������Ĵ洢��ʽ��0x12345678->0x87654321��
	printf("0901-4.�ı�һ�������Ĵ洢��ʽ\n");
	int num = 0x12345678;//0x12345678-->0x78563412(0x87654321?)
	printf("Before reverse bytes order: 0x%x\n", num);
	reverse_int(&num);
	printf("After reverse bytes order: 0x%x\n\n", num);

	//0901-5.��һ���ַ������յ������� "hello world" -> "world hello"
	printf("0901-5.��һ���ַ������յ�������\"hello world\" -> \"world hello\"\n");
	RevWord("Hello world");
	printf("\n\n");
	
	//0901-6.��һ���ַ�������N���ַ����磬����3���ַ�"hello world" "lo worldhel"
	printf("0901-6.��һ���ַ�������N���ַ����磬����3���ַ�\"hello world\" \"lo worldhel\"\n");
	reverse_Nch("hello world");
	printf("%s\n\n", tmp);

	//0901-7.ͨ�����ʵ��һ��ֻ��һ��ָ�����˫������
	printf("0901-7.ͨ�����ʵ��һ��ֻ��һ��ָ�����˫������");
	Linker();
	printf("\n");

	//0908-1.�����Ӵ�
	printf("0908-1.�����Ӵ�\n");
	printf("%s\n", _strstr("hello world", "o"));
	printf("%s\n", _strstr("hello world", "xyz"));
	printf("%s\n\n", _strstr("hello world", NULL));

	//0915-1.��һ��IPv4��ַ�ַ�����32λ��������ת�� 255.255.255.255 <-> 0xFFFFFFFF
	printf("0915-1.��һ��IPv4��ַ�ַ�����32λ��������ת�� 255.255.255.255 <-> 0xFFFFFFFF\n");
	char ip1[16];
	char ip2[16];
	ip2str(0x12345678, ip1, 16);
	printf("ip:%s\n", ip1);
	iptostr(0x12345678, ip2, 16);
	printf("ip:%s\n", ip2);
	ip2str(0xffffffff, ip1, 16);
	printf("ip:%s\n\n", ip1);
	
	//0916-1.ʵ��void *memmove(void *pDst, const void *pSrc, size_t len) �����ص�
	printf("0916-1.ʵ��void *memmove(void *pDst, const void *pSrc, size_t len) �����ص�\n");
	char pDir[12] = { 0 };
	_memmove(pDir, "hello world", sizeof("hello world"));
	printf("%s\n\n", pDir);

	//0916-2.ʵ��void itoa(int i, char *buf) / int atoi(char *str)
	printf("0916-2.ʵ��void itoa(int i, char *buf) / int atoi(char *str)\n");
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


	//1006-1.����ж�һ�����������ѭ��
	printf("1006-1.����ж�һ�����������ѭ��\n");
	node *nodelist;
	nodelist = creatList();
	node* resnode = FindLoop(nodelist);
	if (resnode == NULL)
	{
		printf("��ѭ��\n\n");
	}
	else
	{
		printf("��ѭ����ѭ����ڵ�ַΪ��0x%x\n\n", resnode);
	}

	//1006-2.�ҳ������ѭ�������е���m���
	printf("1006-2.�ҳ������ѭ�������е���m���\n");
	node2 *nodelist1;
	nodelist1 = creatList2();
	node2 *resnode1 = FindLoopNumber(nodelist1, 3);
	if (resnode1 == NULL)
	{
		printf("num ���� �ڵ���, num ��������Χ��\n");
	}
	else
	{
		printf("��%d�����ĵ�ַΪ��0x%x\n", 3, resnode);
	}

	//1013-1.�ҳ�40000���ڵ�������ɸ����
	printf("1013-1.�ҳ�40000���ڵ�������ɸ����\n");
	printf("40000����һ��%d������\n\n", sift_prime());

	//1013-2.һ�������ֵ��ַ�����������б�׼��IP�����硰11022345��
	// 110.2.234.5 1.102.234.5 1.102.23.45 110.2.23.45
	printf("1013-2.һ�������ֵ��ַ�����������б�׼��IP\n");
	enumerate_ips("11022345");
	printf("\n");

	//1014-1.��һ���ַ��������е�*��ǰ he*llo wor*l*d  ->  ***hello world
	printf("1014-1.��һ���ַ��������е�*��ǰ he*llo wor*l*d  ->  ***hello world\n");
	char SS[] = { "he*llo wor*l*d" };
	move_stars_to_front(SS);
	printf("%s\n\n", SS);

	//1014-2.��һ�������������ҳ��ظ����������������ֵ�ķ�Χ��С��65536
	printf("1014-2.��һ�������������ҳ��ظ����������������ֵ�ķ�Χ��С��65536\n");
	FindRepNum();
	printf("\n");


	//1021-1.//1.����һ������2�ַ�����
			 //2.��������
			 //3.��һ��������ɾ��һ����㣨Ч�ʸߣ�
	printf("1021-1.�������\n");
	//�ǵݹ�����
	printf("****�ǵݹ�����****\n");
	node3 *nodeList = (node3*)malloc(LEN);
	nodeList->next = NULL;
	creatList(nodeList);
	showResult(nodeList);
	nodeList = ListOprReverse(nodeList);
	showResult(nodeList);
	free(nodeList);
	nodeList = NULL;

	//�ݹ�����
	printf("****�ݹ�����****\n");
	node3 *nodeList2 = (node3*)malloc(LEN);
	nodeList2->next = NULL;
	creatList(nodeList2);
	showResult(nodeList2);
	nodeList2 = ListOprReverse2(nodeList2);
	showResult(nodeList2);
	free(nodeList2);
	nodeList2 = NULL;

	//����
	printf("****����****\n");
	node3 *nodeList3 = (node3*)malloc(LEN);
	nodeList3->next = NULL;
	creatList(nodeList3);
	showResult(nodeList3);
	nodeList3 = ListOprSort(nodeList3);
	showResult(nodeList3);
	free(nodeList3);
	nodeList3 = NULL;

	//ɾ��
	printf("****ɾ��****\n");
	node3 *nodeList4 = (node3*)malloc(LEN);
	nodeList4->next = NULL;
	creatList(nodeList4);
	showResult(nodeList4);
	nodeList4 = ListOprDelNode(nodeList4, 5);
	showResult(nodeList4);
	free(nodeList4);
	nodeList4 = NULL;

	//ɾ��β���
	printf("****ɾ��β���****\n");
	node3 *nodeList5 = (node3*)malloc(LEN);
	nodeList5->next = NULL;
	creatList(nodeList5);
	showResult(nodeList5);
	nodeList5 = ListOprDelNode(nodeList5, 1);
	showResult(nodeList5);
	free(nodeList5);
	nodeList5 = NULL;
	printf("\n");

	//1028-1.��һ���ض��ַ�����ɾ��һ���ض��ַ�
	//void delChar(char *str, char del)
	//void delChars(char *str, char dels[], size_t len)
	//Hello world o -> Hell wrld
	//Hello world ol -> He wrd
	printf("1028-1.��һ���ض��ַ�����ɾ��һ���ض��ַ�\n");
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