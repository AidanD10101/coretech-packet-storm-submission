//
// Created by Aidan on 25/08/2024.
//

#ifndef PcapReader_H
#define PcapReader_H
#include <unordered_map>
#include <iostream>
#include <vector>
#include <netinet/in.h>


class PcapReader {
    public:
        // See documentation in .cpp file
        PcapReader();
        void process_packet(const u_char *packet);
        void sort_ips(int order);
        void print(int choice);
    private:
        // Hashmaps to store destination ips + frequency for sorting later and protocol usage
        std::unordered_map<std::string, int> dest_ip_count;
        std::unordered_map<std::string, int> protocol_count;

        // Vector containing the sorted hashmap
        std::vector<std::pair<std::string, int>> sorted_ips;

        // Used for updating prior protocol_count hasmap, see .cpp file documentation
        u_char protocol = 0;

        void process_ipv4(const u_char *ip_header);
        void process_ipv6(const u_char *ip_header);

        void tally_protocols();

};



#endif //PcapReader_H
