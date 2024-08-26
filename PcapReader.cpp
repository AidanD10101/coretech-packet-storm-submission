//
// Created by Aidan on 25/08/2024.
//

#include "PcapReader.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <unordered_map>
#include <vector>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>

PcapReader::PcapReader() = default;

void PcapReader::process_packet(const u_char *packet) {
    // This method examines an individual packet to determine its version (v4/v6) and calls methods to update hashmaps containing
    // all the other packets in the capture and packet protocol usage
    // ---------------------------------------------------------------------------------------------------------------------------
    // INPUT:  packet - unsigned char   : the next packet in the pcap capture returned from pcap_next()
    //


    // Assuming Ethernet headers for simplicity
    const u_char *ip_header = packet + 14;
    //
    // Read first 4 bits of the IP header to identify the version
    const u_char version = ip_header[0] >> 4;

    // Call corresponding ip methods
    if (version == 4) {process_ipv4(ip_header);}
    else if (version == 6) {process_ipv6(ip_header);}
    else {
        std::cerr << "Unknown IP version!" << std::endl;
    }

    // Accumulate the protocol used by packet in a hashmap by calling corresponding method
    tally_protocols();
}

void PcapReader::process_ipv4(const u_char *ip_header) {
    // This method extracts the destination ip address from the ip header by casting to iphdr, then increments the corresponding
    // integer value in the destination ip hashmap. It also overwrites the class' protocol u_char so tally_protocol() increments the
    // correct value.
    // ---------------------------------------------------------------------------------------------------------------------------
    // INPUT:  ip_header - unsigned char   : the extracted ip header from the current packet
    //

    // Cast to iphdr
    const auto *ipv4 = (struct ip*)ip_header;

    // Access destination IPv4 address
    const std::string dest_ip = inet_ntoa(ipv4->ip_dst);

    // Update private protocol variable so tally_protocol() increments the correct value.
    this->protocol=ipv4->ip_p;

    // Increment destination ip count in the hashmap.
    dest_ip_count[dest_ip]++;
}

void PcapReader::process_ipv6(const u_char *ip_header) {
    // This method extracts the destination ip address from the ip header by casting to ip6_hdr, then increments the corresponding
    // integer value in the destination ip hashmap. It also overwrites the class' protocol u_char so tally_protocol() increments the
    // correct value.
    // ---------------------------------------------------------------------------------------------------------------------------
    // INPUT:  ip_header - unsigned char   : the extracted ip header from the current packet
    //

        // Cast to ip6_hdr
        auto ipv6 = (struct ip6_hdr *) ip_header;
        // Access binary destination IPv6 address
        char dest_ipv6[INET6_ADDRSTRLEN];

        // Convert binary address to denary
        inet_ntop(AF_INET6, &(ipv6->ip6_dst), dest_ipv6, INET6_ADDRSTRLEN);

        // Update private protocol variable so tally_protocol() increments the correct value.
        this->protocol=ipv6->ip6_nxt;

        // Increment destination ip count in the hashmap.
        dest_ip_count[dest_ipv6]++;
}

void PcapReader::tally_protocols() {
    // This method inspects the current class protocol u_char and increments the corresponding protocol in the hashmap.
    // ---------------------------------------------------------------------------------------------------------------------------
    //

    switch (protocol) {
        case IPPROTO_TCP:
            protocol_count["TCP"]++;
        break;
        case IPPROTO_UDP:
            protocol_count["UDP"]++;
        break;
        case IPPROTO_ICMP:
            protocol_count["ICMP"]++;
        break;
        default:
            protocol_count["Other"]++;
        break;
    }
}

void PcapReader::print(int choice) {
    // This method prints the contents of either the sorted ip vector or the protocol hashmap.
    // ---------------------------------------------------------------------------------------------------------------------------
    // INPUT:  choice - int  : 0 to print the sorted ip list, 1 to print the protocol hashmap.
    //
    switch (choice) {
        case 0:
            for (const auto &pair : sorted_ips) {
                std::cout << "Destination IP: " << pair.first << " - " << pair.second << " packets" << std::endl;
            }
            break;
        case 1:
            for (const auto &pair : protocol_count) {
                std::cout << "Protocol: " << pair.first << " | Count: " << pair.second << std::endl;
            }
            break;
        default:
            break;
    }

}

void PcapReader::sort_ips(int order) {
    // This method sorts the contents of the dest_ip_count hashmap in either ascending or descending order.
    // ---------------------------------------------------------------------------------------------------------------------------
    // INPUT:  order - int  : 0 to sort descending, 1 to sort ascending
    //

    // Copy hashmap values to vector
    sorted_ips.assign(dest_ip_count.begin(), dest_ip_count.end());

    // Use sort function
    switch (order) {
        case 0:
            std::sort(sorted_ips.begin(), sorted_ips.end(), [](const auto &a, const auto &b) { return b.second < a.second; });
        break;
        case 1:
            std::sort(sorted_ips.begin(), sorted_ips.end(), [](const auto &a, const auto &b) { return b.second > a.second; });
        break;
        default:
            std::sort(sorted_ips.begin(), sorted_ips.end(), [](const auto &a, const auto &b) { return b.second < a.second; });
        break;
    }
}

