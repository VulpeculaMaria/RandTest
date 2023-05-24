#include<fstream>
#include<iostream>
#include<string>
#include<cstdlib>
#include<chrono>  //for getting time
using namespace std;

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int* arr, int start, int end)
{
    int pivot = arr[start];
    int count = 0;

    for(int i = start + 1; i <= end; i++) {if(arr[i] <= pivot){count++;}}
    int pivot_index = start + count;
    swap(arr[pivot_index], arr[start]);

    int i = start; int j = end;
    while(i < pivot_index && j > pivot_index)
    {
        while(arr[i] <= pivot){i++;}
        while(arr[j] > pivot) {j--;}
        if(i < pivot_index && j > pivot_index) {swap(arr[i++], arr[j--]);}
    }

    return pivot_index;
}
void QuickSort(int arr[], int start, int end)
{
    if(start >= end) {return;}
    int p = partition(arr, start, end);
    QuickSort(arr, start, p-1);
    QuickSort(arr, p+1, end);

}
void write_arr(string filename, int* arr, int size)
{
    fstream fs;
    fs.open(filename, fstream::out);
    if(fs.is_open())
    {
        fs << size << endl;
        for(int i = 0; i < size; ++i) {fs << arr[i] << ' ';}
        fs << '\n';
        fs.close();
    }

}
void read_arr(const string& filename, int*& arr, int& size)
{
    fstream fs;
    fs.open(filename, fstream::in);
    if(fs.is_open())
    {
        fs >> size;
        arr = new int[size];
        for(int i = 0; i < size; ++i) {fs >> arr[i];}
        fs.close();
    }


}
void print(int* arr, int n) 
{ 
    for (int i = 0; i < n; i++) 
        cout << arr[i] << " "; 
    cout << endl;
}

int main()
{
    string file = "MyHwFile.txt";
    const int size = 500000;
    int* arr_rand = new int[size];
    srand(time(nullptr)); // используем текущее время, чтобы сгенерировать рандомные значения

    int min_border = 5;
    int range_len = 1000;

    for(int i = 0; i < size; ++i) {arr_rand[i] = min_border + rand() % range_len;} //circle for writing random to arr 
    write_arr(file, arr_rand, size); // write arr to file
    int* array_from_file = new int[size];
    for(int i = 0; i < size; ++i)
    {
        array_from_file[i] = arr_rand[i];
    }
    QuickSort(array_from_file, 0, size);
    write_arr(file, array_from_file, size);
  
    getchar();
}