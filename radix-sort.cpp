#include <iostream>
#include <limits>
#include <new>
using namespace std;

int integerInput();
int getSize();
void radixSort(int[], int);
void countingSort(int[], int, int);
int getMax(int[], int);
void displayArray(int[], int);

int main()
{
	int size, * arr;

	cout << "Enter the size of the array: ";
	size = getSize();
	arr = new (nothrow) int[size];
	if (arr == nullptr)
	{
		cout << endl << "Failed to allocate memory! Please restart the application.";
		exit(0);
	}

	cout << endl << "Enter all the elements of the array: ";
	for (int i = 0; i < size; i++)
	{
		arr[i] = integerInput();
		if (size - i - 1 == 0)
			break;
		cout << "Elements remaining to be entered: " << size - i - 1 << endl;
	}

	radixSort(arr, size);
	displayArray(arr, size);

	return 0;
}

int integerInput()
{
	int n;

	while (!(cin >> n))
	{
		cin.clear();
		cin.ignore(numeric_limits <streamsize>::max(), '\n');
		cout << endl << "Invalid integer input! Please try again with correct input: ";
	}

	return n;
}

int getSize()
{
	int size = integerInput();

	if (size <= 0)
	{
		cout << endl << "Invalid size! Please try again: ";
		size = getSize();
	}

	return size;
}

void radixSort(int arr[], int size)
{
	int max = getMax(arr, size);

	for (int div = 1; max / div > 0; div *= 10)
	{
		countingSort(arr, div, size);
	}
}

void countingSort(int arr[], int div, int size)
{
	int range = 10;
	int* sortedArr = new (nothrow) int[size];
	int* count = new (nothrow) int[range];
	if (sortedArr == nullptr || count == nullptr)
	{
		cout << endl << "Failed to allocate memory! Please restart the application.";
		exit(0);
	}

	for (int i = 0; i < range; i++)
	{
		count[i] = 0;
	}

	for (int i = 0; i < size; i++)			// Counting all unique elements in the array
	{
		count[(arr[i] / div) % 10]++;
	}

	for (int i = 1; i < range; i++)			// Cumulatively adding all the counting values
	{
		count[i] += count[i - 1];
	}

	for (int i = size - 1; i >= 0; i--)
	{
		sortedArr[count[(arr[i] / div) % 10] - 1] = arr[i];// Assigning the values to the output array in ascending order
		count[(arr[i] / div) % 10]--;
	}

	for (int i = 0; i < size; i++)
	{
		arr[i] = sortedArr[i];
	}
}

int getMax(int arr[], int size)
{
	int max = arr[0];
	for (int i = 1; i < size; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}

	return max;
}

void displayArray(int arr[], int size)
{
	cout << endl << "The sorted array is: ";

	for (int i = 0; i < size; i++)
	{
		cout << "|" << arr[i] << "|";
	}
}