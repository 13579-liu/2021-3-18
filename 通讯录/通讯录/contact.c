#define _CRT_SECURE_NO_WARNINGS

#include "contact.h"

////��̬��ʼ��ͨѶ¼
// void InitContact(struct Contact* pc)
//{
//		 pc->sz = 0;
//		 memset(pc->data, 0, sizeof(pc->data));
//}

 int CheckCapacity(Contact* pc)
 {
	 if (pc->sz == pc->capacity)
	 {
		 //����
		 struct PeoInfo* ptr = (struct PeoInfo*)realloc(pc->data, (pc->capacity + 2) * sizeof(struct PeoInfo));
		 if (ptr == NULL)
		 {
			 printf("����ʧ��\n");
			 return 0;
		 }
		 else
		 {
			 //������ݳɹ�Ҫ��ptr��ֵ��pc->data
			 pc->data = ptr;
			 pc->capacity += 2;
			 printf("���ݳɹ�\n");
			 return 1;
		 }
	 }
	 return 1;
 }

 void LoadContact(Contact* pc)
 {
	 //���ļ�
	 FILE* pfIn = fopen("contact.dat", "rb");
	 if (pfIn == NULL)
	 {
		 printf("LoadContact::%s\n", strerror(errno));
		 return;
	 }
	 //��ȡ�ļ����ݷŽ�ͨѶ¼
	 PeoInfo tmp = { 0 };
	 while (fread(&tmp, sizeof(PeoInfo), 1, pfIn))//ÿ�ζ�ȡһ������Ϣ������ȡ����ʱ������0
	 {
		 //����Ƿ�Ҫ����
		 if (CheckCapacity(pc) == 0)
		 {
			 printf("ͨѶ¼��ʼ��ʧ��\n");
			 return;
		 }
		 //�洢Ԫ��
		 pc->data[pc->sz] = tmp;
		 pc->sz++;
	 }
	 //�ر��ļ�
	 fclose(pfIn);
	 pfIn = NULL;
 }

 //��̬�汾-��ʼ��ͨѶ¼
 void InitContact( Contact* pc)
 {
	 pc->sz = 0;
	 pc->capacity = DEFAULT_SZ;//ͨѶ¼�����õ�ʱ��Ĭ���ܷ�DEFAULT_SZ���˵���Ϣ
	 pc->data=(struct PeoInfo*)malloc(DEFAULT_SZ * sizeof(struct PeoInfo));
	 if (pc->data == NULL)
	 {
		 printf("��ʼ��ͨѶ¼ʧ��\n");
		 exit(1);
	 }
	 //�����ļ�
	 LoadContact(pc);

 }
 ////��̬�İ汾����һ���˵���Ϣ
 //void AddContact(struct Contact* pc)
 //{
	// if (pc->sz == NAME_MAX)
	// {
	//	 printf("ͨѶ¼�������޷����\n");
	// }
	// else
	// {
	//	 printf("����������:>\n");
	//	 scanf("%s", pc->data[pc->sz].name);
	//	 printf("����������:>\n");
	//	 scanf("%d", &(pc->data[pc->sz].age));
	//	 printf("�������Ա�:>\n");
	//	 scanf("%s", pc->data[pc->sz].sex);
	//	 printf("������绰:>\n");
	//	 scanf("%s", pc->data[pc->sz].tele);
	//	 printf("�������ַ:>\n");
	//	 scanf("%s", pc->data[pc->sz].addr);
	//	 pc->sz++;
	//	 printf("��ӳɹ�\n");
	// }
 //}

  //��̬�����İ汾
 void AddContact(struct Contact* pc)
 {
	 if (CheckCapacity(pc)==0)
	 {
		 printf("�ռ䲻��ʹ�ã���������ʱʧ��\n");
		 return;
	 }
	 
		 printf("����������:>\n");
		 scanf("%s", pc->data[pc->sz].name);
		 printf("����������:>\n");
		 scanf("%d", &(pc->data[pc->sz].age));
		 printf("�������Ա�:>\n");
		 scanf("%s", pc->data[pc->sz].sex);
		 printf("������绰:>\n");
		 scanf("%s", pc->data[pc->sz].tele);
		 printf("�������ַ:>\n");
		 scanf("%s", pc->data[pc->sz].addr);
		 pc->sz++;
		 printf("��ӳɹ�\n");
	 
 }

 //��ӡͨѶ¼�е���Ϣ
 void ShowContact(const struct Contact* pc)
 {
	 int i = 0;
	 if (pc->sz == 0)
	 {
		 printf("ͨѶ¼Ϊ��\n");
	 }
	 else
	 {
		 printf("%-15s\t %-5s\t %-5s\t %-12s\t %-20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
	 }
	 for (i = 0; i < pc->sz; i++)
	 {
		 printf("%-15s\t %-5d\t %-5s\t %-12s\t %-20s\n", 
			 pc->data[i].name,
			 pc->data[i].age,
			 pc->data[i].sex,
			 pc->data[i].tele,
			 pc->data[i].addr);
	 }
 }

 //���ҵ�һ������Ϣ
 static int FindByName(const struct Contact* pc, char name[])
 {
	 int i = 0;
	 for (i = 0; i < pc->sz; i++)
	 {
		 if (strcmp(pc->data[i].name, name) == 0)
		 {
			 return i;
		 }
	 }
	 //û�ҵ�
	 return -1;
 }
 //ɾ��һ������Ϣ
 void DelContact(struct Contact* pc)
 {
	 char name[NAME_MAX] = { 0 };
	 if (pc->sz == 0)
	 {
		 printf("ͨѶ¼Ϊ�գ��޷�ɾ��\n");
	 }
	 else
	 {
		 //1.�ҵ�Ҫɾ������
		 printf("������Ҫɾ���˵�����:>");
		 scanf("%s", name);
		 int pos = FindByName(pc, name);
		 {
			 if (pos == -1)
			 {
				 printf("Ҫɾ�����˲�����\n");
			 }
			 else
			 {
				 //2.ɾ��
				 int j = 0;
				 for (j = pos; j < pc ->sz - 1; j++)
				 {
					 pc->data[j] = pc->data[j + 1];
				 }
				 pc->sz--;
				 printf("ɾ���ɹ�\n");
			 }
		 }
	 }
 }

 //����ָ����ϵ��
 void SearchContact(const struct Contact* pc)
 {
	 char name[NAME_MAX];
	 printf("������Ҫ����������:>");
	 scanf("%s", name);
	 int pos = FindByName(pc, name);
	 if (pos == -1)
	 {
		 printf("Ҫ���ҵ��˲�����\n");
	 }
	 else
	 {
		 printf("%-15s\t %-5s\t %-5s\t %-12s\t %-20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
	 	
		 printf("%-15s\t %-5d\t %-5s\t %-12s\t %-20s\n",
			 pc->data[pos].name,
			 pc->data[pos].age,
			 pc->data[pos].sex,
			 pc->data[pos].tele,
			 pc->data[pos].addr);
	 }
	 
 }
 //�޸�ָ����ϵ��
 void ModifyContact(struct Contact* pc)
 {
	 char name[NAME_MAX];
	 printf("������Ҫ�޸�������:>");
	 scanf("%s", name);
	 int pos = FindByName(pc, name);
	 if (pos == -1)
	 {
		 printf("Ҫ�޸ĵ��˲�����\n");
	 }
	 else
	 {
		 printf("����������:>\n");
		 scanf("%s", pc->data[pos].name);
		 printf("����������:>\n");
		 scanf("%d", &(pc->data[pos].age));
		 printf("�������Ա�:>\n");
		 scanf("%s", pc->data[pos].sex);
		 printf("������绰:>\n");
		 scanf("%s", pc->data[pos].tele);
		 printf("�������ַ:>\n");
		 scanf("%s", pc->data[pos].addr);
		 pc->sz++;
		 printf("�޸ĳɹ�\n");
	 }
 }

 int cmp_stu_by_name(const void* e1, const void* e2)
 {
	 //�Ƚ����־��ǱȽ��ַ���
	 //�ַ����Ƚϲ���ֱ����><=���Ƚϣ�Ӧ����strcmp����
	 return strcmp(((const char * )e1), ((const char* )e2));
 }
 //������ĸ����ͨѶ¼
 void SortContact(struct Contact* pc)
 {
	 qsort(pc->data, pc->sz, sizeof(struct PeoInfo), cmp_stu_by_name);
 }

 void DestroyContact(struct Contact* pc)
 {
	 free(pc->data);
	 pc->data = NULL;
	 pc->capacity = 0;
	 pc->sz = 0;
 }

 void SaveContact(Contact* pc)
 {
	 //���ļ�
	 FILE* pfOut = fopen("contact.dat", "wb");
	 if (pfOut == NULL)
	 {
		 printf("SaveContact::%s\n", strerror(errno));
	 }
	 //д����
	 int i = 0;
	 for (i = 0; i < pc->sz; i++)
	 {
		 fwrite(pc->data + i, sizeof(PeoInfo), 1, pfOut);
	 }
	 //�ر��ļ�
	 fclose(pfOut);
	 pfOut = NULL;
 }