#include <stdio.h>
//standard useful functions
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int power(int base, int exp)
{
    for (int i = 1; i <= exp; i++)
        base *= base;
    return base;
}

//bubble sort
void bubblesort(int array[], int size)
{ //increasing order
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (array[j] < array[i])
                swap(&array[j], &array[i]);
}
void bubblesort_(int array[], int size)
{ //dec order
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (array[j] > array[i])
                swap(&array[j], &array[i]);
}

//selection sort
void selectionsort(int array[], int size)
{ //asc order
    for (int i = 0; i < size; i++)
    {
        int smallest = array[i];
        for (int j = i; j < size; j++) //finding smallest
            if (smallest > array[j])
                swap(&smallest, &array[j]);
        swap(&array[i], &smallest);
    }
}
void selectionsort_(int array[], int size)
{ //desc order
    for (int i = 0; i < size; i++)
    {
        int largest = array[i];
        for (int j = i; j < size; j++)
            if (largest < array[j])
                swap(&largest, &array[j]);
        swap(&array[i], &largest);
    }
}

//insertion sort
void insertionsort(int array[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int t = array[i], j = i - 1;
        while (t < array[j] && j >= 0) //pushing to the left
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = t; //last update
    }
}
void insertionsort_(int array[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int t = array[i], j = i - 1;
        while (t > array[j] && j >= 0)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = t; //last update
    }
}

//merge sort
void merge(int array[], int size, int a, int b, int c)
{                //merge arr[a..b] and arr[b+1..c] into arr[a..c]
    int i, j, k, //random variables for loop
        size_of_a = b - a + 1, size_of_b = c - b,
        A[size_of_a], B[size_of_b]; //2 temp array for copy pasting

    for (i = 0; i < size_of_a; i++) //copying entries
        A[i] = array[a + i];
    for (j = 0; j < size_of_b; j++)
        B[j] = array[b + 1 + j];

    i = j = 0;
    k = a; //resetting variables

    while (i < size_of_a && j < size_of_b)
    { //merging
        if (A[i] >= B[j])
        {
            array[k] = B[j];
            j++;
        }
        else
        {
            array[k] = A[i];
            i++;
        }
        k++;
    }
    //filling remaining entries if anyone left
    while (i < size_of_a)
    {
        array[k] = A[i];
        i++;
        k++;
    }
    //same for another arrayF
    while (j < size_of_b)
    {
        array[k] = B[j];
        j++;
        k++;
    }
}
void mergesort(int array[], int size, int p, int q)
{
    int mid = (p + q) / 2;
    if (p < q)
    {
        mergesort(array, size, p, mid);
        mergesort(array, size, mid + 1, q);
        merge(array, size, p, mid, q);
    }
}

void merge_(int array[], int size, int a, int b, int c)
{
    int i, j, k,
        size_of_a = b - a + 1, size_of_b = c - b,
        A[size_of_a], B[size_of_b];

    for (i = 0; i < size_of_a; i++)
        A[i] = array[a + i];
    for (j = 0; j < size_of_b; j++)
        B[j] = array[b + j + 1];
    i = j = 0;
    k = a;
    while (i < size_of_a && j < size_of_b)
    {
        if (A[i] <= B[j])
        {
            array[k] = B[j];
            j++;
        }
        else
        {
            array[k] = A[i];
            i++;
        }
        k++;
    }
    while (i < size_of_a)
    {
        array[k] = A[i];
        k++;
        i++;
    }
    while (j < size_of_b)
    {
        array[k] = B[j];
        k++;
        j++;
    }
}
void mergesort_(int array[], int size, int p, int q)
{
    int mid = (p + q) / 2;
    if (p < q)
    {
        mergesort_(array, size, p, mid);
        mergesort_(array, size, mid + 1, q);
        merge_(array, size, p, mid, q);
    }
}

//quick sort
int partition(int array[], int size, int p, int q)
{ //complicated
    int pivot = array[q],
        i = p - 1;
    for (int j = p; j < q; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[q]);
    return (i + 1);
}
void quicksort(int arrray[], int size, int p, int q)
{
    if (p < q)
    {
        int part = partition(arrray, size, p, q);
        quicksort(arrray, size, p, part - 1);
        quicksort(arrray, size, part + 1, q);
    }
}
void quicksort_(int array[], int size, int p, int q)
{
    quicksort(array, size, p, q);
    for (int i = 0; i < size / 2; i++)
        swap(&array[i], &array[size - i - 1]);
}
//counting sort
void countingsort(int array[], int size)
{
    int max = array[0], i, t, s, copy[size];
    for (i = 1; i < size; i++)
        if (max < array[i])
            max = array[i];

    int temp[max + 1];

    for (i = 0; i < max + 1; i++)
        temp[i] = 0;

    for (i = 0; i < size; i++)
    {
        temp[array[i]]++;
        copy[i] = array[i];
    }

    for (i = 1; i < max + 1; i++)
        temp[i] += temp[i - 1];
    for (i = 0; i < size; i++)
    {
        t = copy[i];
        temp[t]--;
        s = temp[t];
        array[s] = t;
    }
}
void countingsort_(int array[], int size)
{
    int max = array[0], i, t, s, copy[size];
    for (i = 1; i < size; i++)
        if (max < array[i])
            max = array[i];
    int temp[max + 1];
    for (i = 0; i < max + 1; i++)
        temp[i] = 0;

    for (i = 0; i < size; i++)
    {
        temp[array[i]]++;
        copy[i] = array[i];
    }

    for (i = 1; i < max + 1; i++)
        temp[i] += temp[i - 1];

    for (i = 0; i < size; i++)
    {
        t = copy[i];
        temp[t]--;
        s = temp[t];
        array[s] = t;
    }
    for (i = 0; i < size / 2; i++)
        swap(&array[i], &array[size - i - 1]);
}

