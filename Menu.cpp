//
// Created by Aidan on 25/08/2024.
//

#include "Menu.h"
#include <cstdlib>
#include <iostream>
#include <pcap/pcap.h>

#include "PcapReader.h"

void Menu::print() {
    // This method prints the menu for the application using std::cout
    // ---------------------------------------------------------------------------------------------------------------------------
    //
    std::cout << "\n";
    std::cout << "===== Aidan's coretech solution =====\n";
    std::cout << "1. Display packet occurrences in ascending order\n";
    std::cout << "2. Display packet occurrences in descending order\n";
    std::cout << "3. Display protocol occurrences\n";
    std::cout << "4. Display capture volume and average packet size\n";
    std::cout << "5. Exit\n";
    std::cout << "Please choose an option: ";
}

pcap_t *Menu::load_pcap() {
    // This method asks the user for a filename input to select a pcap file to be analysed.
    // ---------------------------------------------------------------------------------------------------------------------------
    // OUTPUT:  handle - pcap_t   : The loaded pcap file, returns nullptr if user cancels
    //
    pcap_t *handle = nullptr;
    do {
        std::cout << "Please enter pcap filename/path (enter 0 to exit): ";
        std::cin >> filename;

        if (filename != "0") {
            char errbuf[PCAP_ERRBUF_SIZE];
            handle = pcap_open_offline(filename.c_str(), errbuf);
            if (!handle) {
                std::cerr << "Failed to open file: " << errbuf << std::endl;
            } else {
                file_found=true;
            }
        } else {
            file_found=true;
        }

    } while (file_found != true);
    return handle;


}

void Menu::run(PcapReader *pcapReader, const double avg_packet_size, uint64_t total_packet_size) {
    // This method displays the menu and takes in user choice to select menu options, calling relevent pcapReader methods.
    // ---------------------------------------------------------------------------------------------------------------------------
    //
    do {
        system("clear");
        print();
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "\n";
                pcapReader->sort_ips(1);
                pcapReader->print(0);
            break;
            case 2:
                std::cout << "\n";
                pcapReader->sort_ips(0);
                pcapReader->print(0);
            break;
            case 3:
                std::cout << "\n";
                pcapReader->print(1);
            break;
            case 4:
                std::cout << "\n";
                std::cout << "Total data capture volume: " << total_packet_size << " bytes\n" << std::endl;
                std::cout << "Average Packet Size: " << avg_packet_size << " bytes\n" << std::endl;
            break;
            case 5:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice" << std::endl;
        }

    } while (choice != 5);
}
