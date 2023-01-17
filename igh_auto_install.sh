sudo apt-get update
sudo apt-get upgrade
git clone https://gitlab.com/etherlab.org/ethercat.git
cd ethercat
git checkout stable-1.5
sudo apt-get install autoconf
sudo apt-get install libtool
sudo rm /usr/bin/ethercat
sudo rm /etc/init.d/ethercat
./bootstrap 
./configure --prefix=/usr/local/etherlab  --disable-8139too --enable-generic 
make all modules
sudo make modules_install install
sudo depmod
sudo ln -s /usr/local/etherlab/bin/ethercat /usr/bin/
sudo ln -s /usr/local/etherlab/etc/init.d/ethercat /etc/init.d/ethercat
sudo mkdir -p /etc/sysconfig
sudo cp /usr/local/etherlab/etc/sysconfig/ethercat /etc/sysconfig/ethercat
sudo groupadd ecusers
sudo usermod -a -G ecusers ${USER}
sudo bash -c "echo KERNEL==\"EtherCAT[0-9]*\", MODE=\"0664\", GROUP=\"ecusers\" > /etc/udev/rules.d/99-EtherCAT.rules"
