#!/bin/bash

sudo -kS modprobe tegra_vnet
sudo -kS sysctl -w net.ipv4.ip_forward=1
sudo -kS sysctl -w net.core.rmem_default=90000000
sudo -kS sysctl -w net.core.rmem_max=90000000
sudo -kS sysctl -w net.ipv4.udp_rmem_min=10000000
sudo -kS sysctl -w net.ipv4.udp_mem='90000000 90000000 90000000'

sudo -kS nmcli dev disconnect eth0
sudo -kS nmcli dev disconnect eth1

sudo -kS ifconfig eth0 up
sudo -kS ifconfig eth0 192.168.7.8
