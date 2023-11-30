FROM docker.io/library/debian:12

RUN apt-get update \
  && apt-get install -y \
    build-essential git curl \
    meson ninja-build libefl-all-dev \
    pkg-config libsdl2-image-dev \
  && apt-get clean

WORKDIR /build

ARG THORVG_VERSION=0.11.5

RUN curl --location --silent --output thorvg.tar.gz https://github.com/thorvg/thorvg/archive/refs/tags/v$THORVG_VERSION.tar.gz \
  && mkdir thorvg-src thorvg-build \
  && tar -xzf thorvg.tar.gz --strip-components=1 -C thorvg-src \
  && cd thorvg-src \
  && meson setup ../thorvg-build \
    -Dexamples=true -Dprefix=/usr \
  && ninja -C ../thorvg-build install \
  && cd /build \
  && rm -rf thorvg.tar.gz thorvg-src thorvg-build

ADD Makefile ./

ADD src ./src
RUN make -j "$(nproc)"
