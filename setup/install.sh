cp -a ./upgrade_tool /usr/local/UBTTools/
echo "安装成功后需要手动修改sudoer给程序赋root免密权限
sudo vim /etc/sudoers
在最下方oneai ALL=NOPASSWD:后添加 ,/usr/local/UBTTools/upgrade_tool"
