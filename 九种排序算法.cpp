/*******************************Program Description****************************
purpose: ͨ�����򣬶Ծ��������㷨������ϰ�����ÿ������ĵ�һ�˽�������һ��
         1��ð������  2��ѡ������  3����������  4��ϣ������  5��������
         6���鲢����  7����������  8����������  9����������
author: Dong-Hong-Yan
created: 2013-5-11 10:02:30
verson: codeblocks 10.05 ����ͨ��
******************************************************************************/

#include <iostream>
using namespace std;

int arr[10] = {3, 6, 8, 2, 4, 0, 9, 1, 5, 7};

// ð������
void BubbleSortArray(int arr[],int n)
{
    for(int i=1; i<n; i++)
    {
        for(int j=0; j<n-i; j++)
        {
            if(arr[j]>arr[j+1])//�ȽϽ�������Ԫ��
            {
                int temp;
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

// ѡ������
void SelectSortArray(int arr[], int n)
{
    int min, temp;
    for(int i=0; i<n-1; i++)          /*������ѡ����С���Ĳ���*/
    {
        min=i;          /*������ŵ�����С�����±�*/
        for(int j=i+1; j<n; j++)
        {
            if(arr[j]<arr[min])
            {
                min=j;
            }
        }
        temp=arr[min];
        arr[min]=arr[i];        /*��С��a[k]��a[i]����*/
        arr[i]=temp;
    }
}

// ��������
void InsertSortArray(int arr[], int n)
{
    for(int i=1; i<n; i++) //ѭ���ӵڶ�������Ԫ�ؿ�ʼ����Ϊarr[0]��Ϊ��������򲿷�
    {
        int temp = arr[i];//temp���Ϊδ�����һ��Ԫ��
        int j=i-1;
        while (j>=0 && arr[j]>temp)/*��temp��������Ԫ�ش�С����Ƚϣ�Ѱ��tempӦ�����λ��*/
        {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=temp;
    }
}

// ϣ������
void ShellSortArray(int arr[], int n)
{
    int inc = 0;
    for (int i=2; n/i>0; i=i*2)
    {
        inc++;
    }
    for(; inc>0; inc--)//�����ݼ���������3��2��1Ϊ��
    {
        for(int L=0; L<(n-1)/inc; L++)//�ظ��ֳɵ�ÿ�����б�
        {
            for(int i=L+inc; i<n; i+=inc)//��ÿ�����б�Ӧ�ò�������
            {
                int temp=arr[i];
                int j=i-inc;
                while(j>=0 && arr[j]>temp)
                {
                    arr[j+inc] = arr[j];
                    j -= inc;
                }
                arr[j+inc] = temp;
            }
        }
    }
}

// ������


// �鲢����
void MergeSort(int arr[], int low, int high)
{
    int mid, i, j, k;
    if(low >= high)   return;     //ÿ�����б���ʣ��һ��Ԫ��ʱֹͣ
    else mid=(low+high)/2;   //���б��ֳ���ȵ��������б�,����������Ԫ�أ�����������б�����Ҳ����б�


    MergeSort(arr, low, mid);           //���б��һ������
    MergeSort(arr, mid+1, high);
    int *B = new int [high-low+1];       //�½�һ�����飬���ڴ�Ź鲢��Ԫ��

    for(i=low, j=mid+1,k=low; i<=mid && j<=high; k++) //�������б��������鲢��ֱ���������б��е�һ������
    {

        if (arr[i]<=arr[j])
        {
            B[k]=arr[i];
            i++;
        }
        else
        {
            B[k]=arr[j];
            j++;
        }
    }

    for(; j<=high; j++,k++)     //����ڶ������б�����Ȼ��Ԫ�أ���׷�ӵ����б�
        B[k] = arr[j];
    for(; i<=mid; i++,k++)  //����ڵ�һ�����б�����Ȼ��Ԫ�أ���׷�ӵ����б���
        B[k] = arr[i];
    for(int z=0; z<10; z++)     //�����������B�� ����Ԫ�ظ��Ƶ�ԭʼ����arr��
        arr[z] = B[z];
}

// ��������

void swap(int &a, int &b)
{
    int t;
    t = a;
    a = b;
    b = t;
}
int Partition(int arr[], int low, int high)
{
    int pivot = arr[low];//���������еĵ�һ��Ԫ����Ϊ��ŦԪ��
    while (low < high)
    {
        //�Ӻ���ǰ�Ժ�벿����Ѱ�ҵ�һ��С����ŦԪ�ص�Ԫ��
        while (low<high && arr[high]>=pivot)
        {
            --high;
        }
        //���������ŦԪ��С��Ԫ�ؽ�����ǰ�벿��
        swap(arr[low], arr[high]);
        //��ǰ������ǰ�벿����Ѱ�ҵ�һ��������ŦԪ�ص�Ԫ��
        while (low<high && arr[low]<=pivot)
        {
            ++low;
        }
        swap(arr[low], arr[high]);//�������ŦԪ�ش��Ԫ�ؽ�������벿��
    }
    return low; //������ŦԪ�����ڵ�λ��
}
void QuickSort(int arr[], int low, int high)    // �����������QuickSort(arr, 0, 9);��������ôд
{
    if (low<high)
    {
        int n=Partition (arr ,low ,high);
        QuickSort (arr, low ,n);
        QuickSort (arr, n+1, high);
    }
}

int main()
{
    cout << "************************�����㷨*********************\n";
    cout << "*      1��ð������    2��ѡ������  3����������      *\n";
    cout << "*      4��ϣ������    5��������    6���鲢����      *\n";
    cout << "*      7����������    8����������    9����������    *\n";
    cout << "*****************************************************\n";

    MergeSort(arr, 0, 10);
    for (int i=0; i<10; ++i)
    {
        cout << arr[i] << ' ';
    }
    return 0;

}
