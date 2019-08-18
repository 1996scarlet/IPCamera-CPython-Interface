sudo apt update
sudo apt dist-upgrade
sudo apt install nginx libnginx-mod-rtmp -y
sudo systemctl stop nginx
sudo systemctl start nginx
