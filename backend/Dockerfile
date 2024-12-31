FROM --platform=linux/amd64 ubuntu:24.04

# Install necessary tools
# for "CLion" project : cmake, gdb, g++ (Install "GCC 13" Later)
# for "Crow" : git (for clone repository), libasio-dev
# for "OR-Tools" : build-essential, cmake, lsb-release, wget (for get binary)
RUN apt-get update && \
    apt-get install -y \
      build-essential \
      cmake \
      gdb \
      git \
      g++ \
      libasio-dev \
      lsb-release \
      wget \
    && apt-get clean

# Install "Crow"
WORKDIR /app
RUN git clone https://github.com/CrowCpp/Crow.git && \
    mkdir -p ./Crow/build && \
    cd ./Crow/build && \
    cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF && \
    make install

# Install "OR-Tools"
ARG ORTOOLS_VERSION=v9.10
ARG ORTOOLS_BUILD=4067
ARG ORTOOLS_FILE=or-tools_amd64_ubuntu-24.04_cpp_${ORTOOLS_VERSION}.${ORTOOLS_BUILD}.tar.gz
WORKDIR /app
RUN wget https://github.com/google/or-tools/releases/download/${ORTOOLS_VERSION}/${ORTOOLS_FILE} && \
    mkdir -p or-tools && \
    tar -xvzf ${ORTOOLS_FILE} --strip-components=1 -C or-tools && \
    rm ${ORTOOLS_FILE}

# Build
COPY . /app
WORKDIR /app
RUN mkdir -p build && \
		cd build && \
		cmake .. && \
		make

EXPOSE 18080

CMD ["./build/tsp_solver_backend"]

