/*******************************Program Description****************************
purpose: 通过程序，对九种排序算法进行练习，输出每种排序的第一趟结果和最后一趟
         1、冒泡排序  2、选择排序  3、插入排序  4、希尔排序  5、堆排序
         6、归并排序  7、快速排序  8、拓扑排序  9、基数排序
author: Dong-Hong-Yan
created: 2013-5-11 10:02:30
verson: codeblocks 10.05 编译通过
******************************************************************************/

#include <iostream>
using namespace std;

int arr[10] = {3, 6, 8, 2, 4, 0, 9, 1, 5, 7};

// 冒泡排序
void BubbleSortArray(int arr[],int n)
{
    for(int i=1; i<n; i++)
    {
        for(int j=0; j<n-i; j++)
        {
            if(arr[j]>arr[j+1])//比较交换相邻元素
            {
                int temp;
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

// 选择排序
void SelectSortArray(int arr[], int n)
{
    int min, temp;
    for(int i=0; i<n-1; i++)          /*进行轮选择最小数的操作*/
    {
        min=i;          /*用来存放第轮最小数的下标*/
        for(int j=i+1; j<n; j++)
        {
            if(arr[j]<arr[min])
            {
                min=j;
            }
        }
        temp=arr[min];
        arr[min]=arr[i];        /*最小数a[k]与a[i]互换*/
        arr[i]=temp;
    }
}

// 插入排序
void InsertSortArray(int arr[], int n)
{
    for(int i=1; i<n; i++) //循环从第二个数组元素开始，因为arr[0]作为最初已排序部分
    {
        int temp = arr[i];//temp标记为未排序第一个元素
        int j=i-1;
        while (j>=0 && arr[j]>temp)/*将temp与已排序元素从小到大比较，寻找temp应插入的位置*/
        {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=temp;
    }
}

// 希尔排序
void ShellSortArray(int arr[], int n)
{
    int inc = 0;
    for (int i=2; n/i>0; i=i*2)
    {
        inc++;
    }
    for(; inc>0; inc--)//增量递减，以增量3，2，1为例
    {
        for(int L=0; L<(n-1)/inc; L++)//重复分成的每个子列表
        {
            for(int i=L+inc; i<n; i+=inc)//对每个子列表应用插入排序
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

// 堆排序


// 归并排序
void MergeSort(int arr[], int low, int high)
{
    int mid, i, j, k;
    if(low >= high)   return;     //每个子列表中剩下一个元素时停止
    else mid=(low+high)/2;   //将列表划分成相等的两个子列表,若有奇数个元素，则在左边子列表大于右侧子列表


    MergeSort(arr, low, mid);           //子列表进一步划分
    MergeSort(arr, mid+1, high);
    int *B = new int [high-low+1];       //新建一个数组，用于存放归并的元素

    for(i=low, j=mid+1,k=low; i<=mid && j<=high; k++) //两个子列表进行排序归并，直到两个子列表中的一个结束
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

    for(; j<=high; j++,k++)     //如果第二个子列表中仍然有元素，则追加到新列表
        B[k] = arr[j];
    for(; i<=mid; i++,k++)  //如果在第一个子列表中仍然有元素，则追加到新列表中
        B[k] = arr[i];
    for(int z=0; z<10; z++)     //将排序的数组B的 所有元素复制到原始数组arr中
        arr[z] = B[z];
}

// 快速排序

void swap(int &a, int &b)
{
    int t;
    t = a;
    a = b;
    b = t;
}
int Partition(int arr[], int low, int high)
{
    int pivot = arr[low];//采用子序列的第一个元素作为枢纽元素
    while (low < high)
    {
        //从后往前栽后半部分中寻找第一个小于枢纽元素的元素
        while (low<high && arr[high]>=pivot)
        {
            --high;
        }
        //将这个比枢纽元素小的元素交换到前半部分
        swap(arr[low], arr[high]);
        //从前往后在前半部分中寻找第一个大于枢纽元素的元素
        while (low<high && arr[low]<=pivot)
        {
            ++low;
        }
        swap(arr[low], arr[high]);//将这个枢纽元素大的元素交换到后半部分
    }
    return low; //返回枢纽元素所在的位置
}
void QuickSort(int arr[], int low, int high)    // 这里如果调用QuickSort(arr, 0, 9);，必须这么写
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
    cout << "************************排序算法*********************\n";
    cout << "*      1、冒泡排序    2、选择排序  3、插入排序      *\n";
    cout << "*      4、希尔排序    5、堆排序    6、归并排序      *\n";
    cout << "*      7、快速排序    8、拓扑排序    9、基数排序    *\n";
    cout << "*****************************************************\n";

    MergeSort(arr, 0, 10);
    for (int i=0; i<10; ++i)
    {
        cout << arr[i] << ' ';
    }
    return 0;

}
