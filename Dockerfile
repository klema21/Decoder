FROM gcc:latest as build

RUN apt update && \
    apt install -y \
      libgtest-dev \
      cmake \
      libicu-dev \
    && \
    git submodule update --init --recursive \
    cmake -DCMAKE_BUILD_TYPE=Release /usr/src/gtest && \
    cmake --build .

# would be here after fix conanfile
#COPY conanfile.txt /app/
#RUN mkdir /app/build && cd /app/build && \
#    conan install .. --build=missing

ADD ./src /app/src

WORKDIR /app/build

RUN cmake ../src && \
    cmake --build .

FROM ubuntu:latest

RUN groupadd -r sample && useradd -r -g sample sample
USER sample

WORKDIR /app

COPY --from=build /app/build/hello_world_app .

ENTRYPOINT ["./hello_world_app"]