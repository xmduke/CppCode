// filedemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "mfun.h"
#include <errno.h>
int isLogin;

int _tmain(int argc, _TCHAR* argv[])
{
	char resbuf[20], ubuf[20], pbuf[20], upath[50];
	printf("------�ļ�ϵͳ��ʾ����------\n");
	while (!isLogin){
		printf("����˵��:\n");
		printf("1����½ ��ʽ: login [username] [password]\n");
		printf("2��ע�� ��ʽ: regist [username] [password]\n");
		printf("����������:");
		scanf("%s %s %s", resbuf, ubuf, pbuf);
		if (strcmp(resbuf, "login") == 0){
			int lres = login(ubuf, pbuf);
			if (lres == -1){
				printf("�û�'%s'������,��˶���Ϣ��ע��\n", ubuf);
				continue;
			}
			else if (lres == 0){
				printf("������'%s'��ƥ��,��˶�\n", ubuf);
				continue;
			}
			else{
				printf("��½�ɹ�\n");
				isLogin = 1;
				sprintf(upath, "/home/lhx/study/kefile/%s/", ubuf);
				lres = chdir(ubuf);
				if (lres != 0){
					printf("����Ŀ¼ʧ��\n");
					printf("Error:%s\n", strerror(errno));
				}
				else{
					printf("��ǰ����Ŀ¼:%s\n", upath);
				}
				system("clear");
			}
		}
		else if (strcmp(resbuf, "regist") == 0){
			int rres = regist(ubuf, pbuf);
			if (rres == -1){
				printf("ע��ʧ��,������\n");
			}
			else{
				printf("ע��ɹ����Ͽ��½ϵͳ��ʾ��\n");
				mkdir(ubuf, 0741);
			}
		}
		else{
			printf("������������޷�ʶ��,������\n");
		}
	}
	printf("---------�ļ�������ʾ----------\n");

	while (1){
		int filedesc;
		printf("--------------------------------------------------\n");
		printf("�����ļ�:create [filename] [mode](eg:666)\n");
		printf("�鿴�ļ�����:type [filename] -n\n");
		printf("ɾ���ļ�:delete [filename] -n\n");
		printf("����Ŀ¼:mkdir [dirname] -n\n");
		printf("ɾ��Ŀ¼:rmdir [dirname] -n\n");
		printf("�쿴��ǰĿ¼�µ��ļ�:dir [option](-l:detail,-nl) -n\n");
		printf("����Ŀ¼:cd [dirname] -n\n");
		printf("�������������:");
		scanf("%s %s %s", resbuf, ubuf, pbuf);
		if (strcmp(resbuf, "create") == 0)
		{
			int mode = atoi(pbuf);
			if (mode == 0){
				printf("�޷�ʶ����ļ�Ȩ��\n");
				continue;
			}
			filedesc = creat(ubuf, tentoe(mode));
			if (filedesc == -1){
				printf("����ʧ�ܣ����ļ��Ѵ���\n");
			}
			else{
				printf("�����ɹ�\n");
			}
			close(filedesc);
		}
		else if (strcmp(resbuf, "type") == 0){
			filedesc = open(ubuf, O_RDONLY);
			if (filedesc == -1){
				printf("���ļ�������!\n");
			}
			else{
				char buf[1025];
				int count;
				printf("'%s'�ļ�������:\n", ubuf);
				while (1){
					count = read(filedesc, buf, 1024);
					if (count == 0){
						break;
					}
					buf[count] = 0;
					printf("%s", buf);
				}
			}
		}
		else if (strcmp(resbuf, "delete") == 0){
			filedesc = unlink(ubuf);
			if (filedesc != 0){
				printf("ɾ��ʧ�ܣ��ļ����ܲ�����\n");
			}
			else{
				printf("ɾ���ļ�'%s'�ɹ�\n", ubuf);
			}
		}
		else if (strcmp(resbuf, "mkdir") == 0){
			filedesc = mkdir(ubuf, 0751);
			if (filedesc != 0){
				printf("����Ŀ¼ʧ�ܣ�Ŀ¼�����Ѿ�������\n");
			}
			else{
				printf("����Ŀ¼'%s'�ɹ�\n", ubuf);
			}
		}
		else if (strcmp(resbuf, "rmdir") == 0){
			filedesc = rmdir(ubuf);
			if (filedesc != 0){
				printf("ɾ��Ŀ¼ʧ�ܣ�Ŀ¼���ܲ����ڻ���Ŀ¼�ǿ�\n");
			}
			else{
				printf("ɾ��Ŀ¼'%s'�ɹ�\n", ubuf);
			}
		}
		else if (strcmp(resbuf, "cd") == 0){
			char dpath[50];
			sprintf(dpath, "%s%s", upath, ubuf);
			strcpy(upath, dpath);
			filedesc = chdir(dpath);
			if (filedesc != 0){
				printf("���Ĺ���Ŀ¼ʧ��!\n");
			}
			else{
				printf("��ǰ����Ŀ¼��%s\n", dpath);
			}
		}
		else if (strcmp(resbuf, "dir") == 0){

			if (strcmp(ubuf, "-nl") == 0){
				DIR* dir;
				struct dirent* drt;
				dir = opendir(upath);
				while (1){
					drt = readdir(dir);
					if (drt == NULL){
						break;
					}
					printf("%s\t", drt->d_name);
				}
				printf("\n");
				closedir(dir);
			}
			else if (strcmp(ubuf, "-l") == 0){
				listdtl(upath);
			}
			else{
				printf("����ʶ���ѡ��'%s'!\n", ubuf);
				continue;
			}
		}
		else{
			printf("δ��ʶ�������,��˶�!\n");
		}

	}
	return 0;
}

