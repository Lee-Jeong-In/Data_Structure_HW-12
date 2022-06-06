/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);

int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

int hashing(int *a, int **ht);

int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); 

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);         // 배열 초기화
			break;
		case 'q': case 'Q':
			freeArray(array);           // 메모리 해제
			break;
		case 's': case 'S':
			selectionSort(array);       // 선택 정렬
			break;
		case 'i': case 'I':
			insertionSort(array);       // 삽입 정렬
			break;
		case 'b': case 'B':
			bubbleSort(array);          // 버블 정렬
			break;
		case 'l': case 'L':
			shellSort(array);           // 쉘 정렬
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");   // 퀵정렬
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':             // 해쉬
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':             // 해쉬에서 찾기
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;       // 임시의 포인터 함수 생성

	if(*a == NULL)          // 배열의 메모리가 없으면
    {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  
	}
    else
		temp = *a;          // 있으면 temp에 저장

	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;      // 배열에 0~12까지 랜덤하게 넣는다.

	return 0;
}

int freeArray(int *a)           // 메모리 해제 및 종료
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)       // 선택정렬 함수 (배열을 한번씩 쭉 보고 제일 적은 값을 왼쪽에 넣는다.)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)            //선택정렬 수행 알고리즘
	{
		minindex = i;
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)       // 선택 정렬은 앞index부터 작은 값으로 채워 나간다.
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)                // 삽입 정렬
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)     // 삽입정렬은 왼쪽은 삽입 되어있다고 가정하고 시작한다.
	{
		t = a[i];
		j = i;
		while (a[j-1] > t && j > 0)         // 정렬이 되어있다고 생각되는 배열에 새로운 값이 들어갈 위치를 잡는 알고리즘이다.
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)              // 버블 정렬 (두 숫자증 큰값을 오른쪽에 정렬한다.)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)         // 정렬되는 범위(전체범위를 잡는다.)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)    // 실질적으로 정렬이 되는 부분
		{                                       // 버블 정렬은 맨 오른쪽부터 정렬된다.    
			if (a[j-1] > a[j])
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)           // 쉘정렬은 반절씩 줄여나가면서 정렬하다 마지막에는 삽입정렬로 마무리한다.
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)       // 나누는 부분을 반절씩 줄여나간다. ( 범위 잡기)
	{
		for (i = 0; i < h; i++)                     // 나눈 부분의 갯수만큼 정렬 수행   (범위 잡기)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)  // 한개의 부분에의 정렬을 수행한다. (실제 정렬 수행)
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)    // 퀵정렬은 중심이 되는 피봇과 정령 부분을 나눈 다는 것이다.
{
	int v, t;
	int i, j;

	if (n > 1)                  // 나보다 작은 값이 1개이 있을 때 까지 반복한다.
	{
		v = a[n-1];             // 피봇위치 잡기
		i = -1;
		j = n - 1;              // 범위 정하기

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;  
			t = a[i];           // 피봇보다 작은 값들을 왼쪽으로 보낸다.
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);            // 첫번째 정렬된 후 피봇의 위치가 확정되었으므로 피봇보다 작은쪽을 정렬하러 재귀함수 호출
		quickSort(a+i+1, n-i-1);    // 첫번째 정렬 후 왼쪽부분 정렬 완료 했으니 오른쪽 부분 정렬하러 자귀함수 호출
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)       // 관리를 유지하고 유지(해시함수 만들기) / 속도가 빠르다
{
	int *hashtable = NULL;

	if(*ht == NULL)         // 해시 테이블 만들기
    {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  
	} else 
    {
		hashtable = *ht;	
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)    // 해시 테이블 초기화
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);       // 함수를 사용해 해시코드를 만든다.
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)    // 해시 테이블에 값이 없으면 그대로 저장
		{
			hashtable[hashcode] = key;
		}
         else 	                            // 충돌이 발생했을 때 처리과정
        {

			index = hashcode;       

			while(hashtable[index] != -1)   // 비어있는 인덱스가 나올때까지 옆으로 이동(Chaining 방법을 사용)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)        // 해시 테이블에서 값 찾기
{
	int index = hashCode(key);      // 해시 코드를 받아서

	if(ht[index] == key)            // 원하는 값을 찾으면 그 값이 있는 인덱스 리턴
		return index;

	while(ht[++index] != key)       // 없으면 찾을 때 까지 이동
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}
