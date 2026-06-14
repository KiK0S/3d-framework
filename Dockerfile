FROM ubuntu:latest

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y locales \
    && sed -i 's/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen \
    && locale-gen en_US.UTF-8 \
    && rm -rf /var/lib/apt/lists/*
ENV LANG=en_US.UTF-8



RUN apt-get update && apt-get -y install software-properties-common && add-apt-repository universe
RUN apt-get -y install \
	cxxtest \
	libsfml-dev
RUN apt-get -y install \
	g++


COPY test_entrypoint.sh /opt/app/entrypoint.sh
COPY test/ /opt/app/test/
COPY src/ /opt/app/src/

RUN chmod +x /opt/app/entrypoint.sh
ENTRYPOINT ["/opt/app/entrypoint.sh"]
