
#include <iostream>
#include "Order.h"

#define NOTEBOOKS_COUNT 3
Notebook* notebooks[NOTEBOOKS_COUNT] = { new Notebook("Realme RMNB1002", "realme", "", 8, 512, 45700, new CPU("Intel Core i5 1135G7", 2400), new Videocard("Integrated", 0)),
    new Notebook("Lenovo IdeaPad 3", "Lenovo", "", 8, 256, 29635, new CPU("Intel Celeron N4020", 1100), new Videocard("Integrated", 0)),
    new Notebook("Thunderobot 911 Air Wave D", "ThundeRobot", "", 8, 256, 85999, new CPU("Intel Core i5 11400H", 2700), new Videocard("NVIDIA GeForce RTX 3050M", 4)) };


#define TABLETS_COUNT 3
Tablet* tablets[TABLETS_COUNT] = { new Tablet("Lenovo Tab M10 Plus TB128XU", "Lenovo", "", 4, 128, 24999, new CPU("Qualcomm Snapdragon 680", 2400), "12"),
    new Tablet("HONOR Pad 8 W-Fi", "HONOR", "", 6, 128, 24999, new CPU("Qualcomm Snapdragon 680", 2400), "12"),
    new Tablet("HUAWEI MatePad T 8.0", "HUAWEI", "", 3, 32, 11888, new CPU("MediaTek MT8768", 2000), "10 (no Google services)")};


#define PHONES_COUNT 3
Phone* phones[PHONES_COUNT] = { new Phone("Nothing Phone (1) 8/256 GB", "Nothing", "", 8, 256, 44999, new CPU("Qualcomm Snapdragon 778G Plus", 2400), "12"),
    new Phone("Realme 10 8/256 GB", "realme", "", 8, 256, 23999, new CPU("MediaTek Helio G99", 2200), "12"),
    new Phone("Xiaomi POCO M5s 4/64 GB", "Xiaomi", "", 4, 64, 15990, new CPU("MediaTek Helio G95", 2050), "12") };

std::string dot_or_comma(int index, int max) {
    if (index < max - 1) return "; ";
    else return ".\n";
}

Queue<Order> orders;

void add_to_order(Order& o) {
    int input, i;
    std::string end;
    Device* ordered;

    std::cout << "\nEnter type of ordered device: \"1\" for notebook, \"2\" for phone, \"3\" for tablet: ";
    std::cin >> input;
    switch (input)
    {
    case 1:
        std::cout << "Currently we have " + std::to_string(NOTEBOOKS_COUNT) + " notebook models: ";
        for (i = 0; i < NOTEBOOKS_COUNT; i++) std::cout << std::to_string(i + 1) + ") " + notebooks[i]->get_name() + dot_or_comma(i, NOTEBOOKS_COUNT);
        std::cout << "Enter index of ordered notebook model: ";
        std::cin >> input;
        if (input - 1 >= 0 && input - 1 < NOTEBOOKS_COUNT) ordered = notebooks[input - 1];
        else {
            std::cout << "Error! No such notebook index! Try again";
            return;
        }
        break;
    case 2:
        std::cout << "Currently we have " + std::to_string(PHONES_COUNT) + " phone models: ";
        for (i = 0; i < PHONES_COUNT; i++) std::cout << std::to_string(i + 1) + ") " + phones[i]->get_name() + dot_or_comma(i, PHONES_COUNT);
        std::cout << "Enter index of ordered phone model: ";
        std::cin >> input;
        if (input - 1 >= 0 && input - 1 < PHONES_COUNT) ordered = phones[input - 1];
        else {
            std::cout << "Error! No such phone index! Try again\n";
            return;
        }
        break;
    case 3:
        std::cout << "Currently we have " + std::to_string(TABLETS_COUNT) + " tablet models: ";
        for (i = 0; i < TABLETS_COUNT; i++) std::cout << std::to_string(i + 1) + ") " + tablets[i]->get_name() + dot_or_comma(i, TABLETS_COUNT);
        std::cout << "Enter index of ordered tablet model: ";
        std::cin >> input;
        if (input - 1 >= 0 && input - 1 < TABLETS_COUNT) ordered = tablets[input - 1];
        else {
            std::cout << "Error! No such tablet index! Try again\n";
            return;
        }
        break;
    default:
        std::cout << "Error! Unexpected input! Try again\n";
        return;
    }
    std::cout << "Enter amount of ordered devices: ";
    std::cin >> input;
    o.add_to_order(ordered, input);
}

void edit_order(Order& o) {
    int input, i;
    std::string end;

    std::cout << "\nCurrent order info:\n" + o.print();
    std::cout << "\nEnter index of the order part you want to edit or remove: ";

    std::cin >> i;
    if (i - 1 < 0 || i - 1 >= o.count()) 
    {
        std::cout << "Error! No order part with such index! Try again\n";
        return;
    }

    std::cout << "If you want to edit this part of order enter \"1\", otherwise, if you want to remove it enter \"2\": ";
    std::cin >> input;
    auto& elem = o.get(i - 1);
    switch (input)
    {
    case 1:
        std::cout << "Enter new amount of devices in this entry: ";
        std::cin >> input;
        elem.second = input;
        std::cout << "Amount of devices changed.\n";
        break;
    case 2:
        o.remove(i - 1);
        std::cout << "Order entry " + std::to_string(input) + " successfuly removed.\n";
        break;
    default:
        std::cout << "Error! Unexpected input! Try again\n";
        return;
    }
}

void register_order() {
    int input;
    std::string end;

    Order o;

    while (true)
    {
        if (o.count() > 0) {
            std::cout << "\nTo add new device to the order enter \"1\", to edit or remove something from it enter \"2\"";
            std::cout << "\nNote: you can only edit amount of devices in order entry, not the device model itself!\n";
            std::cin >> input;
            switch (input)
            {
            case 1:
                add_to_order(o);
                break;
            case 2:
                edit_order(o);
                break;
            default:
                std::cout << "Error! Unexpected input! Try again\n";
                continue;
            }
        }
        else add_to_order(o);

        std::cout << "\nCurrent order info:\n" + o.print();

        std::cout << "\nIf the order is finished enter \"Y\", otherwise enter any other symbol\n";
        std::cin >> end;
        if (end == "Y" || end == "y") break;
    }

    if (o.count() > 0) {
        orders.push(o);
        std::cout << "\nOrder registered.\n\n";
    }
    else std::cout << "\nError! Can't add order with no entries!.\n\n";
}

void receive_order() {
    if (!orders.size()) {
        std::cout << "\nNo orders to receive!\n\n";
        return;
    }

    Order o = orders.pop();
    std::string input;
    int i;

    std::cout << "\nReceived order info:\n" + o.print();
    while (true)
    {
        std::cout << "\nIf you want to get detailed information about any device model from order enter \"d\" or any other symbol to leave.\n";
        std::cin >> input;
        if (input == "d")
        {
            std::cout << "Enter index of needed device: ";
            std::cin >> i;

            if (i - 1 < 0 || i - 1 >= o.count())
            {
                std::cout << "Error! No order part with such index! Try again\n";
                continue;
            }

            std::cout << '\n' + o.get(i - 1).first->get_full_description();
        }
        else break;
    }

    std::cout << "Order was removed from the queue.\n\n";
}

int main()  
{
    while (true) {
        std::cout << "Welcome. Enter \"1\" to register new order, \"2\" to receive latest order, any other input to leave\n";
        std::string input;
        std::cin >> input;
        if (input == "1") register_order();
        else if (input == "2") receive_order();
        else {
            std::cout << "Goodbye.";
            return 0;
        }
    }
}
