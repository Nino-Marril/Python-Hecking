#whitelist and blacklist
#Signature Detection
#if found an anomaly, the source IP is dropped and blocked

import os #can interact with operating systems like command iptables
import sys #access system parameters exit script with error code
import time #detect time intervals
from collections import defaultdict #used to simplify packet counting logic
from scapy.all import sniff, IP, TCP #scan, manipulate, analyze packets

THRESHOLD = 40 #limitation
print(f"THRESHOLD{THRESHOLD}")

def read_ip_file(filename): #uses to read list of ip addresses
    with open(filename, "r") as file: #opens a file and does a read mode
        ips = [line.strip() for line in file] #list comprehension
    return set(ips) #return list of ips shiz


def is_nimda_worm(packet): #checks and association with the nimda worm
    if packet.haslayer(TCP) and packet[TCP].dport == 80: #if it has a tcp layer and the port is 80(http request)
        payload = packet[TCP].payload #extract payloads of the packets
        return "GET /scrips/root.exe" in str(payload) #return true if any nimda worm signature is inside and contained
    return False #otherwise


def log_event(message): #writes a log file with a timestamp
    log_folder = "logs" #value setting
    os.makedirs(log_folder, exist_ok=True) #create a log folder if it doesnt exist, use the True to prevent errors if it exist
    timestamp = time.strftime("%Y-$m-$d_%H-%M-%S", time.localtime()) #timestamp
    log_file = os.path.join(log_folder, f"log_{timestamp}.txt") #log file variable and set the log file of the variable with timestamp

    with open(log_file, "a") as file: #automatically closes after writing
        file.write(f"{message}\n")


def packet_callback(packet):

    src_ip = packet[IP].src #extract source ip from the ip layer

    if src_ip in whitelist_ips: #check if the ip is in the whitelist
        return #return if true

    if src_ip in blacklist_ips: #check if the ip is in the blacklist
        os.system(f"iptables -A INPUT -s {src_ip} -j DROP") #it then sends a command where the packed is immediately drops and blocks the ip
        log_event(f"Blocking blacklisted IP: {src_ip}") #creates a log of the blocked IP 
        return

    if is_nimda_worm(packet): #checks if the packed has a nimda worm function
        print(f"Blocking Nimda source IP: {src_ip}") #messages to blocking an ip
        os.system(f"iptables -A INPUT -s {src_ip} -j DROP") #performed the command
        log_event(f"Blocking Nimda source IP: {src_ip}") #logs the event
        return

    packet_count[src_ip] += 1 #increaments

    #IMPORTANT STUFF HERE PACKET RATE STUFF
    current_time = time.time() #time stuff
    time_interval = current_time - start_time[0]

    if time_interval >= 1:
        for ip, count in packet_count.items():
            packet_rate = count / time_interval
            #print(f"IP: {ip}, Packet rate: {packet_rate}") 
            if packet_rate > THRESHOLD and ip not in blocked_ips: #checks on the packet rate
                print(f"Blocking IP: {ip}, packetrate: {packet_rate}")
                os.system(f"iptables -A INPUT -s {ip} -j DROP")
                blocked_ips.add(ip)

        packet_count.clear() #clears it
        start_time[0] = current_time #resets time


if __name__ == "__main__":
    if os.getuid() != 0:
        print(f"This script requires root privileges.")
        sys.exit(1)

    whitelist_ips = read_ip_file("whitelist.txt")
    blacklist_ips = read_ip_file("blacklist.txt")

    packet_count = defaultdict(int)
    start_time = [time.time()]
    blocked_ips = set()

    print("Monitoring network traffic...")
    sniff(filter="ip", prn=packet_callback)
    #implementations
    #ALERTING
        #learn APIs
    #Web Dashboard
        #visualize data
        #flash and django
        #app sec & bug bounty
    #IMPROVE SIGNATURE DETECTION
         #OWASP - learn common attacks(sql, xss, rfi)
         #function relationship
    #NETWORK THREAT <3 MASTERY
