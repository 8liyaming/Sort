#define  _CRT_SECURE_NO_WARNINGS 1
#include "Sort.h"
#include "Stack.h"


void PrintArray(int* a, int n)  //��ӡ
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void Swap(int* p1, int* p2)  //����
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

//��������
void InsertSort(int* a, int n)
{
	assert(a);

	for (int i = 0; i < n - 1; ++i)  //ע��iֻ��ȡ��n-2,����end+1���������±�Խ��
	{
		//��������([0,end]���򣬰�end+1��[0,end]������뱣��������)
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

//ϣ������
void ShellSort(int* a, int n)
{
	//1. gap > 1�൱��Ԥ����������ӽ�����
	//2. gap = 1�൱��ֱ�Ӳ������򣬱�֤��������
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;  //+1��Ŀ���Ǳ�֤���һ��gapΪ1��/3�Ǿ���ֵ
		for (int i = 0; i < n - gap; ++i)  //���鲢��
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

//ѡ������
void SelectSort(int* a, int n)
{
	assert(a);

	int begin = 0;
	int end = n - 1;
	while (begin < end)
	{
		//��[begin,end]֮���ҳ���С������������±�
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

		//���maxi��beginλ���ص�����maxi��λ����Ҫ����������ִ�����潻����͸�ԭ��
		if (begin == maxi)
		{
			maxi = mini;
		}

		Swap(&a[end], &a[maxi]);

		++begin;
		--end;
	}
}

//������
void AdjustDown(int* a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;  //���跨���������Һ����д���Ǹ�������

	while (child < n)  //���ӽڵ�λ�ó����ܵ����λ��ʱ�������ٽ���
	{
		//�ҳ����Һ�����С����һ��
		//ע�⣺���汣֤��child����Խ�磬��child+1���ܻ�Խ��(û���Һ��ӣ���ľ�������)���������油���ˡ�child+1 < n��������
		if (child + 1 < n && a[child + 1] > a[child])  //child+1����ʾ�Һ���
		{
			++child;  //����Һ��ӵ�ֵ�����ӵ�ֵ���������󣬸���Ϊ�Һ��������Һ����д���Ǹ�
		}

		//������ӽڵ�ȸ��׽ڵ���򽻻����ڵ�
		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			//ѭ������
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
	//�����򣬽����
	//����Ϊ�����������Ǵ�ѵ���ʽ
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)  //�ӵ����ĵ�һ����Ҷ�ӽڵ㿪ʼ����(�����һ��Ҷ�ӽڵ�:n-1�ĸ���)
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

//ð������
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

		//���һ��ð�ݵĹ�����û�з������������Ѿ����򣬲���Ҫ��ð��
		if (exchange == 0)
		{
			break;
		}

		--end;
	}
}

//��������ݹ�ʵ��
int GetMidIndex(int* a, int begin, int end)  //����ȡ��
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

//����ָ�뷨
int PartSort1(int* a, int begin, int end)
{
	int midIndex = GetMidIndex(a, begin, end);
	//�������������м���������һ��������һ�£���֤��ѡ��key�������Ļ�����С�ģ��ž�����������
	Swap(&a[midIndex], &a[end]);

	int keyindex = end;
	while (begin < end)
	{
		//begin�Ҵ�
		while (begin < end && a[begin] <= a[keyindex])
		{
			++begin;
		}
		//end��С
		while (begin < end && a[end] >= a[keyindex])
		{
			--end;
		}

		Swap(&a[begin], &a[end]); 
	}

	Swap(&a[begin], &a[keyindex]);  //������ֹͣ��λ��ֵ����

	return begin;  //�����м�������λ�ã�ȡendҲ����
}

//�ڿӷ�
int PartSort2(int* a, int begin, int end)
{
	int midIndex = GetMidIndex(a, begin, end);
	//�������������м���������һ��������һ�£���֤��ѡ��key�������Ļ�����С�ģ��ž�����������
	Swap(&a[midIndex], &a[end]);

	int key = a[end];  //���迪ʼ�����һ��Ԫ��Ϊ��
	while (begin < end)
	{
		while (begin < end && a[begin] <= key)  //����߿�ʼ�ұ�key���ֵ
		{
			++begin;
		}

		//����ҵ���key�����ұߵĿӣ�beginλ�þ��γ����µĿ�
		a[end] = a[begin];

		while (begin < end && a[end] >= key) ////���ұ߿�ʼ�ұ�keyС��ֵ
		{
			--end;
		}

		//�ұ��ҵ���keyС�����ߵĿӣ�endλ�þ��γ����µĿ�
		a[begin] = a[end];
	}

	a[begin] = key;  //������ʱ��Ϊ���һ���ӣ�����key

	return begin;  //�����м�������λ�ã�ȡendҲ����
}

//ǰ��ָ�뷨
int PartSort3(int* a, int begin, int end)
{
	int midIndex = GetMidIndex(a, begin, end);
	//�������������м���������һ��������һ�£���֤��ѡ��key�������Ļ�����С�ģ��ž�����������
	Swap(&a[midIndex], &a[end]);

	int prev = begin - 1;
	int cur = begin;
	int keyindex = end;

	while (cur < end)
	{
		if (a[cur] < a[keyindex] && ++prev != cur)  //��Ϊ++prev = curʱ����������һ��������Ͳ�������
			//�������Ҳ����һ�£��Ͳ���д������������������ĳ�Swap(&a[++prev], &a[cur])����
		{
			Swap(&a[prev], &a[cur]);
		}

		++cur;
	}

	Swap(&a[++prev], &a[keyindex]);  //�����˴�������key

	return prev;
}

void QuickSort(int* a, int left, int right)
{
	assert(a);
	if (left >= right)
	{
		return;
	}

	//�������һЩ������prev���ߵ������������˻��б�Ҫ������ͣ�Ļ��ֱȽ��𣿿��Բ���֮ǰ�Ĳ�������
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
		//С�ڵ���10�����ڵ����䣬���ڵݹ�����ֱ�Ӳ�������
		InsertSort(a + left, right - left + 1);
	}
}

//��������ǵݹ�ʵ��(ջģ��ʵ��)  
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

		//[begin, div-1]  div  [div+1, end]  ���õݹ��ˣ���ջ
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

//�鲢����ݹ�ʵ��
void MergeArr(int* a, int begin1, int end1, int begin2, int end2, int* tmp)
{
	int left = begin1;
	int right = end2;
	int index = begin1;

	while (begin1 <= end1 && begin2 <= end2) //������һ�������˾�ֹͣ
	{
		if (a[begin1] < a[begin2])
		{
			tmp[index++] = a[begin1++];  //˭С˭��tmp���ã���ʹ�ú�++
		}
		else
		{
			tmp[index++] = a[begin2++];
		}
	}

	//��������һ����û��������������ѭ��ֻ�����һ��
	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}

	//�ѹ鲢�õ���tmp�е����ݿ����ص�ԭ����
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

	//[left, mid] [mid + 1, right]����������Ժϲ�����������û������������
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid+1, right, tmp);

	//�鲢[left, mid] [mid + 1, right]����
	MergeArr(a, left, mid, mid + 1, right, tmp);
}

