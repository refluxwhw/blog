# Linux虚拟机配置

## 静态IP配置
```
sudo vi /etc/network/interfaces

auto lo
iface lo inet loopback

iface eth0 inet static
address 192.168.1.200
gateway 192.168.1.1
netmask 255.255.255.0
network 192.168.1.0
broadcast 192.168.1.255
# DNS 配置
dns-nameservers 61.139.2.69 202.98.96.68

iface eth1 inet static
address 128.0.42.104
gateway 128.0.42.1
netmask 255.255.255.0
network 128.0.42.0
broadcast 128.0.42.255
dns-nameservers 61.139.2.69 202.98.96.68
```
