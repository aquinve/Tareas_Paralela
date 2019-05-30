#bin/#!/usr/bin/env bash

#docker

echo "INSTALACION DOCKER"
#Actualizar lista de paquetes
sudo apt-get update
#Instala las dependencias necesarias
sudo apt install apt-transport-https ca-certificates curl software-properties-common
#Importar clave GPG
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
#Agregar el repositorio de Docker a la lista de repos del software del sistema
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu bionic stable"
#Actualizar
sudo apt update
#Revisar que Docker este listo para ser instalado
apt-cache policy docker-ce
#Instalar Docker CE
sudo apt install docker-ce
#Verifica versión
docker --version
echo "Ahora Docker debe estar isntalado y para comprobar que esta corriendo, debe ejecutar el siguiente comando"
echo "sudo systemctl status docker"
echo "FIN INSTALACION DOCKER"


#-------------------------------------------------------------------------------

#docker compose
echo "INSTALACION DOCKER COMPOSE"
#verifica y actualiza docker compose
sudo curl -L https://github.com/docker/compose/releases/download/1.21.2/docker-compose-`uname -s`-`uname -m` -o /usr/local/bin/docker-compose
#Permisos de ejecución
sudo chmod +x /usr/local/bin/docker-compose
#Verifica versión
docker-compose --version

#-------------------------------------------------------------------------------
#ejecución de docker sin sudo
sudo usermod -a -G docker $USER
echo "FIN INSTALACION DOCKER COMPOSE"
