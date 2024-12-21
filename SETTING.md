# Setting with Docker

## 0. install docker

- [How To Install and Use Docker on Ubuntu 22.04](https://www.digitalocean.com/community/tutorials/how-to-install-and-use-docker-on-ubuntu-22-04#step-1-installing-docker)


## 1. docker image
```commandline
$ docker pull osrf/ros:melodic-desktop-full
$ docker images
```

## 2. docker container

```commandline
docker run \
--name ros1 \
-it \
--privileged \
--env="DISPLAY=:0.0" \
-v=/tmp/.X11-unix:/tmp/.X11-unix:ro \
-v=/dev:/dev \
-v=<Host_ws>:<Container_ws> \
-w=<Work_dir> \
osrf/ros:melodic-desktop-full
```

## Reference

- [Ubuntu에서 Docker를 이용한 ROS1, ROS2 설치](https://with-rl.tistory.com/entry/Ubuntu%EC%97%90%EC%84%9C-Docker%EB%A5%BC-%EC%9D%B4%EC%9A%A9%ED%95%9C-ROS1-ROS2-%EC%84%A4%EC%B9%98)
