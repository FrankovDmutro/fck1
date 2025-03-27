#include <iostream>
#include <fstream>
#include <cmath>

#include "price.header.h"

using namespace std;

int multiplyPrice(Price& p1, int multiplier) {
    int totalKopiykas = (p1.hryvnias * 100 + p1.kopiykas) * multiplier;
    p1.hryvnias = totalKopiykas / 100;
    p1.kopiykas = totalKopiykas % 100;
    return 0;
}

int addPrices(Price& p1, const Price& p2) {
    p1.hryvnias += p2.hryvnias;
    p1.kopiykas += p2.kopiykas;
    if (p1.kopiykas >= 100) {
        p1.hryvnias += p1.kopiykas / 100;
        p1.kopiykas %= 100;
    }
    return 0;
}

int roundPrice(Price& p1) {
    //Тут (totalKopiykas + 5) / 10 * 10 округлює до найближчого десятка копійок.
    int totalKopiykas = (p1.hryvnias * 100 + p1.kopiykas + 5) / 10 * 10;
    p1.hryvnias = totalKopiykas / 100;
    p1.kopiykas = totalKopiykas % 100;
    return 0;
}

void processPrices() {
    ifstream file("price.txt");
    if (!file) {
        cerr << "Помилка відкриття файлу!" << endl;
        return;
    }

    Price temp = {0, 0};
    Price sum = {0, 0};
    // int grn;
    // short int kop;
    int quantity;

    while (file >> temp.hryvnias >> temp.kopiykas >> quantity) {
        // sum = {grn, kop};
        multiplyPrice(temp, quantity);
        addPrices(sum, temp);
    }
    file.close();

    cout << "Загальна ціна: " << sum.hryvnias << " грн. " << sum.kopiykas << " коп." << endl;
    roundPrice(sum);
    cout << "Заокруглена ціна: " << sum.hryvnias << " грн. " << sum.kopiykas << " коп." << endl;
}