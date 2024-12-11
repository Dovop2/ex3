/******************
Name: Dov Prashizky
ID: 215945569
Assignment: ex3
*******************/

#include <stdio.h>
#include <time.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};


void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}
// Set everything in the cube to -1
void emptyCube(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int numOfBrands, int numOfTypes, int numOfDays) {
    for (int day = 0; day < numOfDays; day++) {
        for (int brand = 0; brand < numOfBrands; brand++) {
            for (int type = 0; type < numOfTypes; type++) {
                cube[day][brand][type] = -1;
            }
        }
    }
}

void insert(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brandIndex, int currentDay,
    int suvSales, int sedanSales, int coupeSales, int gtSales) {
    arr[currentDay][brandIndex][0] = suvSales;
    arr[currentDay][brandIndex][1] = sedanSales;
    arr[currentDay][brandIndex][2] = coupeSales;
    arr[currentDay][brandIndex][3] = gtSales;
}

// Checks if given brand doesnt have value yet
int checkEmpty(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brandIndex, int currentDay) {
        if (arr[currentDay][brandIndex][0] == -1)
            return brandIndex;
        return -1;
}
// Print the brands name
void printBrand(int brandIndex) {
    for (int i = 0; brands[brandIndex][i] != 0; i++) {
        printf("%c", brands[brandIndex][i]);
    }
}
// Print the type name
void printType(int brandIndex) {
    for (int i = 0; types[brandIndex][i] != 0; i++) {
        printf("%c", types[brandIndex][i]);
    }
}
int brandSales(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brandIndex, int currentDay, int numOfTypes) {
    int sum = 0;
    for(int type = 0; type < numOfTypes; type++) {
        sum = sum + arr[currentDay][brandIndex][type];
    }
    return sum;
}

int brandSalesTotal(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brandIndex, int currentDay,
    int numOfTypes) {
    int brandTotal = 0;
    for(int day = 0; day < currentDay; day++) {
        brandTotal = brandTotal + brandSales(arr, brandIndex, day, numOfTypes);
    }
    return brandTotal;
}

int typeSales(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int typeIndex, int currentDay, int numOfBrands) {
    int sum = 0;
    for(int brand = 0; brand < numOfBrands; brand++) {
        sum = sum + arr[currentDay][brand][typeIndex];
    }
    return sum;
}
int typeSalesTotal(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
    int typeIndex, int currentDay, int numOfBrands) {
    int typeTotal = 0;
    for(int day = 0; day < currentDay; day++) {
        typeTotal = typeTotal + typeSales(arr, typeIndex, day, numOfBrands);
    }
    return typeTotal;
}
int daySalesTotal(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
    int currentDay, int numOfTypes, int numOfBrands) {
    int dayTotal = 0;
    for(int type = 0; type < numOfTypes; type++) {
        dayTotal = dayTotal + typeSales(arr, type, currentDay, numOfBrands);
    }
    return dayTotal;
}

void printBrandSales(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
    int brandIndex, int currentDay, int numOfTypes ) {
    printf("Sales for ");
    printBrand(brandIndex);
    printf(":\n");
    for(int day = 0; day < currentDay; day++) {
        printf("Day %d- ", day + 1);
        for(int type = 0; type < numOfTypes; type++) {
            printType(type);
            printf(": %d ", arr[day][brandIndex][type]);
        }
        printf("\n");
    }
}

double brandDelta(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brandIndex, int currentDay, int numOfTypes) {
    double brandDelta = 0;
    double totalDelta = 0;
    for(int day = 1; day < currentDay; day++) {
        brandDelta = brandSales(arr, brandIndex, day, numOfTypes) - brandSales(arr, brandIndex, day - 1, numOfTypes);
        totalDelta = totalDelta + brandDelta;
    }
    return totalDelta / (currentDay - 1);
}


