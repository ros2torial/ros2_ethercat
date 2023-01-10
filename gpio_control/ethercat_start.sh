sudo /etc/init.d/ethercat stop
sleep 0.1
sudo /etc/init.d/ethercat start
sleep 0.1
ethercat slaves
sleep 0.1
sudo chmod 777 /dev/EtherCAT0
