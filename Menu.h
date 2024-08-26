//
// Created by Aidan on 25/08/2024.
//

#ifndef MENU_H
#define MENU_H
#include <pcap/pcap.h>

#include "PcapReader.h"


class Menu {
public:
    // Prints menu options
    static void print();

    // Loads pcap file
    pcap_t *load_pcap();

    // Main menu method
    void run(PcapReader *pcapReader, double avg_packet_size, uint64_t total_packet_size);

private:
    // Choice for menu option selection
    int choice = 0;

    // Used for logic flow in file loading method
    bool file_found = false;

    // Holder for user input
    std::string filename{};
};



#endif //MENU_H
