sudo apt update
sudo apt dist-upgrade
sudo apt install nginx libnginx-mod-rtmp -y
sudo cp ./nginx.conf /etc/nginx
sudo systemctl stop nginx
sudo systemctl start nginx
sudo apt install libnss3-tools -y
sudo openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout ajax.googleapis.com.key -out ajax.googleapis.com.crt -config ajax.googleapis.com.conf
sudo cp ajax.googleapis.com.crt /etc/ssl/certs/ajax.googleapis.com.crt
sudo mv ajax.googleapis.com.key /etc/ssl/private/ajax.googleapis.com.key
sudo nginx -s reload
certutil -d sql:$HOME/.pki/nssdb -A -t "P,," -n "ajax.googleapis.com" -i ajax.googleapis.com.crt
rm -f ajax.googleapis.com.crt
