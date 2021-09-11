#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ѧ���ڵ�
typedef struct _STU
{
	char arrStuNum[10];
	char arrStuName[10];
	int  iStuScore;
	struct _STU* pNext;
} STUNODE;

//���������ͷ��β
STUNODE* g_pHead = NULL;  //O 
STUNODE* g_pEnd = NULL; 

//���һ��ѧ������Ϣ
void AddStuMSG(char *arrStuNum, char arrStuName[10], int iStuScore);

//����ͷ���һ���ڵ�
void AddStuMSGToLinkHead(char *arrStuNum, char arrStuName[10], int iStuScore);

//�������
void FreeLinkData();

//��ӡ����
void ShowStuData();

//��ʾָ��
void ShowOrder();

//�����ƶ�ѧ��
STUNODE* FindStuByNum(char* arrStuNum); //����

//ָ��λ�ò���ڵ�
void InsertNode(STUNODE* pTemp, char *arrStuNum, char arrStuName[10], int iStuScore);

//ɾ��ָ��ѧ��
void DeleteStuNode(STUNODE* pNode);

//������Ϣ���ļ�
void SaveStuToFile();

//��ȡ�ļ���ѧ����Ϣ
void ReadStuFromFile();


int main(void)
{
	int nOrder = -1; //nOrder iOrder  s db arr p
	                 //��ʼ��
	char arrStuNum[10] = {'\0'};
	char arrStuName[10] = {'\0'};
	int  iStuScore = -1;

	int nFlag = 1;

	STUNODE* pTemp = NULL;
	ShowOrder();

	//��ȡ�ļ���ѧ����Ϣ
	ReadStuFromFile();

	while(nFlag)
	{
		printf ("������ָ��(10���鿴ָ��):");
		scanf("%d", &nOrder);

		switch (nOrder)
		{
		case 1://β���
			//���һ��ѧ������Ϣ
			printf ("����ѧ��:");
			scanf ("%s", arrStuNum);
			printf ("��������:");
			scanf ("%s", arrStuName);
			printf ("�������:");
			scanf ("%d", &iStuScore);

			AddStuMSG(arrStuNum, arrStuName, iStuScore);
			break;
		case 11: //ͷ���
			//���һ��ѧ������Ϣ
			printf ("����ѧ��:");
			scanf ("%s", arrStuNum);
			printf ("��������:");
			scanf ("%s", arrStuName);
			printf ("�������:");
			scanf ("%d", &iStuScore);

			AddStuMSGToLinkHead(arrStuNum, arrStuName, iStuScore);
			break;
		case 111:  //�м����
			
			printf ("����ָ��ѧ��:");
			scanf ("%s", arrStuNum);
			pTemp = FindStuByNum(arrStuNum);
			if (NULL != pTemp)  //200501013  1254
			{
				//TODO������
				printf ("����ѧ��:");
				scanf ("%s", arrStuNum);
				printf ("��������:");
				scanf ("%s", arrStuName);
				printf ("�������:");
				scanf ("%d", &iStuScore);

				InsertNode(pTemp, arrStuNum, arrStuName, iStuScore);
			}
			break;
		case 2: //��ӡָ��ѧ������Ϣ
			//����һ��ѧ��
			printf ("����ָ��ѧ��:");
			scanf ("%s", arrStuNum);
			//����
			pTemp = FindStuByNum(arrStuNum);

			//��ӡ
			if (NULL != pTemp)  //200501013  1254
			{
				printf("ѧ��:%s, ����:%s, ����:%d\n", pTemp->arrStuNum, pTemp->arrStuName, pTemp->iStuScore);
			}

			break;
		case 3:  //�޸�ָ��ѧ������Ϣ
			//����һ��ѧ��
			printf ("����ָ��ѧ��:");
			scanf ("%s", arrStuNum);

			//����
			pTemp = FindStuByNum(arrStuNum);

			//��ӡ
			if (NULL != pTemp)  //200501013  1254
			{
				//�޸�ѧ��
				printf ("����ѧ��:");
				scanf("%s", arrStuNum);
				strcpy(pTemp->arrStuNum, arrStuNum);

				//�޸����֡�
				printf ("��������:");
				scanf("%s", arrStuName);
				strcpy(pTemp->arrStuName, arrStuName);

				//�޸ķ���
				printf ("�������:");
				scanf("%d", &iStuScore);
				pTemp->iStuScore = iStuScore;
			}
			break;
		case 4:
			//����ѧ����Ϣ
			SaveStuToFile();
			break;
		case 6:
			//����һ��ѧ��
			printf ("����Ҫɾ����ѧ��ѧ��:");
			scanf ("%s", arrStuNum);

			//����
			pTemp = FindStuByNum(arrStuNum);

			//ɾ������ڵ�
			if (NULL != pTemp)  //200501013  1254
			{
				//����ɾ��ѧ���ĺ���
				DeleteStuNode(pTemp);
			}
			break;
		case 7:
			//,�ͷ�
			FreeLinkData();
			g_pHead = NULL;
			g_pEnd = NULL;
			//�ظ� ��ӽڵ�
			ReadStuFromFile();

			break;
		case 9:
			//��ʾ��������
			ShowStuData();
			break;
		case 10:
			//�鿴ָ��
			ShowOrder();
			break;
		case 0:
			//�˳�
			nFlag = 0;
			break;
		default:
			printf("�����ָ��ԣ�\n");
		}
	}
	
	//����
	SaveStuToFile();
	//�ͷ�����
	FreeLinkData();
	system("pause");
	return 0;
}

