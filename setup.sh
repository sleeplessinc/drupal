#!/bin/bash

echo 
echo "----------------------------------------"
echo "THIS IS GOING TO CLOBBER A LOT OF STUFF!"
echo "----------------------------------------"
echo -n "Sure you want to proceed? "
read a
if [ "$a" != "yes" ] ; then
	return 1
fi


pushd /etc
sudo mv localtime was-localtime
sudo ln -s /usr/share/zoneinfo/US/Pacific localtime
popd


sudo yum -y update
sudo yum -y install vim mysql-server mysql httpd mod_ssl php php-mbstring php-mysql php-mcrypt iptraf git 


sudo /etc/init.d/mysqld start
sudo /usr/bin/mysql_secure_installation
sudo /sbin/chkconfig mysqld on


p="`pwd`"
d=`basename $p`

chmod a+x ~
sudo touch /var/www/html/index.html
sudo rm "/etc/httpd/conf.d/$d.conf"
sudo ln -s "$p/httpd.conf" "/etc/httpd/conf.d/$d.conf"
sudo rm "/var/www/$d"
sudo ln -s "$p" "/var/www/$d"


mkdir db-backups

crontab crontab	


sudo /sbin/chkconfig httpd on
sudo /etc/init.d/httpd start


