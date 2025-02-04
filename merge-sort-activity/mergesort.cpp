/*sbatch to run on compute node
sbatch --mem=32G --time=01:00:00 --partition=Centaurus ./script.sh
slurm-##.out
mv slurm.out output.csv
git add output.csv
add script.sh
git commit
can use excel/lib
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

int* arrayRandomizer(int size);
int* mergeSort(int* array, int size);
int* merge(int* leftSide, int leftSize, int* rightSide, int rightSize);

int main(int argc, char* argv[]) {
    //check number of arguments
    if (argc != 2) {
        std::cout << "Invalid number of arguments" << std::endl;
        return 0;
    }

    //convert string to size_t
    size_t size = std::stoi(argv[1]);

    //std::cout << size << ", " <<size + 2 << "\n";


    //change seed to current time
    srand(time(0));

    //create array of random ints
    int* array = arrayRandomizer(size);
    std::cout << "Unsorted array: " << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    //sort array
    std::cout << "Sorted array: " << std::endl;
    int* sortedArray = mergeSort(array, size);
    for (int i = 0; i < size; i++) {
        std::cout << sortedArray[i] << " ";
    }
    std::cout << std::endl;

    //delete arrays
    delete[] array;
    delete[] sortedArray;
    return 0;
}

int* arrayRandomizer(int size) {
    int* array = new int[size];
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100;
    }
    return array;
}

int* mergeSort(int* array, int size) {
    //base case
    if (size == 1) {
        int* newArray = new int[1];
        newArray[0] = array[0];
        return newArray;
    }
    int middle = size / 2;
    //allocate new arrays
    int* leftSide = new int[middle];
    for (int i = 0; i < middle; i++) {
        leftSide[i] = array[i];
    }

    int* rightSide = new int[size - middle];
    for (int i = middle; i < size; i++) {
        rightSide[i - middle] = array[i];
    }
    //recursive call
    int* sortedLeftSide = mergeSort(leftSide, middle);
    int* sortedRightSide = mergeSort(rightSide, size - middle);

    //delete arrays
    delete[] leftSide;
    delete[] rightSide;

    int* mergedArray = merge(sortedLeftSide, middle, sortedRightSide, size - middle);

    //delete arrays
    delete[] sortedLeftSide;
    delete[] sortedRightSide;

    return mergedArray;
}

int* merge(int* leftSide,int leftSize, int* rightSide, int rightSize) {
    int* newArray = new int[leftSize + rightSize];
    int a = 0, b = 0, c = 0;
    //while both arrays have elements, add the smaller element to the new array
    while (a < leftSize && b < rightSize) {
        if (leftSide[a] <= rightSide[b]) {
            newArray[c] = leftSide[a]; 
            c++;
            a++;
        } else {
            newArray[c] = rightSide[b];
            c++;
            b++;
        }
    }
    //add remaining elements
    while (a < leftSize) {
        newArray[c] = leftSide[a];
        c++;
        a++;
    }
    while (b < rightSize) {
        newArray[c] = rightSide[b];
        c++;
        b++;
    }
    return newArray;
}