FROM centos:6

ENV lua_path=/lua

RUN yum update
RUN yum install -y lua-devel gcc
VOLUME ${lua_path}
WORKDIR ${lua_path}
CMD ["/bin/bash"]
