#ifndef PRICE_HEADER_H
#define PRICE_HEADER_H

struct Price {
    int hryvnias;
    short kopiykas;
};

int multiplyPrice(Price& p1, int multiplier);
int addPrices(Price& p1, const Price& p2);
int roundPrice(Price& p1);

void processPrices();

#endif // PRICE_HEADER_H
