//
// Created by Aidan on 25/08/2024.
//


#include "PcapReader.h"
#include "iostream"
#include <netinet/ip.h>

#include "Menu.h"


int main() {
    // Declares pcapReader and menu classes
    PcapReader pcapReader;
    Menu menu;

    // Load pcap file from user input
    pcap_t *handle = menu.load_pcap();

    // If a file is found
    if (handle != nullptr) {
        // Status message
        std::cout << "Analysing..." << std::endl;

        // Init values for later capture/avg packet size calculations
        uint64_t total_packet_size = 0;
        int packet_count = 0;

        // Init variables to store each packet from the pcap file
        pcap_pkthdr header{};
        const u_char *packet;

        // for each packet in the capture
        while ((packet = pcap_next(handle, &header)) != nullptr) {

            total_packet_size += header.len;
            pcapReader.process_packet(packet);
            packet_count++;
        }

        pcap_close(handle);

        const double avg_packet_size = static_cast<double>(total_packet_size) / packet_count;

        std::cout << "Done!" << std::endl;

        // Display menu and take user input
        menu.run(&pcapReader, avg_packet_size, total_packet_size);

    }

    return 0;


}