//shell
void shellsort_(int array[], int size)
{ //doubt
    for (int i = size / 2; i > 0; i /= 2)
    {
        for (int j = i; j < size; j++)
        {
            int temp = array[j], k;
            for (k = j; k >= i && array[k - i] < temp; k -= i)
                array[k] = array[k - i];
            array[k] = temp;
        }
    }
}
void shellsort(int array[], int size)
{ //doubt
    for (int i = size / 2; i > 0; i /= 2)
    {
        for (int j = i; j < size; j++)
        {
            int temp = array[j], k;
            for (k = j; k >= i && array[k - i] > temp; k -= i)
                array[k] = array[k - i];
            array[k] = temp;
        }
    }
}

//radix
void radixsort(int array[], int size)
{
    int max = array[0],
        digits = 0, i, clone[size], j, k;
    //search for max
    for (i = 1; i < size; i++)
        if (max < array[i])
            max = array[i];
    while (max >= 1)
    {
        max /= 10;
        digits++;
    }
    for (i = 0; i < digits; i++)
    {
        for (j = 0; j < size; j++)
            clone[j] = array[j] % power(10, i + 1);
        //checking clone but arranging array
        //bubble sort
        for (j = 0; j < size; j++)
        {
            for (k = j; k < size; k++)
            {
                if (clone[k] < clone[j])
                {
                    swap(&array[k], &array[j]);
                    swap(&clone[j], &clone[k]);
                }
            }
        }
    }
}
void radixsort_(int array[], int size)
{
    int max = array[0], i, j, k, digits = 0, clone[size];
    //search for max
    for (i = 1; i < size; i++)
        if (max < array[i])
            max = array[i];
    while (max >= 1)
    {
        max /= 10;
        digits++;
    }
    for (i = 0; i < digits; i++)
    {
        for (j = 0; j < size; j++)
            clone[j] = array[j] % power(10, i + 1);
        //bubble sort
        for (j = 0; j < size; j++)
        {
            for (k = j; k < size; k++)
            {
                if (clone[k] > clone[j])
                {
                    swap(&clone[j], &clone[k]);
                    swap(&array[j], &array[k]);
                }
            }
        }
    }
}

//heap
//ascending
void maxheapify(int array[], int size, int i)
{ //maxheap
    int leftchild = 2 * i + 1,
        rightchild = 2 * i + 2,
        largest = i;
    if (leftchild < size && array[leftchild] > array[largest])
        largest = leftchild;
    if (rightchild < size && array[rightchild] > array[largest])
        largest = rightchild;
    if (largest != i)
    {
        swap(&array[largest], &array[i]);
        maxheapify(array, size, largest);
    }
}
void maxheapsort(int array[], int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
        maxheapify(array, size, i);
    for (int i = size - 1; i >= 0; i--)
    {
        swap(&array[0], &array[i]);
        maxheapify(array, i, 0);
    }
}

void minheap(int array[], int size, int i)
{
    int smallest = i,
        leftchild = 2 * i + 1,
        rightchild = 2 * i + 2;
    if (leftchild < size && array[smallest] > array[leftchild])
        smallest = leftchild;
    if (rightchild < size && array[smallest] > array[rightchild])
        smallest = rightchild;
    if (smallest != i)
    {
        swap(&array[i], &array[smallest]);
        minheap(array, size, smallest);
    }
}
void minheapsort(int array[], int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
        minheap(array, size, i);
    for (int i = size - 1; i >= 0; i--)
    {
        swap(&array[0], &array[i]);
        minheap(array, i, 0);
    }
}

void main()
{
    int size = 20, arr[] = {34, 5, 6, 7, 12, 5, 23, 70, 89, 76, 4, 0, 4, 23, 43, 129, 54, 44, 88, 2};
    minheapsort(arr, size);
    printf("Sorted Array : ");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
}