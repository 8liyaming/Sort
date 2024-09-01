#define  _CRT_SECURE_NO_WARNINGS 1
#include "Sort.h"
#include "Stack.h"


void PrintArray(int* a, int n)  //打印
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void Swap(int* p1, int* p2)  //交换
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

//插入排序
void InsertSort(int* a, int n)
{
	assert(a);

	for (int i = 0; i < n - 1; ++i)  //注意i只能取到n-2,否则end+1超过数组下标越界
	{
		//单趟排序([0,end]有序，把end+1往[0,end]区间插入保持它有序)
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (tmp < a[end])
			{
				a[end + 1] = a[end];
				--end;
			}
			else
			{
				break;
			}
			a[end + 1] = tmp;
		}
	}
}

//希尔排序
void ShellSort(int* a, int n)
{
	//1. gap > 1相当于预排序，让数组接近有序
	//2. gap = 1相当于直接插入排序，保证数组有序
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;  //+1的目的是保证最后一次gap为1，/3是经验值
		for (int i = 0; i < n - gap; ++i)  //多组并排
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (tmp < a[end])
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;
		}

		PrintArray(a, n);
	}
}

//选择排序
void SelectSort(int* a, int n)
{
	assert(a);

	int begin = 0;
	int end = n - 1;
	while (begin < end)
	{
		//在[begin,end]之间找出最小数和最大数的下标
		int mini;
		int maxi;
		mini = maxi = begin;
		for (int i = begin + 1; i <= end; ++i)
		{
			if (a[i] > a[maxi])
			{
				maxi = i;
			}

			if (a[i] < a[mini])
			{
				mini = i;
			}
		}

		Swap(&a[begin], &a[mini]);

		//如果maxi和begin位置重叠，则maxi的位置需要修正，否则执行下面交换后就复原了
		if (begin == maxi)
		{
			maxi = mini;
		}

		Swap(&a[end], &a[maxi]);

		++begin;
		--end;
	}
}

//堆排序
void AdjustDown(int* a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;  //假设法：假设左右孩子中大的那个是左孩子

	while (child < n)  //孩子节点位置超出总的最大位置时即不用再交换
	{
		//找出左右孩子中小的那一个
		//注意：上面保证了child不会越界，但child+1可能会越界(没有右孩子，大的就是左孩子)，故在下面补上了“child+1 < n”的条件
		if (child + 1 < n && a[child + 1] > a[child])  //child+1即表示右孩子
		{
			++child;  //如果右孩子的值比左孩子的值大，则假设错误，更正为右孩子是左右孩子中大的那个
		}

		//如果孩子节点比父亲节点大，则交换两节点
		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			//循环迭代
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void HeapSort(int* a, int n)
{
	//排升序，建大堆
	//调整为左右子树都是大堆的形式
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)  //从倒数的第一个非叶子节点开始调整(即最后一个叶子节点:n-1的父亲)
	{
		AdjustDown(a, n, i);
	}

	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		--end;
	}
}

//冒泡排序
void BubbleSort(int* a, int n)
{
	int end = n;
	while (end > 0)
	{
		int exchange = 0;
		for (int i = 1; i < end; ++i)
		{
			if (a[i - 1] > a[i])
			{
				Swap(&a[i - 1], &a[i]);
				exchange = 1;
			}
		}

		//如果一趟冒泡的过程中没有发生交换，则已经有序，不需要再冒泡
		if (exchange == 0)
		{
			break;
		}

		--end;
	}
}

//快速排序递归实现
int GetMidIndex(int* a, int begin, int end)  //三数取中
{
	int mid = (begin + end) / 2;
	if (a[begin] < a[mid])
	{
		if (a[mid] < a[end])
		{
			return mid;
		}
		else if(a[begin] > a[end])
		{
			return begin;
		}
		else
		{
			return end;
		}
	}
	else
	{
		if (a[mid] > a[end])
		{
			return mid;
		}
		else if (a[begin] < a[end])
		{
			return begin;
		}
		else
		{
			return end;
		}

	}
}

//左右指针法
int PartSort1(int* a, int begin, int end)
{
	int midIndex = GetMidIndex(a, begin, end);
	//把三个数中最中间的数与最后一个数交换一下，保证了选的key不是最大的或者最小的，杜绝了最坏情况发生
	Swap(&a[midIndex], &a[end]);

	int keyindex = end;
	while (begin < end)
	{
		//begin找大
		while (begin < end && a[begin] <= a[keyindex])
		{
			++begin;
		}
		//end找小
		while (begin < end && a[end] >= a[keyindex])
		{
			--end;
		}

		Swap(&a[begin], &a[end]); 
	}

	Swap(&a[begin], &a[keyindex]);  //相遇后停止的位置值交换

	return begin;  //返回中间相遇的位置，取end也可以
}

