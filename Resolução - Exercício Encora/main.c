#include <stdio.h>
#include <stdlib.h>

// Define a struct to represent a coin combination
typedef struct {
    int quarters;
    int dimes;
    int nickels;
    int pennies;
} CoinCombination;

// Function to create a new CoinCombination
CoinCombination createCombination(int quarters, int dimes, int nickels, int pennies) {
    CoinCombination combo = {quarters, dimes, nickels, pennies};
    return combo;
}

// Function to recursively calculate and return the best combination representing n cents
CoinCombination makeChange(int n, CoinCombination currentCombination) {
    if (n == 0) {
        // Base case: return the current combination
        return currentCombination;
    } else if (n < 0) {
        // Invalid input: return a combination with large values
        return createCombination(100, 1000, 100, 100);
    }

    // Try using each coin and choose the combination with the fewest coins
    CoinCombination bestCombination = createCombination(100, 100, 100, 100);

    CoinCombination combinationWithQuarter = makeChange(n - 25, createCombination(currentCombination.quarters + 1, currentCombination.dimes, currentCombination.nickels, currentCombination.pennies));

    if (combinationWithQuarter.quarters < bestCombination.quarters) {
        bestCombination = combinationWithQuarter;
    }

    CoinCombination combinationWithDime = makeChange(n - 10, createCombination(currentCombination.quarters, currentCombination.dimes + 1, currentCombination.nickels, currentCombination.pennies));

    if (combinationWithDime.quarters + combinationWithDime.dimes < bestCombination.quarters + bestCombination.dimes) {
        bestCombination = combinationWithDime;
    }

    CoinCombination combinationWithNickel = makeChange(n - 5, createCombination(currentCombination.quarters, currentCombination.dimes, currentCombination.nickels + 1, currentCombination.pennies));

    if (combinationWithNickel.quarters + combinationWithNickel.dimes + combinationWithNickel.nickels <
        bestCombination.quarters + bestCombination.dimes + bestCombination.nickels) {
        bestCombination = combinationWithNickel;
    }

    CoinCombination combinationWithPenny = makeChange(n - 1, createCombination(currentCombination.quarters, currentCombination.dimes, currentCombination.nickels, currentCombination.pennies + 1));

    if (combinationWithPenny.quarters + combinationWithPenny.dimes + combinationWithPenny.nickels + combinationWithPenny.pennies <
        bestCombination.quarters + bestCombination.dimes + bestCombination.nickels + bestCombination.pennies) {
        bestCombination = combinationWithPenny;
    }

    return bestCombination;
}

// Example usage:
int main() {
    int n;
    printf("Enter the value (in cents): ");
    scanf("%d", &n);

    CoinCombination initialCombination = createCombination(0, 0, 0, 0);
    CoinCombination bestCombination = makeChange(n, initialCombination);

    // Print the best combination:
    printf("Best combination for %d cents (optimized): [%d, %d, %d, %d]\n",
           n, bestCombination.quarters, bestCombination.dimes, bestCombination.nickels, bestCombination.pennies);

    return 0;
}

