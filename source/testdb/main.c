#include <stdio.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <string.h>
#include "utf8_gbk_mem.h"

typedef struct Teacher
{
    int TeacherID;
    char Name[10];
    int Gender;
    char OfficeAddr[100];
    char HomeAddr[100];
    int PhoneNumber;
    double BasicSalary;
    double Adds;
    double AddsLife;
    double TelephoneFee;
    double WaterElectricityFee;
    double HouseFee;
    double GainTax;
    double HealthFee;
    double PublicFee;
    double SalaryBeforeFee;
    double TotalFee;
    double SalaryAfterFee;
} teacher;

sqlite3 *dbaccess;

void outputTeacher(const teacher *t)
{
    printf("��ʦ����\n\n");
    printf("-----������Ϣ-----\n");
    printf("��ʦ��ţ�%d\n��ʦ������%s\n",t->TeacherID,t->Name);
    if(t->Gender)
        printf("��ʦ�Ա�Ů\n");
    else
        printf("��ʦ�Ա���\n");
    printf("��λ���ƣ�%s\n��ͥסַ��%s\n��ϵ�绰��%d\n\n",t->OfficeAddr,t->HomeAddr,t->PhoneNumber);
    printf("-----���������벹��-----\n");
    printf("�������ʣ�%.5lf\n������%.5lf\n�������%.5lf\n\n",t->BasicSalary,t->Adds,t->AddsLife);
    printf("-----�ۿ���Ϣ-----\n");
    printf("�绰�ѣ�%.5lf\nˮ��ѣ�%.5lf\n���⣺%.5lf\n����˰��%.5lf\n�����ѣ�%.5lf\n������%.5lf\n\n"
            ,t->TelephoneFee,t->WaterElectricityFee,t->HouseFee,t->GainTax,t->HealthFee,t->PublicFee);
    printf("-----�ϼ�-----\n");
    printf("Ӧ�����ʣ�%.5lf\n�ϼƿۿ%.5lf\nʵ�����ʣ�%.5lf\n",t->SalaryBeforeFee,t->TotalFee,t->SalaryAfterFee);
}

int callback(void *ret,int nCount,char **cValue,char **cName)
{
    teacher *retdata=(teacher*)ret;

    retdata->TeacherID=atoi(cValue[0]);
    utf82gbk_(cValue[1],retdata->Name);
    retdata->Gender=atoi(cValue[2]);
    utf82gbk_(cValue[3],retdata->OfficeAddr);
    utf82gbk_(cValue[4],retdata->HomeAddr);
    retdata->PhoneNumber=atoi(cValue[5]);
    retdata->BasicSalary=atof(cValue[6]);
    retdata->Adds=atof(cValue[7]);
    retdata->AddsLife=atof(cValue[8]);
    retdata->TelephoneFee=atof(cValue[9]);
    retdata->WaterElectricityFee=atof(cValue[10]);
    retdata->HouseFee=atof(cValue[11]);
    retdata->GainTax=atof(cValue[12]);
    retdata->HealthFee=atof(cValue[13]);
    retdata->PublicFee=atof(cValue[14]);
    retdata->SalaryBeforeFee=atof(cValue[15]);
    retdata->TotalFee=atof(cValue[16]);
    retdata->SalaryAfterFee=atof(cValue[17]);

    outputTeacher(retdata);
    return SQLITE_OK;
}

int main() {
    sqlite3_open("data.db",&dbaccess);
    teacher t;
    char *sql="SELECT * FROM teacherdata WHERE TeacherID=10000;",*err; // ����sql���ʹ�����Ϣ����
    int retc=sqlite3_exec(dbaccess,sql,callback,&t,&err); // ��ѯ���ݿ�
    if(retc != SQLITE_OK) // �����ѯ���ִ��ʧ��
        printf("�������ݿ�ʧ�ܡ������룺%d��������Ϣ��%s\n",retc,err); // �׳�����
     return 0;
}