//���һ��ѧ������Ϣ
void AddStuMSG(char *arrStuNum, char arrStuName[10], int  iStuScore) //��������
{
	//�߼�
	//����һ���ڵ�
	STUNODE* pTemp = malloc(sizeof (STUNODE));

	//��һ������������ĺϷ���
	if (NULL == arrStuNum || NULL == arrStuName || iStuScore < 0)
	{
		printf ("ѧ����Ϣ�������!\n");
		return ;
	}
	//�ڵ��Ա����ʼֵ
	strcpy(pTemp->arrStuNum, arrStuNum);
	strcpy(pTemp->arrStuName, arrStuName);
	pTemp->iStuScore = iStuScore;
	pTemp->pNext = NULL;

	//����������
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		g_pHead = pTemp;
		//g_pEnd = pTemp;
	}
	else
	{
		g_pEnd->pNext = pTemp;  //����
		//g_pEnd = pTemp;         //����ƶ�
	}
	g_pEnd = pTemp;
}


//�������
void FreeLinkData()
{
	STUNODE* pTemp = g_pHead;
	while (g_pHead != NULL)
	{
		//��¼�ڵ�
		pTemp = g_pHead;

		//����ƶ���һ��
		g_pHead = g_pHead->pNext;

		//ɾ���ڵ�
		free(pTemp);
	}
}

//��ӡ����
void ShowStuData()
{
	STUNODE* pTemp = g_pHead;
	while (pTemp != NULL)
	{
		printf ("ѧ��:%s, ����:%s, ����:%d\n", pTemp->arrStuNum, pTemp->arrStuName, pTemp->iStuScore);
		//������һ��
		pTemp = pTemp->pNext;
	}
}

//��ʾָ��
void ShowOrder()
{
	printf("*******************ѧ����Ϣ����ϵͳ*********************\n");
	printf("*******************��ϵͳ����ָ������*******************\n");
	printf("***             1�� ����һ��ѧ����Ϣ(β���)         ***\n");
	printf("***            11�� ����һ��ѧ����Ϣ(ͷ���)         ***\n");
	printf("***           111�� ����һ��ѧ����Ϣ(��ָ��λ�����) ***\n");
	printf("***             2�� ����ָ��ѧ������Ϣ������/ѧ�ţ�  ***\n");
	printf("***             3�� �޸�ָ��ѧ������Ϣ               ***\n");
	printf("***             4�� ����ҵ������Ϣ���ļ���           ***\n");
	printf("***             5�� ��ȡ�ļ��е�ҵ����Ϣ             ***\n");
	printf("***             6�� ɾ��ָ��ѧ������Ϣ               ***\n");
	printf("***             7�� �ָ�ɾ����ѧ������Ϣ             ***\n");
	printf("***             9�� ��ʾ����ѧ������Ϣ               ***\n");
	printf("***             0�� �˳�ϵͳ                         ***\n");
	printf("********************************************************\n");
}

//����ͷ���һ���ڵ�
void AddStuMSGToLinkHead(char *arrStuNum, char arrStuName[10], int iStuScore)
{
	//����һ���ڵ�
	STUNODE* pTemp = malloc(sizeof(STUNODE));

	//�������ĺϷ���
	if (NULL == arrStuName || NULL == arrStuName || iStuScore < 0)
	{
		printf ("ѧ����Ϣ�������!\n");
		return ;
	}
	
	//c��Ա��ֵ
	//�ڵ��Ա����ʼֵ
	strcpy(pTemp->arrStuNum, arrStuNum);
	strcpy(pTemp->arrStuName, arrStuName);
	pTemp->iStuScore = iStuScore;
	pTemp->pNext = NULL;

	if (NULL == g_pHead || NULL == g_pEnd)
	{
		//����Ϊ��
		//g_pHead = pTemp;
		g_pEnd = pTemp;
	}
	else
	{
		//�½ڵ����һ�� ָ��ͷ
		pTemp->pNext = g_pHead;
		//ͷ��ǰŲ��һ��
		//g_pHead = pTemp;
	}
	g_pHead = pTemp;
}

//�����ƶ�ѧ��
STUNODE* FindStuByNum(char* arrStuNum)  //200501013  1254
{
	STUNODE* pTemp = g_pHead;
	//�������ĺϷ���
	if (NULL == arrStuNum)
	{
		printf ("ѧ���������\n");
		return NULL;
	}
	
	//�ж������Ƿ��ǿ�
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		printf ("����ΪNULL��\n");
		return NULL;
	}

	//��������	
	while(pTemp != NULL)
	{
		if (0 == strcmp(pTemp->arrStuNum, arrStuNum))
		{
			return pTemp;
		}
		pTemp = pTemp->pNext;
	}

	printf ("���޴˽ڵ㣡\n");
	return NULL;
}

