#define _CRT_SECURE_NO_WARNINGS

#include "contact.h"

////静态初始化通讯录
// void InitContact(struct Contact* pc)
//{
//		 pc->sz = 0;
//		 memset(pc->data, 0, sizeof(pc->data));
//}

 int CheckCapacity(Contact* pc)
 {
	 if (pc->sz == pc->capacity)
	 {
		 //增容
		 struct PeoInfo* ptr = (struct PeoInfo*)realloc(pc->data, (pc->capacity + 2) * sizeof(struct PeoInfo));
		 if (ptr == NULL)
		 {
			 printf("扩容失败\n");
			 return 0;
		 }
		 else
		 {
			 //如果增容成功要把ptr赋值给pc->data
			 pc->data = ptr;
			 pc->capacity += 2;
			 printf("增容成功\n");
			 return 1;
		 }
	 }
	 return 1;
 }

 void LoadContact(Contact* pc)
 {
	 //打开文件
	 FILE* pfIn = fopen("contact.dat", "rb");
	 if (pfIn == NULL)
	 {
		 printf("LoadContact::%s\n", strerror(errno));
		 return;
	 }
	 //读取文件内容放进通讯录
	 PeoInfo tmp = { 0 };
	 while (fread(&tmp, sizeof(PeoInfo), 1, pfIn))//每次读取一个人信息，当读取不到时，返回0
	 {
		 //检测是否要增容
		 if (CheckCapacity(pc) == 0)
		 {
			 printf("通讯录初始化失败\n");
			 return;
		 }
		 //存储元素
		 pc->data[pc->sz] = tmp;
		 pc->sz++;
	 }
	 //关闭文件
	 fclose(pfIn);
	 pfIn = NULL;
 }

 //动态版本-初始化通讯录
 void InitContact( Contact* pc)
 {
	 pc->sz = 0;
	 pc->capacity = DEFAULT_SZ;//通讯录创建好的时候，默认能放DEFAULT_SZ个人的信息
	 pc->data=(struct PeoInfo*)malloc(DEFAULT_SZ * sizeof(struct PeoInfo));
	 if (pc->data == NULL)
	 {
		 printf("初始化通讯录失败\n");
		 exit(1);
	 }
	 //加载文件
	 LoadContact(pc);

 }
 ////静态的版本增加一个人的信息
 //void AddContact(struct Contact* pc)
 //{
	// if (pc->sz == NAME_MAX)
	// {
	//	 printf("通讯录已满，无法添加\n");
	// }
	// else
	// {
	//	 printf("请输入名字:>\n");
	//	 scanf("%s", pc->data[pc->sz].name);
	//	 printf("请输入年龄:>\n");
	//	 scanf("%d", &(pc->data[pc->sz].age));
	//	 printf("请输入性别:>\n");
	//	 scanf("%s", pc->data[pc->sz].sex);
	//	 printf("请输入电话:>\n");
	//	 scanf("%s", pc->data[pc->sz].tele);
	//	 printf("请输入地址:>\n");
	//	 scanf("%s", pc->data[pc->sz].addr);
	//	 pc->sz++;
	//	 printf("添加成功\n");
	// }
 //}

  //动态增长的版本
 void AddContact(struct Contact* pc)
 {
	 if (CheckCapacity(pc)==0)
	 {
		 printf("空间不够使用，增加容量时失败\n");
		 return;
	 }
	 
		 printf("请输入名字:>\n");
		 scanf("%s", pc->data[pc->sz].name);
		 printf("请输入年龄:>\n");
		 scanf("%d", &(pc->data[pc->sz].age));
		 printf("请输入性别:>\n");
		 scanf("%s", pc->data[pc->sz].sex);
		 printf("请输入电话:>\n");
		 scanf("%s", pc->data[pc->sz].tele);
		 printf("请输入地址:>\n");
		 scanf("%s", pc->data[pc->sz].addr);
		 pc->sz++;
		 printf("添加成功\n");
	 
 }

 //打印通讯录中的信息
 void ShowContact(const struct Contact* pc)
 {
	 int i = 0;
	 if (pc->sz == 0)
	 {
		 printf("通讯录为空\n");
	 }
	 else
	 {
		 printf("%-15s\t %-5s\t %-5s\t %-12s\t %-20s\n", "名字", "年龄", "性别", "电话", "地址");
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

 //查找到一个人信息
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
	 //没找到
	 return -1;
 }
 //删除一个人信息
 void DelContact(struct Contact* pc)
 {
	 char name[NAME_MAX] = { 0 };
	 if (pc->sz == 0)
	 {
		 printf("通讯录为空，无法删除\n");
	 }
	 else
	 {
		 //1.找到要删除的人
		 printf("请输入要删除人的名字:>");
		 scanf("%s", name);
		 int pos = FindByName(pc, name);
		 {
			 if (pos == -1)
			 {
				 printf("要删除的人不存在\n");
			 }
			 else
			 {
				 //2.删除
				 int j = 0;
				 for (j = pos; j < pc ->sz - 1; j++)
				 {
					 pc->data[j] = pc->data[j + 1];
				 }
				 pc->sz--;
				 printf("删除成功\n");
			 }
		 }
	 }
 }

 //查找指定联系人
 void SearchContact(const struct Contact* pc)
 {
	 char name[NAME_MAX];
	 printf("请输入要查找人姓名:>");
	 scanf("%s", name);
	 int pos = FindByName(pc, name);
	 if (pos == -1)
	 {
		 printf("要查找的人不存在\n");
	 }
	 else
	 {
		 printf("%-15s\t %-5s\t %-5s\t %-12s\t %-20s\n", "名字", "年龄", "性别", "电话", "地址");
	 	
		 printf("%-15s\t %-5d\t %-5s\t %-12s\t %-20s\n",
			 pc->data[pos].name,
			 pc->data[pos].age,
			 pc->data[pos].sex,
			 pc->data[pos].tele,
			 pc->data[pos].addr);
	 }
	 
 }
 //修改指定联系人
 void ModifyContact(struct Contact* pc)
 {
	 char name[NAME_MAX];
	 printf("请输入要修改人姓名:>");
	 scanf("%s", name);
	 int pos = FindByName(pc, name);
	 if (pos == -1)
	 {
		 printf("要修改的人不存在\n");
	 }
	 else
	 {
		 printf("请输入名字:>\n");
		 scanf("%s", pc->data[pos].name);
		 printf("请输入年龄:>\n");
		 scanf("%d", &(pc->data[pos].age));
		 printf("请输入性别:>\n");
		 scanf("%s", pc->data[pos].sex);
		 printf("请输入电话:>\n");
		 scanf("%s", pc->data[pos].tele);
		 printf("请输入地址:>\n");
		 scanf("%s", pc->data[pos].addr);
		 pc->sz++;
		 printf("修改成功\n");
	 }
 }

 int cmp_stu_by_name(const void* e1, const void* e2)
 {
	 //比较名字就是比较字符串
	 //字符串比较不能直接用><=来比较，应该用strcmp函数
	 return strcmp(((const char * )e1), ((const char* )e2));
 }
 //以首字母排序通讯录
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
	 //打开文件
	 FILE* pfOut = fopen("contact.dat", "wb");
	 if (pfOut == NULL)
	 {
		 printf("SaveContact::%s\n", strerror(errno));
	 }
	 //写数据
	 int i = 0;
	 for (i = 0; i < pc->sz; i++)
	 {
		 fwrite(pc->data + i, sizeof(PeoInfo), 1, pfOut);
	 }
	 //关闭文件
	 fclose(pfOut);
	 pfOut = NULL;
 }