//挖坑法
int PartSort2(int* a, int begin, int end)
{
	int midIndex = GetMidIndex(a, begin, end);
	//把三个数中最中间的数与最后一个数交换一下，保证了选的key不是最大的或者最小的，杜绝了最坏情况发生
	Swap(&a[midIndex], &a[end]);

	int key = a[end];  //假设开始挖最后一个元素为坑
	while (begin < end)
	{
		while (begin < end && a[begin] <= key)  //从左边开始找比key大的值
		{
			++begin;
		}

		//左边找到比key大的填到右边的坑，begin位置就形成了新的坑
		a[end] = a[begin];

		while (begin < end && a[end] >= key) ////从右边开始找比key小的值
		{
			--end;
		}

		//右边找到比key小的填到左边的坑，end位置就形成了新的坑
		a[begin] = a[end];
	}

	a[begin] = key;  //相遇的时候为最后一个坑，填入key

	return begin;  //返回中间相遇的位置，取end也可以
}

//前后指针法
int PartSort3(int* a, int begin, int end)
{
	int midIndex = GetMidIndex(a, begin, end);
	//把三个数中最中间的数与最后一个数交换一下，保证了选的key不是最大的或者最小的，杜绝了最坏情况发生
	Swap(&a[midIndex], &a[end]);

	int prev = begin - 1;
	int cur = begin;
	int keyindex = end;

	while (cur < end)
	{
		if (a[cur] < a[keyindex] && ++prev != cur)  //因为++prev = cur时交不交换都一样，这里就不交换了
			//如果等于也交换一下，就不用写后面条件，并把下面改成Swap(&a[++prev], &a[cur])即可
		{
			Swap(&a[prev], &a[cur]);
		}

		++cur;
	}

	Swap(&a[++prev], &a[keyindex]);  //走完了处理最后的key

	return prev;
}

void QuickSort(int* a, int left, int right)
{
	assert(a);
	if (left >= right)
	{
		return;
	}

	//如果排完一些次数后，prev两边的数个数不多了还有必要继续不停的划分比较吗？可以采用之前的插入排序
	if ((right - left + 1) > 10)
	{
		int div = PartSort3(a, left, right);

		/*PrintArray(a+left, right-left+1);
		printf("[%d,%d] %d [%d,%d]\n", left, div - 1, div, div + 1, right);*/

		//[left,div-1] div [div+1, right]
		QuickSort(a, left, div - 1);
		QuickSort(a, div + 1, right);
	}
	else
	{
		//小于等于10个以内的区间，不在递归排序，直接插入排序
		InsertSort(a + left, right - left + 1);
	}
}

//快速排序非递归实现(栈模拟实现)  
void QuickSortNonR(int* a, int left, int right)
{
	ST st;
	StackInit(&st);

	StackPush(&st, right);
	StackPush(&st, left);

	while (!StackEmpty(&st))
	{
		int begin = StackTop(&st);
		StackPop(&st);
		int end = StackTop(&st);
		StackPop(&st);

		//[begin, end]
		int div = PartSort3(a, begin, end);

		//[begin, div-1]  div  [div+1, end]  不用递归了，用栈
		if (div + 1 < end)
		{
			StackPush(&st, end);
			StackPush(&st, div+1);
		}

		if (begin < div - 1)
		{
			StackPush(&st, div - 1);
			StackPush(&st, begin);
		}

	}

	StackDestroy(&st);
}

//归并排序递归实现
void MergeArr(int* a, int begin1, int end1, int begin2, int end2, int* tmp)
{
	int left = begin1;
	int right = end2;
	int index = begin1;

	while (begin1 <= end1 && begin2 <= end2) //两个有一个结束了就停止
	{
		if (a[begin1] < a[begin2])
		{
			tmp[index++] = a[begin1++];  //谁小谁往tmp里拿，先使用后++
		}
		else
		{
			tmp[index++] = a[begin2++];
		}
	}

	//两个总有一个还没结束，下面两个循环只会进入一个
	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}

	//把归并好的在tmp中的数据拷贝回到原数组
	for (int i = left; i <= right; ++i)
	{
		a[i] = tmp[i];
	}
}
void _MergeSort(int* a, int left, int right, int* tmp)
{
	if (left >= right)
	{
		return;
	}

	int mid = (left + right) / 2;

	//[left, mid] [mid + 1, right]若有序则可以合并，现在它们没有序，子问题解决
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid+1, right, tmp);

	//归并[left, mid] [mid + 1, right]有序
	MergeArr(a, left, mid, mid + 1, right, tmp);
}

void MergeSort(int* a, int n)
{
	assert(a);
	int* tmp = malloc(sizeof(int) * n);

	_MergeSort(a, 0, n - 1, tmp);

	free(tmp);
}

//归并排序非递归实现
void MergeSortNonR(int* a, int n)
{
	assert(a);
	int* tmp = malloc(sizeof(int) * n);
	int gap = 1;
	while (gap < n)
	{
		for (int i = 0; i < n; i += 2 * gap)
		{
			//[i, i+gap-1] [i+gap, i+2*gap-1]
			int begin1 = i;
			int end1 = i + gap - 1;
			int begin2 = i + gap;
			int end2 = i + 2 * gap - 1;

			//1. 合并时只有第一组，第二组不存在，就不需要合并
			if (begin2 >= n)
			{
				break;
			}
			//2. 合并时第二组只有部分数据，需要修正end2边界
			if (end2 >= n)
			{
				end2 = n - 1;
			}

			MergeArr(a, begin1, end1, begin2, end2, tmp);
		}
		PrintArray(a, n);
		gap *= 2;
	}
	
	free(tmp);
}