//ָ��λ�ò���ڵ�
void InsertNode(STUNODE* pTemp, char *arrStuNum, char arrStuName[10], int iStuScore)
{
	//�����ڵ�
	STUNODE* pNewTemp = malloc(sizeof(STUNODE));
	
	//��Ա��ֵ
	strcpy(pNewTemp->arrStuNum, arrStuNum);
	strcpy(pNewTemp->arrStuName, arrStuName);
	pNewTemp->iStuScore = iStuScore;
	pNewTemp->pNext = NULL;    ///

	//����
	if (pTemp == g_pEnd)  //��β�ڵ�
	{
		g_pEnd->pNext = pNewTemp;
		g_pEnd = pNewTemp;
	}
	else
	{
		//
		pNewTemp->pNext = pTemp->pNext;
		pTemp->pNext = pNewTemp;
	}
}

//ɾ��ָ��ѧ��
void DeleteStuNode(STUNODE* pNode)
{
	//ֻ��һ���ڵ�
	if (g_pHead == g_pEnd)
	{
		free(g_pHead);
		g_pHead = NULL;
		g_pEnd = NULL;
	}
	//ֻ�������ڵ�
	else if (g_pHead->pNext == g_pEnd)
	{
		if (g_pHead == pNode)
		{
			free(g_pHead);
			g_pHead = g_pEnd;
		}
		else
		{
			free(g_pEnd);
			g_pEnd = g_pHead;
			g_pHead->pNext = NULL;
		}
	}
	else // >=3
	{
		STUNODE* pTemp = g_pHead;
		//�ж�ͷ
		if(g_pHead == pNode)
		{
			//��סͷ
			pTemp = g_pHead;
			g_pHead = g_pHead->pNext;
			free(pTemp);
			pTemp = NULL;
			return ;  //����
		}

		while(pTemp)
		{
			if(pTemp->pNext == pNode)
			{
				//ɾ��
				if (pNode == g_pEnd)
				{
					free(pNode);
					pNode = NULL;
					g_pEnd = pTemp;
					g_pEnd->pNext = NULL;
					return ;
				}
				else
				{
					//��סҪɾ���Ľڵ�
					STUNODE* p = pTemp->pNext;
					//����
					pTemp->pNext = pTemp->pNext->pNext;
					//�ͷŽڵ�
					free(p);
					p = NULL;
					return ;
				}
			}

			pTemp = pTemp->pNext;
		}
	}
}

//������Ϣ���ļ�
void SaveStuToFile()
{
	//�ж������Ƿ���NULL
	FILE* pFile = NULL;
	STUNODE* pTemp = g_pHead;
	char strBuf[30] = {0};
	char strScore[10] = {0};

	if (NULL == g_pHead)
	{
		printf("û��ѧ��\n");
		return ;
	}

	//���ļ�
	pFile = fopen("dat.dat", "wb+");
	if (NULL == pFile)
	{
		printf("�ļ���ʧ��\n");
		return ;
	}
	//�����ļ�ָ��
	while(pTemp)
	{
		//ѧ�Ÿ�ֵ��ȥ
		strcpy(strBuf, pTemp->arrStuNum);
		strcat(strBuf, ".");
		//����
		strcat(strBuf, pTemp->arrStuName);
		strcat(strBuf, ".");
		//����
		itoa(pTemp->iStuScore, strScore, 10);
		strcat(strBuf, strScore);

		fwrite(strBuf, 1, strlen(strBuf), pFile); //
		fwrite("\r\n", 1, strlen("\r\n"), pFile);

		pTemp = pTemp->pNext;
	}

	//�ر��ļ�
	fclose(pFile);
}

//��ȡ�ļ���ѧ����Ϣ
void ReadStuFromFile()
{
	FILE* pFile = fopen("dat.dat", "rb+"); //

	char strBuf[30] = {0};

	char strStuNum[10] = {0};
	char strStuName[10] = {0};
	char strStuScore[10] = {0};

	int nCount = 0;
	int j = 0;

	if (NULL == pFile)
	{
		printf("�ļ���ʧ��\n");
		return ;
	}


	//����ָ�룬��ȡ����
	while( NULL !=  fgets(strBuf, 30, pFile))  //EOF  feof   3����
	{
		int i =0;
		nCount = 0;
		j = 0;
		for (i = 0; strBuf[i] != '\r'; i++)
		{
			if(0 == nCount) //û��'.'
			{
				strStuNum[i] = strBuf[i];
				if ('.' == strBuf[i])
				{
					strStuNum[i] = '\0';
					nCount++;
				}
			}
			else if (1 == nCount) //��һ��'.'
			{
				strStuName[j] = strBuf[i];
				j++;	
				if ('.' == strBuf[i])
				{
					strStuName[j] = '\0';
					nCount++;
					j = 0;
				}		
			}
			else  //�ڶ���'.' 2 == nCount
			{
				strStuScore[j] = strBuf[i];
				j++;
			}
		}
		//���뵽����
		AddStuMSG(strStuNum, strStuName, atoi(strStuScore));
	}

	fclose(pFile);
}