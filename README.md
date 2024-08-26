# coretech-packet-storm-submission
My submission to coretech's 2024 graduate competition

Before building please ensure the following are installed:

GCC/G++: 
    
    Install using:

    sudo apt update
    sudo apt install build-essential

CMake: 

    Install using:

    sudo apt install cmake

Check its installation using:

    cmake  --version
libpcap:

    Install using:

    sudo apt install libpcap-dev

Clone my project using

    git clone https://github.com/AidanD10101/coretech-packet-storm-submission

Create a build directory:

    $ mkdir project_build
    $ cd project_build


Build my project using:

    $ cmake ..
    $ cmake --build .

Run my project using:

    $ ./Main

Upon running my program you should be presented with the following prompt:
    
    Please enter pcap filename/path (enter 0 to exit):

Enter the name of the pcap file (packet-storm.pcap). For ease of use ensure the .pcap is in the root directory of the project.
You should see a status message:

    Analysing...
Once the application has finished running you will then be presented with a menu that looks like this;

    ===== Aidan's coretech solution =====
    1. Display packet occurrences in ascending order
    2. Display packet occurrences in descending order
    3. Display protocol occurrences
    4. Display capture volume and average packet size
    5. Exit
    Please choose an option: 

Enter an integer to select the options.