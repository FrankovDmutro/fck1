#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "price.header.h"

using namespace std;

int multiplyPrice(Price& p1, int multiplier) {
    p1.hryvnias *= multiplier;
    p1.kopiykas *= multiplier;
    if (p1.kopiykas >= 100) {
        p1.hryvnias += p1.kopiykas / 100;
        p1.kopiykas %= 100;
    }
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
    // Перетворюємо гривні та копійки в загальну кількість копійок
    int totalKopiykas = p1.hryvnias * 100 + p1.kopiykas;
    // Округлюємо до найближчого десятка копійок
    totalKopiykas = round(totalKopiykas / 10.0) * 10;
    // Перетворюємо назад у гривні та копійки
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
    int grn;
    short int kop;
    int quantity;

    while (file >> grn >> kop >> quantity) {
        sum = {grn, kop};
        multiplyPrice(sum, quantity);
        addPrices(temp, sum);
    }
    file.close();

    cout << "Загальна ціна заокруглення: " << temp.hryvnias << " грн. " << temp.kopiykas << " коп." << endl;
    roundPrice(temp);
    cout << "Загальна ціна: " << temp.hryvnias << " грн. " << temp.kopiykas << " коп." << endl;
}