int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int choice, suvSales, sedanSales, coupeSales, gtSales, brandIndex, statsDay, bestBrandSales = 0, bestBrand,
    bestType, overallSale = 0, currentDay = 0,  bestTypeSales = 0, bestBrandSalesTotal = 0, bestBrandSalesTotalI,
     bestSellingDay, bestSellingDaySales, bestTypeSalesTotal = 0, bestTypeSalesTotalI;
    emptyCube(cube, NUM_OF_BRANDS, NUM_OF_TYPES, DAYS_IN_YEAR);
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice){
            case addOne:
                scanf("%d%d%d%d%d", &brandIndex, &suvSales, &sedanSales, &coupeSales, &gtSales);
                insert(cube, brandIndex, currentDay, suvSales, sedanSales, coupeSales, gtSales);
                break;
            case addAll:
                while (1) {
                    // Check for empty brands and print them
                    int isEmpty = 1;
                    for(int i = 0; i < NUM_OF_BRANDS; i++) {
                        if(checkEmpty(cube, i, currentDay) != -2) {
                            if(isEmpty)
                                printf("No data for brands ");
                            printBrand(i);
                            printf(" ");
                            isEmpty = 0;
                        }
                    }
                    // If no more empty brands are left, increase day and break;
                    if(isEmpty) {
                        currentDay = currentDay + 1;
                        break;
                    }
                    printf("\nPlease complete the data\n");
                    // Scan sales for specific brand
                    scanf("%d", &brandIndex);
                    // Check if brand is valid
                    if((brandIndex <= 4 && brandIndex >= 0) && checkEmpty(cube, brandIndex, currentDay) != -1)  {
                        scanf("%d%d%d%d", &suvSales, &sedanSales, &coupeSales, &gtSales);
                        // Brand is valid, insert into array
                        insert(cube, brandIndex, currentDay, suvSales, sedanSales, coupeSales, gtSales);
                    }
                    else {
                        printf("This brand is not valid\n");
                    }
                }
            break;
            case stats:
                while (1) {
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &statsDay);
                    int newDay = statsDay - 1;
                    // Check if day is valid
                    if((newDay >= 0 && newDay <= DAYS_IN_YEAR) && checkEmpty(cube, 0, newDay) == -2) {
                        printf("In day number %d\n", statsDay);
                        for(int i = 0; i < NUM_OF_BRANDS; i++) {
                            overallSale = overallSale + brandSales(cube, i, newDay,NUM_OF_TYPES);
                        }
                        printf("The sales total was %d\n", overallSale);
                        for(int i = 0; i < NUM_OF_BRANDS; i++) {
                            if(bestBrandSales < brandSales(cube, i, newDay, NUM_OF_TYPES)) {
                                bestBrandSales = brandSales(cube, i, newDay, NUM_OF_TYPES);
                                bestBrand = i;
                            }
                        }
                        printf("The best sold brand with %d sales was ", bestBrandSales);
                        printBrand(bestBrand);
                        for(int i = 0; i < NUM_OF_TYPES; i++) {
                            if (bestTypeSales < typeSales(cube, i, newDay, NUM_OF_BRANDS)){
                                bestTypeSales = typeSales(cube, i, newDay, NUM_OF_BRANDS);
                                bestType = i;
                            }
                        }
                        printf("\nThe best sold type with %d sales was ", bestTypeSales);
                        printType(bestType);
                        printf("\n");
                        break;


                    }
                    else {
                        printf("Please enter a valid day\n");
                        break;
                    }
                }
            break;
            // Prints all available data for sales until current day
            case print:
                printf("*****************************************\n\n");
                for(int brand = 0; brand < NUM_OF_BRANDS; brand++) {
                        printBrandSales(cube, brand, currentDay, NUM_OF_TYPES);
                }
                printf("\n*****************************************\n");
                break;
            case insights:
                printf("The best-selling brand overall is ");
                for(int brand = 0; brand < NUM_OF_BRANDS; brand++) {
                        if(bestBrandSalesTotal < brandSalesTotal(cube, brand, currentDay, NUM_OF_TYPES )) {
                            bestBrandSalesTotal = brandSalesTotal(cube, brand, currentDay, NUM_OF_TYPES);
                            bestBrandSalesTotalI = brand;
                    }
                }
                printBrand(bestBrandSalesTotalI);
                printf(": %d$\n", bestBrandSalesTotal);
                printf("The best-selling type of car is ");
                for(int type = 0; type < NUM_OF_TYPES; type++) {
                    if(bestTypeSalesTotal < typeSalesTotal(cube, type, currentDay, NUM_OF_BRANDS)) {
                        bestTypeSalesTotal = typeSalesTotal(cube, type, currentDay, NUM_OF_BRANDS);
                        bestTypeSalesTotalI = type;
                    }
                }
                printType(bestTypeSalesTotalI);
                printf(": %d$\n", bestTypeSalesTotal);
                printf("The most profitable day was day number ");
                for(int day = 0; day < currentDay; day++) {
                    if(bestSellingDaySales < daySalesTotal(cube, day, NUM_OF_TYPES,
                        NUM_OF_BRANDS)) {
                        bestSellingDaySales = daySalesTotal(cube, day, NUM_OF_TYPES,
                            NUM_OF_BRANDS);
                        bestSellingDay = day + 1;
                    }
                }
                printf("%d: %d$\n", bestSellingDay, bestSellingDaySales);
                break;
            case deltas:
                for(int brand = 0; brand < NUM_OF_BRANDS; brand++) {
                    printf("Brand: ");
                    printBrand(brand);
                    printf(",  Average Delta: %f\n", brandDelta(cube, brand, currentDay, NUM_OF_TYPES));

                }
            break;


            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}