void MergeSort(int* a, int n)
{
	assert(a);
	int* tmp = malloc(sizeof(int) * n);

	_MergeSort(a, 0, n - 1, tmp);

	free(tmp);
}

//�鲢����ǵݹ�ʵ��
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

			//1. �ϲ�ʱֻ�е�һ�飬�ڶ��鲻���ڣ��Ͳ���Ҫ�ϲ�
			if (begin2 >= n)
			{
				break;
			}
			//2. �ϲ�ʱ�ڶ���ֻ�в������ݣ���Ҫ����end2�߽�
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

//******  �����ļ�����10�ڸ����ݣ���Ҫ������ô�죿(�ڴ������ֻ�ܷ�1000W������)  ******//
//%%%%%%%%%%%    ����취��10�ڸ����ݶ��������зֳ�100��    %%%%%%%%%%%%%%//
void _MergeFile(const char* file1, const char*  file2, const char*  mfile)
{
	FILE* fout1 = fopen(file1, "r");
	if (fout1 == NULL)
	{
		printf("���ļ�ʧ��\n");
		exit(-1);
	}

	FILE* fout2 = fopen(file2, "r");
	if (fout2 == NULL)
	{
		printf("���ļ�ʧ��\n");
		exit(-1);
	}

	FILE* fin = fopen(mfile, "w");
	if (fin == NULL)
	{
		printf("���ļ�ʧ��\n");
		exit(-1);
	}

	int num1, num2;
	int ret1 = fscanf(fout1, "%d\n", &num1);
	int ret2 = fscanf(fout2, "%d\n", &num2);
	while (ret1 != EOF && ret2 != EOF)  //������ret����ֱ����������д����(�ٶ�д��)����Ϊ������ȡͬʱ�������ˣ�Ӧ���Ǳ���С��������
	{
		if (num1 < num2)
		{
			fprintf(fin, "%d\n", num1);
			ret1 = fscanf(fout1, "%d\n", &num1);  //С�������ߣ������ٶ�һλ(��д�ļ���ָ���Զ�������)
		}
		else
		{
			fprintf(fin, "%d\n", num2);
			ret2 = fscanf(fout2, "%d\n", &num2);  //С�������ߣ������ٶ�һλ(��д�ļ���ָ���Զ�������)
		}
	}

	//��������һ����û��������������ѭ��ֻ�����һ��
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
		printf("���ļ�ʧ��\n");
		exit(-1);
	}

	//�ָ��һ��һ�����ݣ��ڴ������д��С�ļ�
	int n = 10;  //�еķ�������������10��Ϊ��
	int a[10];  //����һ��ռ䣬��������ļ�����100��������10�ݣ�ÿ��10��
	int i = 0;
	int num = 0;
	char subfile[20];
	int filei = 1;  //С�ļ������
	//�Ӵ򿪵��ļ��ж�����
	while (fscanf(fout, "%d\n", &num) != EOF) //\n����Ϊ�ļ���������һ�����ݻ�һ�У������һ�����ݿ�һ�������\n�ĳɿո�
	{
		if (i < n - 1)
		{
			a[i++] = num;
		}
		else  //������9+1�����ݣ���ʼ����
		{
			a[i] = num;
			QuickSort(a, 0, n - 1);
			//�ź����д���ļ���(������ļ��й鲢���������������͹鲢(�ڴ��й鲢))
			sprintf(subfile, "sub\\%d", filei++);  //%dΪ��Ӧfilei�ı��
			FILE* fin = fopen(subfile, "w");
			if (fin == NULL)
			{
				printf("���ļ�ʧ��\n");
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

	//���û���鲢���ļ���ʵ����������
	char mfile[100] = "12";
	char file1[100] = "sub\\1";
	char file2[100] = "sub\\2";
	for (int i = 2; i <= n; ++i)
	{
		//��ȡfile1��file2�����й鲢��mfile
		_MergeFile(file1, file2, mfile);

		strcpy(file1, mfile);
		sprintf(file2, "sub\\%d", i+1);
		sprintf(mfile, "%s%d", mfile, i + 1);
	}

	fclose(fout);
}

//��������(�ǱȽ�����)
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
		memset(countArr, 0, sizeof(int) * range);  //��ʼ��

		//ͳ�ƴ���
		for (int i = 0; i < n; ++i)
		{
			countArr[a[i]- min]++;  //�Ǽ����ڼ�ӳ���λ����++
		}

		//����
		int index = 0;
		for (int j = 0; j < range; ++j)
		{
			while (countArr[j]--)
			{
				a[index++] = j + min;  //counArr��j��Ӧλ���Ǽ���a�оͰ�˳�����뼸��j + min
			}
		}

		free(countArr);
} 