//******  假设文件中有10亿个数据，需要排序，怎么办？(内存中最多只能放1000W个数据)  ******//
//%%%%%%%%%%%    解决办法：10亿个数据读出来，切分成100份    %%%%%%%%%%%%%%//
void _MergeFile(const char* file1, const char*  file2, const char*  mfile)
{
	FILE* fout1 = fopen(file1, "r");
	if (fout1 == NULL)
	{
		printf("打开文件失败\n");
		exit(-1);
	}

	FILE* fout2 = fopen(file2, "r");
	if (fout2 == NULL)
	{
		printf("打开文件失败\n");
		exit(-1);
	}

	FILE* fin = fopen(mfile, "w");
	if (fin == NULL)
	{
		printf("打开文件失败\n");
		exit(-1);
	}

	int num1, num2;
	int ret1 = fscanf(fout1, "%d\n", &num1);
	int ret2 = fscanf(fout2, "%d\n", &num2);
	while (ret1 != EOF && ret2 != EOF)  //若不用ret变量直接在条件里写不对(少读写数)，因为两个读取同时往后走了，应该是比完小的往后走
	{
		if (num1 < num2)
		{
			fprintf(fin, "%d\n", num1);
			ret1 = fscanf(fout1, "%d\n", &num1);  //小的往后走，往后再读一位(读写文件，指针自动往后移)
		}
		else
		{
			fprintf(fin, "%d\n", num2);
			ret2 = fscanf(fout2, "%d\n", &num2);  //小的往后走，往后再读一位(读写文件，指针自动往后移)
		}
	}

	//两个总有一个还没结束，下面两个循环只会进入一个
	while (ret1 != EOF)
	{
		fprintf(fin, "%d\n", num1);
		ret1 = fscanf(fout1, "%d\n", &num1);
	}

	while (ret2 != EOF)
	{
		fprintf(fin, "%d\n", num2);
		ret2 = fscanf(fout1, "%d\n", &num2);
	}

	fclose(fout1);
	fclose(fout2);
	fclose(fin);
}

void MergeSortFile(const char* file)
{
	FILE* fout = fopen(file, "r");
	if (fout == NULL)
	{
		printf("打开文件失败\n");
		exit(-1);
	}

	//分割成一段一段数据，内存排序后写到小文件
	int n = 10;  //切的份数，这里以切10份为例
	int a[10];  //开辟一块空间，这里假设文件中有100个数，分10份，每份10个
	int i = 0;
	int num = 0;
	char subfile[20];
	int filei = 1;  //小文件名编号
	//从打开的文件中读数据
	while (fscanf(fout, "%d\n", &num) != EOF) //\n是因为文件中数据是一个数据换一行，如果是一个数据空一格这里把\n改成空格
	{
		if (i < n - 1)
		{
			a[i++] = num;
		}
		else  //读好了9+1个数据，开始排序
		{
			a[i] = num;
			QuickSort(a, 0, n - 1);
			//排好序后写到文件中(最后在文件中归并，不建议排完序后就归并(内存中归并))
			sprintf(subfile, "sub\\%d", filei++);  //%d为对应filei的编号
			FILE* fin = fopen(subfile, "w");
			if (fin == NULL)
			{
				printf("打开文件失败\n");
				exit(-1);
			}
			for (int i = 0; i < n; i++)
			{
				fprintf(fin, "%d\n", a[i]);
			}
			fclose(fin);

			i = 0;
		}
	}

	//利用互相归并到文件，实现整体有序
	char mfile[100] = "12";
	char file1[100] = "sub\\1";
	char file2[100] = "sub\\2";
	for (int i = 2; i <= n; ++i)
	{
		//读取file1和file2，进行归并出mfile
		_MergeFile(file1, file2, mfile);

		strcpy(file1, mfile);
		sprintf(file2, "sub\\%d", i+1);
		sprintf(mfile, "%s%d", mfile, i + 1);
	}

	fclose(fout);
}

//计数排序(非比较排序)
void CountSort(int* a, int n)
{
	assert(a);
	int min = a[0];
	int max = a[0];
	for (int i = 1; i < n; ++i)
	{
		if (a[i] > max)
		{
			max = a[i];
		}
		if (a[i] < min)
		{
			min = a[i];
		}
	}
		int range = max - min + 1;
		int* countArr = (int*)malloc(sizeof(int) * range);
		memset(countArr, 0, sizeof(int) * range);  //初始化

		//统计次数
		for (int i = 0; i < n; ++i)
		{
			countArr[a[i]- min]++;  //是几就在几映射的位置上++
		}

		//排序
		int index = 0;
		for (int j = 0; j < range; ++j)
		{
			while (countArr[j]--)
			{
				a[index++] = j + min;  //counArr中j对应位置是几，a中就按顺序填入几个j + min
			}
		}

		free(countArr);
} 