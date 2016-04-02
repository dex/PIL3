FROM ubuntu

ENV lua_path=/lua

RUN apt-get update
RUN apt-get install -y build-essential
RUN apt-get install -y pkg-config
RUN apt-get install -y luajit libluajit-5.1-dev
VOLUME ${lua_path}
WORKDIR ${lua_path}
CMD ["/bin/bash"]
