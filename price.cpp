#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "price.header.h"

using namespace std;

int multiplyPrice(Price p1, int multiplier) {
    //return (p.hryvnias * 100 + p.kopiykas) * multiplier;
    p1.hryvnias *= multiplier;
    p1.kopiykas *= multiplier;
    return 0;
}

int addPrices(Price p1, const Price& p2) {
    //return (p1.hryvnias * 100 + p1.kopiykas) + (p2.hryvnias * 100 + p2.kopiykas);
    p1.hryvnias += p2.hryvnias;
    p1.kopiykas += p2.kopiykas;
    if (p1.kopiykas >= 100) {
        p1.hryvnias += p1.kopiykas / 100;
        p1.kopiykas %= 100;
    }
    return 0;
}

int roundPrice(Price p1) {
    int totalKopiykas = p1.hryvnias * 100 + p1.kopiykas;
    totalKopiykas = round(static_cast<double>(totalKopiykas)); // Round to the nearest integer
    p1.hryvnias = totalKopiykas / 100;
    p1.kopiykas = totalKopiykas % 100;
    return 0;
}

void displayResults(int productCount, const Price& totalBeforeRounding, const Price& totalAfterFix) {

}

void processPrices() {
    ifstream file("price.txt");
    if (!file) {
        cerr << "Помилка відкриття файлу!" << endl;
        return;
    }

    //vector<Price> prices; // Динамічний список цін
    Price temp = {0,0};
    Price sum = {0, 0};
    int grn;
    short int kop;
    int quantity;

    // Читаємо всі ціни з файлу
    while (file >> grn >> kop >> quantity) {
        sum = {grn, kop};
        multiplyPrice(sum, quantity);
        addPrices(temp, sum);
    }

    roundPrice(sum);

    file.close();

    cout << "Загальна ціна: " << sum.hryvnias << " грн. " << sum.kopiykas << " коп." << endl;

}
